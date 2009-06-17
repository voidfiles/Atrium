<?php

/**
 * Implementation of hook_content_default_fields().
 */
function atrium_profile_content_default_fields() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  return _atrium_profile_content_default_fields();
}

/**
 * Implementation of hook_node_info().
 */
function atrium_profile_node_info() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  return _atrium_profile_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_profile_views_default_views() {
  module_load_include('inc', 'atrium_profile', 'atrium_profile.defaults');
  return _atrium_profile_views_default_views();
}
