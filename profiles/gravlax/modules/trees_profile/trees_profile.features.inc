<?php

/**
 * Implementation of hook_node_info().
 */
function trees_profile_node_info() {
  module_load_include('inc', 'trees_profile', 'trees_profile.defaults');
  return _trees_profile_node_info();
}

/**
 * Implementation of hook_views_default_views().
 */
function trees_profile_views_default_views() {
  module_load_include('inc', 'trees_profile', 'trees_profile.defaults');
  return _trees_profile_views_default_views();
}
