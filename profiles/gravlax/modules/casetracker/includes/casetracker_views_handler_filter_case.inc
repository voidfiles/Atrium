<?php
// $Id: casetracker_views_handler_filter_case.inc,v 1.1.2.1 2009/03/02 15:59:55 jmiccolis Exp $
/**
 * Filter to only show casetracker cases.
 */
class casetracker_views_handler_filter_case extends views_handler_filter {
  function query() {    
    if ($case_types = variable_get('casetracker_case_node_types', array('casetracker_basic_case'))) {
      // Weed out disabled types
      foreach ($case_types as $type => $enabled) {
        if (empty($enabled)) {
          unset($case_types[$type]);
        }
      }
      $placeholders = db_placeholders($case_types, 'varchar');
      $table = $this->query->ensure_table('node');
      $this->query->add_where($this->options['group'], "$table.type IN ($placeholders)", $case_types);
    }
    else {
      $this->query->add_where($this->options['group'], "FALSE");
      drupal_set_message(t('You have no node types which are acting as cases.', 'error'));
    }
  }
}
