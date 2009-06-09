<?php
// $Id$

/**
 * Implementation of hook_drush_command().
 */
function atrium_drush_command() {
  $items = array();
  $items['atrium upgrade gravlax'] = array(
    'callback' => 'atrium_drush_upgrade_gravlax',
    'description' => "Migrate a legacy Gravlax site to the Atrium platform.",
  );
  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function atrium_drush_help($section) {
  switch ($section) {
    case 'drush:atrium upgrade gravlax':
      return dt("Migrate a legacy Gravlax site to the Atrium platform.");
  }
}

/**
 * Migration from legacy Gravlax setup to Atrium.
 */
function atrium_drush_upgrade_gravlax() {
  global $profile, $conf;
  $profile = 'atrium';
  $conf['install_profile'] = 'atrium';

  // Set the install profile
  variable_set('install_profile', 'atrium');

  // Re-find modules
  module_rebuild_cache();

  // Iterate through modules and enable/remove where it makes sense.
  $result = db_query("SELECT * FROM {system} WHERE type = 'module'");
  $modules = array();
  while ($row = db_fetch_object($result)) {
    $modules[$row->name] = $row;
  }
  foreach ($modules as $module => $info) {
    if (strpos($module, 'trees') === 0) {
      db_query("DELETE FROM {system} WHERE name = '%s'", $module);
    }
    else if (strpos($module, 'atrium') === 0) {
      db_query("UPDATE {system} SET status = 1 WHERE name = '%s'", $module);
    }
  }

  // Iterate through spaces features and update.
  $result = db_query("SELECT * FROM {spaces_features}");
  while ($row = db_fetch_object($result)) {
    if (strpos($row->id, 'trees') === 0) {
      $renamed = strtr($row->id, array('trees' => 'atrium'));
      db_query("UPDATE {spaces_features} SET id = '%s' WHERE id = '%s' AND sid = %d AND type = '%s'", $renamed, $row->id, $row->sid, $row->type);
    }
  }

  // Update default presets
  $presets = variable_get('spaces_default_presets', array());
  foreach ($presets as $type => $preset) {
    if (strpos($preset, 'trees') === 0) {
      $presets[$type] = strtr($preset, array('trees' => 'atrium'));
    }
  }
  variable_set('spaces_default_presets', $presets);

  // Update theme settings
  variable_set('theme_default', 'ginkgo');

  drupal_flush_all_caches();
}
