<?php
// $Id: strongarm.drush.inc,v 1.1.2.1 2009/06/26 21:58:38 yhahn Exp $

/**
 * @file
 * Drush integration for Strongarm. Provides commands to export variables.
 */

/**
 * Implementation of hook_drush_help().
 */
function strongarm_drush_help($section) {
  switch ($section) {
    case 'drush:strongarm':
      return dt("Export Drupal variables. Without any arguments a list of all variables will be shown. If arguments are specified they'll be var_exported to stdout.");
  }
}

/**
 * Implementation of hook_drush_command().
 */
function strongarm_drush_command() {
  $items['strongarm'] = array(
    'callback' => 'strongarm_drush_export',
    'description' => 'Export variable(s).',
  );
  return $items;
}

// Callback for strongarm command.
function strongarm_drush_export() {
  $vars = func_get_args();
  if (empty($vars)) {
    $result = db_query('SELECT name FROM variable');
    $rows = array(array('Variables'));
    while ($row = db_fetch_array($result)) {
      $rows[] = array_values($row);
    }
    drush_print_table($rows, TRUE);
  }
  else {
    $exports = array();
    foreach ($vars as $v) {
      // We use the very unlikely 'DRUSH_STRONGARM_NO_VALUE_HERE' as the 
      // default value which *should* be ok, right?
      $variable = variable_get($v, 'DRUSH_STRONGARM_NO_VALUE_HERE');
      if ($variable !== 'DRUSH_STRONGARM_NO_VALUE_HERE') {
        $exports[$v] = $variable;
      }
    }
    drush_print(var_export($exports));
  }
}
