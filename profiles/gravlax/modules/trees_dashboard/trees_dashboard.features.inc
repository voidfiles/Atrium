<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function trees_dashboard_context_default_contexts() {
  module_load_include('inc', 'trees_dashboard', 'trees_dashboard.defaults');
  return _trees_dashboard_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function trees_dashboard_menu_default_items() {
  module_load_include('inc', 'trees_dashboard', 'trees_dashboard.defaults');
  return _trees_dashboard_menu_default_items();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_dashboard_views_default_views() {
  module_load_include('inc', 'trees_dashboard', 'trees_dashboard.defaults');
  return _trees_dashboard_views_default_views();
}
