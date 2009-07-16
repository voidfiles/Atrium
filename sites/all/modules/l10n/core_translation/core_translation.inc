<?php
// $Id: core_translation.inc,v 1.1 2008/11/03 01:01:59 nedjo Exp $

/**
 * @file
 * Submit handlers and processing methods for translation import.
 */

/**
 * Process the language addition form submission.
 */
function core_translation_locale_languages_predefined_form_submit($form, &$form_state) {
  $langcode = $form_state['values']['langcode'];

  // See if we have language files to import for the newly added
  // language, collect and import them.
  if ($batch = core_translation_batch_by_language($langcode, '_locale_batch_language_finished')) {
    batch_set($batch);
  }

  $form_state['redirect'] = 'admin/settings/language';
  return;
}

/**
 * Submit callback; handles modules form submission.
 */
function core_translation_system_modules_submit($form, $form_state) {
  include_once './includes/install.inc';
  $new_modules = array();

  // If we are coming from the confirm form...
  if (!isset($form_state['storage'])) {
    // Merge in disabled active modules since they should be enabled.
    // They don't appear because disabled checkboxes are not submitted
    // by browsers.
    if (isset($form_state['values']['disabled_modules'])) {
      $form_state['values']['status'] = array_merge($form_state['values']['status'], $form_state['values']['disabled_modules']);
    }

    // Check values for dependency that we can't install.
    if ($dependencies = system_module_build_dependencies($form_state['values']['validation_modules'], $form_state['values'])) {
      // These are the modules that depend on existing modules.
      foreach (array_keys($dependencies) as $name) {
        $form_state['values']['status'][$name] = 0;
      }
    }
  }
  else {
    $dependencies = NULL;
  }

  // If there where unmet dependencies and they haven't confirmed don't process
  // the submission yet. Store the form submission data needed later.
  if ($dependencies) {
    if (!isset($form_state['values']['confirm'])) {
      return;
    }
  }

  foreach ($form_state['values']['status'] as $key => $choice) {
    if ($choice) {
      if (drupal_get_installed_schema_version($key) == SCHEMA_UNINSTALLED) {
        $new_modules[] = $key;
      }
    }
  }

  // Only act on valid core modules.
  foreach ($new_modules as $key => $module) {
    $info = drupal_parse_info_file(dirname(drupal_get_filename('module', $module)) .'/'. $module .'.info');
    if (!drupal_check_module($module) || !in_array($info['package'], array('Core - required', 'Core - optional'))) {
      unset($new_modules[$key]);
    }
  }

  // Call translations import. This might start a batch, and only return to the redirect
  // path after that.
  if (count($new_modules)) {
    core_translation_system_update($new_modules);
  }

  return;
}

/**
 * Validate system_themes_form form submissions.
 */
function core_translation_system_themes_form_validate($form, &$form_state) {
  // Store list of previously enabled themes and disable all themes
  $form_state['old_theme_list'] = array();
  foreach (list_themes() as $theme) {
    if ($theme->status) {
      $form_state['old_theme_list'][] = $theme->name;
    }
  }
}

/**
 * Process system_themes_form form submissions.
 */
function core_translation_system_themes_form_submit($form, &$form_state) {
  $new_theme_list = array();
  if ($form_state['values']['op'] == t('Save configuration')) {
    if (is_array($form_state['values']['status'])) {
      foreach ($form_state['values']['status'] as $key => $choice) {
        // Always enable the default theme, despite its status checkbox being checked:
        if ($choice || $form_state['values']['theme_default'] == $key) {
          $new_theme_list[] = $key;
        }
      }
    }
  }
  else {
    // Revert to defaults: only Garland is enabled.
    $new_theme_list = array('garland');
  }
  $new_themes = array_diff($new_theme_list, $form_state['old_theme_list']);

  // Call translations import. This might start a batch, and only return to the redirect
  // path after that.
  if (count($new_themes)) {
    core_translation_system_update($new_themes);
  }

  return;
}

/**
 * Process l10n client reimport packages form submissions.
 */
function core_translation_l10n_client_import_package_form_submit($form, &$form_state) {
  // First clean up strings and set up default batch
  l10n_client_import_package_form_submit($form, $form_state);
  // Then we add our own batch for more imports.
  include_once 'includes/locale.inc';
  foreach (array_filter($form_state['values']['langcodes']) as $langcode) {
    if ($batch = core_translation_batch_by_language($langcode, '_locale_batch_language_finished')) {
      batch_set($batch);
    }
  }
}

