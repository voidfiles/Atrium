<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_book_context_default_contexts() {
  module_load_include('inc', 'atrium_book', 'atrium_book.defaults');
  return _atrium_book_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_book_menu_default_items() {
  module_load_include('inc', 'atrium_book', 'atrium_book.defaults');
  return _atrium_book_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function atrium_book_node_info() {
  module_load_include('inc', 'atrium_book', 'atrium_book.defaults');
  return _atrium_book_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_book_views_default_views() {
  module_load_include('inc', 'atrium_book', 'atrium_book.defaults');
  return _atrium_book_views_default_views();
}
