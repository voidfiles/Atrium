<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_dashboard_context_default_contexts() {
  module_load_include('inc', 'atrium_dashboard', 'atrium_dashboard.defaults');
  return _atrium_dashboard_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_dashboard_menu_default_items() {
  module_load_include('inc', 'atrium_dashboard', 'atrium_dashboard.defaults');
  return _atrium_dashboard_menu_default_items();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_dashboard_views_default_views() {
  module_load_include('inc', 'atrium_dashboard', 'atrium_dashboard.defaults');
  return _atrium_dashboard_views_default_views();
}
