<?php

/**
 * Implementation of hook_content_default_fields().
 */
function trees_calendar_content_default_fields() {
  module_load_include('inc', 'trees_calendar', 'trees_calendar.defaults');
  return _trees_calendar_content_default_fields();
}

/**
 * Implementation of hook_context_default_contexts().
 */
function trees_calendar_context_default_contexts() {
  module_load_include('inc', 'trees_calendar', 'trees_calendar.defaults');
  return _trees_calendar_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function trees_calendar_menu_default_items() {
  module_load_include('inc', 'trees_calendar', 'trees_calendar.defaults');
  return _trees_calendar_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function trees_calendar_node_info() {
  module_load_include('inc', 'trees_calendar', 'trees_calendar.defaults');
  return _trees_calendar_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_calendar_views_default_views() {
  module_load_include('inc', 'trees_calendar', 'trees_calendar.defaults');
  return _trees_calendar_views_default_views();
}
