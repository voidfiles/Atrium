<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_shoutbox_context_default_contexts() {
  module_load_include('inc', 'atrium_shoutbox', 'atrium_shoutbox.defaults');
  return _atrium_shoutbox_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function atrium_shoutbox_menu_default_items() {
  module_load_include('inc', 'atrium_shoutbox', 'atrium_shoutbox.defaults');
  return _atrium_shoutbox_menu_default_items();
}

/**
 * Implementation of hook_user_default_permissions().
 */
function atrium_shoutbox_user_default_permissions() {
  module_load_include('inc', 'atrium_shoutbox', 'atrium_shoutbox.defaults');
  return _atrium_shoutbox_user_default_permissions();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_shoutbox_views_default_views() {
  module_load_include('inc', 'atrium_shoutbox', 'atrium_shoutbox.defaults');
  return _atrium_shoutbox_views_default_views();
}
