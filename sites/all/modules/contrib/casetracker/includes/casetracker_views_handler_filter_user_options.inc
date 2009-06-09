<?php
// $Id: casetracker_views_handler_filter_user_options.inc,v 1.1 2009/02/09 23:22:58 jmiccolis Exp $

/**
 * //
 */
class casetracker_views_handler_filter_user_options extends views_handler_filter_many_to_one {
  function get_value_options() {
    $options = array(
      '***CURRENT_USER***' => t('<Current user>'),
      0 => variable_get('casetracker_default_assign_to', variable_get('anonymous', t('Anonymous'))),
    );
    $options += casetracker_user_options();
    $this->value_options = $options;
  }
}