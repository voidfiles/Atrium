<?php
// $Id: casetracker_views_handler_field_status_name.inc,v 1.3.2.1 2009/03/09 15:58:22 jmiccolis Exp $

/**
 * Field handler to show Selective state.
 *
 * @ingroup views_field_handlers
 */
class casetracker_views_handler_field_status_name extends views_handler_field {

  function render($values) {
    if ($values->casetracker_case_case_status_id) {
      return check_plain(casetracker_case_state_load($values->casetracker_case_case_status_id, 'status'));
    }
    return '';
  }
}