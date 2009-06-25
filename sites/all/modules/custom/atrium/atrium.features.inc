<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function atrium_context_default_contexts() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  return _atrium_context_default_contexts();
}

/**
 * Implementation of hook_views_default_views().
 */
function atrium_views_default_views() {
  module_load_include('inc', 'atrium', 'atrium.defaults');
  return _atrium_views_default_views();
}
