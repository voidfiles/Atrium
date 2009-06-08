<?php

/**
 * Implementation of hook_content_default_fields().
 */
function trees_blog_content_default_fields() {
  module_load_include('inc', 'trees_blog', 'trees_blog.defaults');
  return _trees_blog_content_default_fields();
}

/**
 * Implementation of hook_context_default_contexts().
 */
function trees_blog_context_default_contexts() {
  module_load_include('inc', 'trees_blog', 'trees_blog.defaults');
  return _trees_blog_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function trees_blog_menu_default_items() {
  module_load_include('inc', 'trees_blog', 'trees_blog.defaults');
  return _trees_blog_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function trees_blog_node_info() {
  module_load_include('inc', 'trees_blog', 'trees_blog.defaults');
  return _trees_blog_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_blog_views_default_views() {
  module_load_include('inc', 'trees_blog', 'trees_blog.defaults');
  return _trees_blog_views_default_views();
}
