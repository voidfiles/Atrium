<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function messaging_shoutbox_context_default_contexts() {
  module_load_include('inc', 'messaging_shoutbox', 'messaging_shoutbox.defaults');
  return _messaging_shoutbox_context_default_contexts();
}

/**
 * Implementation of hook_menu_default_items().
 */
function messaging_shoutbox_menu_default_items() {
  module_load_include('inc', 'messaging_shoutbox', 'messaging_shoutbox.defaults');
  return _messaging_shoutbox_menu_default_items();
}

/**
 * Implementation of hook_views_default_views().
 */
function messaging_shoutbox_views_default_views() {
  module_load_include('inc', 'messaging_shoutbox', 'messaging_shoutbox.defaults');
  return _messaging_shoutbox_views_default_views();
}
