<?php

/**
 * Implementation of hook_content_default_fields().
 */
function trees_intranet_content_default_fields() {
  module_load_include('inc', 'trees_intranet', 'trees_intranet.defaults');
  return _trees_intranet_content_default_fields();
}

/**
 * Implementation of hook_context_default_contexts().
 */
function trees_intranet_context_default_contexts() {
  module_load_include('inc', 'trees_intranet', 'trees_intranet.defaults');
  return _trees_intranet_context_default_contexts();
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function trees_intranet_imagecache_default_presets() {
  module_load_include('inc', 'trees_intranet', 'trees_intranet.defaults');
  return _trees_intranet_imagecache_default_presets();
}

/**
 * Implementation of hook_menu_default_items().
 */
function trees_intranet_menu_default_items() {
  module_load_include('inc', 'trees_intranet', 'trees_intranet.defaults');
  return _trees_intranet_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function trees_intranet_node_info() {
  module_load_include('inc', 'trees_intranet', 'trees_intranet.defaults');
  return _trees_intranet_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_intranet_views_default_views() {
  module_load_include('inc', 'trees_intranet', 'trees_intranet.defaults');
  return _trees_intranet_views_default_views();
}
