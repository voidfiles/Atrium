<?php

/**
 * Implementation of hook_content_default_fields().
 */
function atrium_calendar_content_default_fields() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  return _atrium_calendar_content_default_fields();
}

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_calendar_context_default_contexts() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  return _atrium_calendar_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_calendar_menu_default_items() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  return _atrium_calendar_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function atrium_calendar_node_info() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  return _atrium_calendar_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_calendar_views_default_views() {
  module_load_include('inc', 'atrium_calendar', 'atrium_calendar.defaults');
  return _atrium_calendar_views_default_views();
}
