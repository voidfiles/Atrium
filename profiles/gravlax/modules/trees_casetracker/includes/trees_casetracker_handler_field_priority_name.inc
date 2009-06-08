<?php
/**
 * Field handler to show Selective state.
 *
 * @ingroup views_field_handlers
 */
class trees_casetracker_handler_field_priority_name extends views_handler_field {
  function render($values) {
    return theme('trees_casetracker_priority', $values->casetracker_case_case_priority_id);
  }
}