/**
 * Imports translations when new modules or themes are installed or enabled.
 *
 * This function will either import translation for the component change
 * right away, or start a batch if more files need to be imported.
 *
 * @param $components
 *   An array of component (theme and/or module) names to import
 *   translations for.
 */
function core_translation_system_update($components) {
  include_once 'includes/locale.inc';
  if ($batch = core_translation_batch_by_component($components)) {
    batch_set($batch);
  }
}

/**
 * Prepare a batch to import translations for all enabled core
 * modules or themes in a given language.
 *
 * @param $langcode
 *   Language code to import translations for.
 * @param $finished
 *   Optional finished callback for the batch.
 * @param $skip
 *   Array of component names to skip. Used in the installer for the
 *   second pass import, when most components are already imported.
 * @return
 *   A batch structure or FALSE if no files found.
 */
function core_translation_batch_by_language($langcode, $finished = NULL, $skip = array()) {
  // Collect all files to import for all enabled modules and themes.
  $files = array();
  $components = array();
  $query = "SELECT name, type FROM {system} WHERE status = 1";
  if (count($skip)) {
    $query .= " AND name NOT IN (". db_placeholders($skip, 'varchar') .")";
  }
  $result = db_query($query, $skip);
  while ($component = db_fetch_object($result)) {
    $files = _core_translation_scan_directory($files, $langcode, $component);
    $components[] = $component->name;
  }

  return _locale_batch_build($files, $finished, $components);
}

/**
 * Prepare a batch to run when installing modules or enabling themes.
 * This batch will import translations for the newly added components
 * in all the languages already set up on the site.
 *
 * @param $components
 *   An array of component (theme and/or module) names to import
 *   translations for.
 * @param $finished
 *   Optional finished callback for the batch.
 */
function core_translation_batch_by_component($components, $finished = '_locale_batch_system_finished') {
  $files = array();
  $languages = language_list('enabled');
  unset($languages[1]['en']);
  if (count($components) && count($languages[1])) {
    // Collect all files to import for all $components.
    $result = db_query("SELECT name, type FROM {system} WHERE status = 1 AND name IN (" . db_placeholders($components, 'varchar') . ")", $components);
    while ($component = db_fetch_object($result)) {
      foreach (array_keys($languages[1]) as $langcode) {
        $files = _core_translation_scan_directory($files, $langcode, $component);
      }
    }
    return _locale_batch_build($files, $finished);
  }
  return FALSE;
}

/**
 * Collect all files for this component in the language, named
 * as $langcode.po or with names ending with $langcode.po. This allows
 * for filenames like node-module.de.po to let translators use small
 * files and be able to import in smaller chunks.
 */
function _core_translation_scan_directory($files, $langcode, $component) {
  return array_merge($files, file_scan_directory(_core_translation_get_directory($component->type, $component->name, $langcode), '(^|\.)'. $langcode .'\.po$', array('.', '..', 'CVS'), 0, TRUE));
}

function _core_translation_get_directory($type, $name, $langcode) {
  static $directories = array();
  global $profile;
  if (!isset($files[$type])) {
    $directories[$type] = array();
  }

  // When this function is called during Drupal's initial installation process,
  // the name of the profile that's about to be installed is stored in the global
  // $profile variable. At all other times, the standard Drupal systems variable
  // table contains the name of the current profile, and we can call variable_get()
  // to determine what one is active.
  if (!isset($profile)) {
    $profile = variable_get('install_profile', 'default');
  }

  if (!isset($directories[$type][$name])) {
    $config = conf_path();
    $dir = $type . 's';
    $trans = 'translations';

    $directories = array(
      // Priorize the site directory.
      "$config/",
      // Then the sites/all directory.
      "sites/all/",
      // Then a profile's directory.
      "profiles/$profile/",
      // And finally, allow a translations directory straight off the
      // install root.
      "",
    );
    // We look in all module's subfolders, not only in 'translations' so we can find files in 'includes' or submodules
    foreach ($directories as $directory) {
      $directory .= "$trans/$langcode/$dir/$name";
      if (file_exists($directory)) {
        $directories[$type][$name] = $directory;
        break;
      }
    }
  }
  if (isset($directories[$type][$name])) {
    return $directories[$type][$name];
  }
}

