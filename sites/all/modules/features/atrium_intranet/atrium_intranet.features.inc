<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_intranet_context_default_contexts() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_context_default_contexts();
}

/**
 * Implementation of hook_filter_default_formats().
 */
function atrium_intranet_filter_default_formats() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_filter_default_formats();
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function atrium_intranet_imagecache_default_presets() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_imagecache_default_presets();
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_intranet_menu_default_items() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function atrium_intranet_node_info() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_node_info();
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_intranet_user_default_permissions() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_user_default_permissions();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_intranet_views_default_views() {
  module_load_include('inc', 'atrium_intranet', 'atrium_intranet.defaults');
  return _atrium_intranet_views_default_views();
}
