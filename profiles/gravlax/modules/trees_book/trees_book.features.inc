<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function trees_book_context_default_contexts() {
  module_load_include('inc', 'trees_book', 'trees_book.defaults');
  return _trees_book_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function trees_book_menu_default_items() {
  module_load_include('inc', 'trees_book', 'trees_book.defaults');
  return _trees_book_menu_default_items();
}

/**
 * Implementation of hook_node_info().
 */
function trees_book_node_info() {
  module_load_include('inc', 'trees_book', 'trees_book.defaults');
  return _trees_book_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_book_views_default_views() {
  module_load_include('inc', 'trees_book', 'trees_book.defaults');
  return _trees_book_views_default_views();
}
