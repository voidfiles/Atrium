<?php
// $Id$
/**
 * Implementation of hook_views_plugins().
 */
function litenode_views_plugins() {
  return array(
    'style' => array(
      'litenode' => array(
        'title' => t('Litenode'),
        'help' => t('Lighter, faster version of the node style.'),
        'handler' => 'litenode_plugin_style_litenode',
        'path' => drupal_get_path('module', 'litenode') .'/views',
        'theme' => 'litenode_view',
        'type' => 'normal',
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_pre_build().
 */
function litenode_views_pre_build(&$view) {
  if ($view->display_handler->get_option('style_plugin') == 'litenode') {
    if (!empty($view->display[$view->current_display]->display_options['fields'])) {
      $fields = $view->display[$view->current_display]->display_options['fields']; 
    }
    else {
      $fields = $view->display['default']->display_options['fields']; 
    }

    $options = $view->display_handler->get_option('style_options');
    foreach (litenode_views_fields() as $module => $module_fields) {
      if (!empty($options['modules'][$module])) {
        $fields = array_merge($fields, $module_fields);
      }
    }
    $view->display_handler->override_option('fields', $fields);
  }
}

/**
 * Implementation of hook_views_query_alter().
 */
function litenode_views_query_alter(&$view, &$query) {
  if ($view->display_handler->get_option('style_plugin') == 'litenode') {
    $options = $view->display_handler->get_option('style_options');
    if (!empty($options['cullen'])) {
      $sub = drupal_clone($query);
      $base = $query->base_table;

      foreach (array_keys($query->where) as $index) {
        reset($query->where[$index]['args']);
        $current_arg = key($query->where[$index]['args']);
        foreach ($query->where[$index]['clauses'] AS $key => $condition) {
          // If the where condition is against the base table...
          if (strpos($condition, "$base.") === 0) {
            unset($query->where[$index]['clauses'][$key]);
            if (preg_match(DB_QUERY_REGEXP, $condition)) {
              unset($query->where[$index]['args'][$current_arg]);
              $current_arg++;
            }
          }
          // If not drop it from the subquery
          else {
            unset($sub->where[$index]['clauses'][$key]);
            if (preg_match(DB_QUERY_REGEXP, $condition)) {
              unset($sub->where[$index]['args'][$current_arg]);
              $current_arg++;
            }
          }
        }
        if (empty($query->where[$index]['clauses'])) {
          unset($query->where[$index]);
        }
        if (empty($sub->where[$index]['clauses'])) {
          unset($sub->where[$index]);
        }
      }

      $backwards_alias = array();
      // Strip subselect of non base table fields
      foreach ($sub->fields as $key => $field) {
        if ($field['table'] != $base) {
          unset($sub->fields[$key]);
        }
        else {
          $backwards_alias[$sub->fields[$key]['alias']] = $sub->fields[$key]['field'];
        }
      }

      // Remove orderbys on subselect for fields that have been stripped
      foreach ($sub->orderby as $key => $order) {
        $order = explode(' ', $order);
        if (empty($sub->fields[$order[0]])) {
          unset($sub->orderby[$key]);
        }
        else {
          if (!empty($backwards_alias)) {
            $sub->orderby[$key] = str_replace(array_keys($backwards_alias), array_values($backwards_alias), $sub->orderby[$key]);
          }
          unset($query->orderby[$key]);
        }
      }

      $sub->fields = array(array('table' => $base, 'field' => '*'));
      $sub->table_queue = array_slice($sub->table_queue, 0, 1);
      $sub->relationships = array_slice($sub->relationships, 0, 1);

      // Add subquery for assembly later
      $view->query->subselect = $sub->query();
      $view->query->subselect_args = $sub->get_where_args();
    }
  }
}

/**
 * Implementation of hook_views_pre_execute().
 */
function litenode_views_pre_execute(&$view) {
  if ($view->display_handler->get_option('style_plugin') == 'litenode' && empty($view->query->fields['nid']['distinct'])) {
    // Remove any unnecessary joins from the count query.
    // This is only possible if the View in question lacks
    // a DISTINCT on the base field.
    // @TODO test this with relationships present
    $count_query = drupal_clone($view->query);
    $where = $count_query->condition_sql();
    // If table is not present in the where condition, we should drop the join
    foreach ($count_query->tables[$count_query->base_table] as $table => $info) {
      if ($table != $count_query->base_table && strpos($where, $table) === FALSE) {
        unset($count_query->tables[$count_query->base_table][$table]);
        unset($count_query->table_queue[$table]);
      }
    }
    $view->build_info['count_query'] = $count_query->query(TRUE);

    // Cullen queries -- EXPERIMENTAL
    $options = $view->display_handler->get_option('style_options');
    if (!empty($options['cullen'])) {
      // Cullen query
      $view->build_info['query'] = litenode_cullen_query($view->query);
      $view->build_info['count_query'] = litenode_cullen_query($count_query, TRUE);

      // Merge arguments in the right order
      $view->build_info['query_args'] = array_merge($view->query->subselect_args, $view->build_info['query_args']);
    }
  }
}

/**
 * Identical to the query() method found in Views' query.inc, except
 * that it replaces the base table with the subselect attached to
 * the query object.
 */
function litenode_cullen_query($query, $get_count = FALSE) {

  // Check query distinct value.
  if (empty($query->no_distinct) && $query->distinct && !empty($query->fields)) {
    if (!empty($query->fields[$query->base_field])) {
      $query->fields[$query->base_field]['distinct'] = TRUE;
    }
  }

  /**
    * An optimized count query includes just the base field instead of all the fields.
    * Determine of this query qualifies by checking for a groupby or distinct.
    */
  $fields_array = $query->fields;
  if ($get_count && !$query->groupby) {
    foreach ($fields_array as $field) {
      if (isset($field['distinct'])) {
        $get_count_optimized = FALSE;
        break;
      }
    }
  }
  else {
    $get_count_optimized = FALSE;
  }
  if (!isset($get_count_optimized)) {
    $get_count_optimized = TRUE;
  }

  $joins = $fields = $where = $having = $orderby = $groupby = '';
  // Add all the tables to the query via joins. We assume all LEFT joins.
  foreach ($query->table_queue as $table) {
    if (is_object($table['join'])) {
      $joins .= $table['join']->join($table, $query) ."\n";
    }
  }


  foreach ($fields_array as $field) {
    if ($fields) {
      $fields .= ",\n   ";
    }
    $string = '';
    if (!empty($field['table'])) {
      $string .= $field['table'] .'.';
    }
    $string .= $field['field'];
    if (isset($field['distinct'])) {
      $string = "DISTINCT($string)";
    }
    if (isset($field['count'])) {
      $string = "COUNT($string)";
    }
    if ($field['alias']) {
      $string .= " AS $field[alias]";
    }
    $fields .= $string;

    if ($get_count_optimized) {
      // We only want the first field in this case.
      break;
    }
  }

  if ($query->groupby) {
    $groupby = "GROUP BY ". implode(', ', $query->groupby) ."\n";
    if ($query->having) {
      $having = $query->condition_sql('having');
    }
  }

  if (!$get_count_optimized) {
    // we only add the groupby if we're not counting.
    if ($query->orderby) {
      $orderby = "ORDER BY ". implode(', ', $query->orderby) ."\n";
    }
  }

  $where = $query->condition_sql();

  if (!empty($query->subselect)) {
    $sql = "SELECT $fields, 'cullened' \n  FROM (". $query->subselect .") $query->base_table \n$joins $where $groupby $having $orderby";
  }
  else {
    $query = "SELECT $fields\n FROM {". $query->base_table ."} $query->base_table \n$joins $where $groupby $having $orderby";
  }

  $replace = array('&gt;' => '>', '&lt;' => '<');
  $sql = strtr($sql, $replace);

  return $sql;
}
