<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function trees_casetracker_context_default_contexts() {
  module_load_include('inc', 'trees_casetracker', 'trees_casetracker.defaults');
  return _trees_casetracker_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function trees_casetracker_menu_default_items() {
  module_load_include('inc', 'trees_casetracker', 'trees_casetracker.defaults');
  return _trees_casetracker_menu_default_items();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_casetracker_views_default_views() {
  module_load_include('inc', 'trees_casetracker', 'trees_casetracker.defaults');
  return _trees_casetracker_views_default_views();
}
