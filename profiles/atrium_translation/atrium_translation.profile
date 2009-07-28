<?php
// $Id$
/**
 * @file
 *   Atrium installer in a different language than English
 *   
 * This install profile will retrieve the language list from the server and provide
 * an intermediate page to select a language.
 */

// We reuse some of the main installer functions, so:
require_once './profiles/atrium_installer/atrium_installer.profile';
//require_once './profiles/atrium_translation/modules/l10n_update/l10n_update.inc';

/**
 * Implementation of hook_profile_details().
 * 
 * Note: we can return a language here
 */
function atrium_translation_profile_details() {
  $details = array(
    'name' => 'Atrium translated',
    'description' => 'Atrium by Development Seed in other languages.'
  );
  
  return $details;
}

/**
 * Implementation of hook_profile_modules().
 */
function atrium_translation_profile_modules() {
  global $install_locale;
  
  $modules = atrium_installer_profile_modules();
  // If language is not English we add the 'atrium_translate' module the first
  // To get some modules installed properly we need to have translations loaded
  // We also use it to check connectivity with the translation server on hook_requirements()
  if (!empty($install_locale) && ($install_locale != 'en')) {
    $modules[] = 'l10n_update';
    $modules[] = 'atrium_translate';
  }

  return $modules;
}

/**
 * Implementation of hook_profile_task_list().
 */
function atrium_translation_profile_task_list() {
  $tasks = array(
    //'locale-extended-import' => st('Import more translations'),
    'intranet-modules' => st('Install intranet modules'),
    'intranet-configure' => st('Intranet configuration'),
  );
  return $tasks;
}

/**
 * Implementation of hook_profile_tasks().
 */
function atrium_translation_profile_tasks(&$task, $url) {
  global $install_locale;
  
  // Just in case some of the future tasks adds some output
  $output = '';

  // Install some more modules and maybe localization helpers too
  if ($task == 'profile') {
    if (!empty($install_locale) && ($install_locale != 'en')) {
      module_load_install('atrium_translate');
      if ($batch = atrium_translate_create_batch($install_locale, 'install')) {
        $batch['finished'] = '_atrium_translation_locale_batch_finished';
        // Remove temporary variables and set install task
        variable_del('install_locale_batch_components');
        variable_set('install_task', 'locale-remaining-batch');
        batch_set($batch);
        batch_process($url, $url);
      }
    }
    $task = 'intranet-modules'; 
  }
  
  // Install some more modules
  if ($task == 'intranet-modules') {
    $operations = array();
    $modules = _atrium_installer_core_modules();
    $modules = array_merge($modules, _atrium_installer_atrium_modules());
    // If not English, install core_translation module.
    /*
    if (!empty($install_locale) && ($install_locale != 'en')) {
      $modules[] = 'core_translation';
    }
    */
    $files = module_rebuild_cache();
    
    foreach ($modules as $module) {
      $operations[] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }
    $batch = array(
      'operations' => $operations,
      'finished' => '_atrium_installer_profile_batch_finished',
      'title' => st('Installing @drupal', array('@drupal' => drupal_install_profile_name())),
      'error_message' => st('The installation has encountered an error.'),
    );
    // Start a batch, switch to 'profile-install-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'profile-install-batch');
    batch_set($batch);
    batch_process($url, $url);
  }

  // Import extended interface translations for all the enabled modules.
  // Our translations are in sites/all/translations, these are imported by core_translation module
  if ($task == 'locale-extended-import') {

    // Found nothing to import or not foreign language, go to next task.
    $task = 'intranet-configure';
  }

  // Run additional configuration tasks
  // @todo Review all the cache/rebuild options at the end, some of them may not be needed
  // @todo Review for localization, the time zone cannot be set that way either
  if ($task == 'intranet-configure') {
    // Disable the english locale if using a different default locale.
    if (!empty($install_locale) && ($install_locale != 'en')) {
      db_query("DELETE FROM {languages} WHERE language = 'en'");
    }

    // Remove default input filter formats
    $result = db_query("SELECT * FROM {filter_formats} WHERE name IN ('%s', '%s')", 'Filtered HTML', 'Full HTML');
    while ($row = db_fetch_object($result)) {
      db_query("DELETE FROM {filter_formats} WHERE format = %d", $row->format);
      db_query("DELETE FROM {filters} WHERE format = %d", $row->format);
    }

    // Eliminate the access content perm from anonymous users.
    db_query("UPDATE {permission} set perm = '' WHERE rid = 1");

    // Create user picture directory
    $picture_path = file_create_path(variable_get('user_picture_path', 'pictures'));
    file_check_directory($picture_path, 1, 'user_picture_path');

    // Create freetagging vocab
    $vocab = array(
      'name' => 'Keywords',
      'multiple' => 0,
      'required' => 0,
      'hierarchy' => 0,
      'relations' => 0,
      'module' => 'event',
      'weight' => 0,
      'nodes' => array('blog' => 1, 'book' => 1),
      'tags' => TRUE,
      'help' => t('Enter tags related to your post.'),
    );
    taxonomy_save_vocabulary($vocab);

    // Set time zone
    variable_set('date_default_timezone_name', 'US/Eastern');

    // Calculate time zone offset from time zone name and set the default timezone offset accordingly.
    // You dont need to change the next two lines if you change the default time zone above.
    $date = date_make_date('now', variable_get('date_default_timezone_name', 'US/Eastern'));
    variable_set('date_default_timezone', date_offset_get($date));

    // Set a default footer message.
    variable_set('site_footer', '&copy; 2009 '. l('Development Seed', 'http://www.developmentseed.org', array('absolute' => TRUE)));

    // Theme
    // @TODO: this actually does not work -- by the time we get here
    // the _system_theme_data() static cache has been populated.
    // We rebuild system_theme_data() on the welcome callback (default frontpage)
    // so this works on the first page load.
    system_theme_data();
    db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'garland');
    variable_set('theme_default', 'ginkgo');

    // Rebuild key tables/caches
    menu_rebuild();
    module_rebuild_cache(); // Detects the newly added bootstrap modules
    node_access_rebuild();
    drupal_get_schema('system', TRUE); // Clear schema DB cache
    drupal_flush_all_caches();
    db_query("UPDATE {blocks} SET status = 0, region = ''"); // disable all DB blocks

    // Revert the filter that messaging provides to our default.  
    $component = 'filter';
    $module = 'atrium_intranet';
    module_load_include('inc', 'features', "features.{$component}");
    module_invoke($component, 'features_revert', $module);

    // Get out of this batch and let the installer continue
    $task = 'profile-finished';
  }
  return $output;
}

/**
 * Finished callback for the first locale import batch.
 *
 * Advance installer task to the configure screen.
 */
function _atrium_translation_locale_batch_finished($success, $results) {
  variable_set('install_task', 'intranet-modules');
}

/**
 * Add available list of languages
 *
 * As only system and filter modules are loaded yet, we need to use this naming
 */
/*
function system_form_install_select_locale_form_alter(&$form) {
  // Get current locales
  $locales = array_keys($form['locale']);
  if ($response = atrium_translation_check_remote_server()) {
    if (!empty($response['error'])) {
      $form['error'] = array('#value' => $response['error'], '#weight' => -10);
    }
    elseif (!empty($response['languages'])) {
      foreach (atrium_translation_get_language_names($response['languages']) as $lang => $name) {
        if (!isset($form['locale'][$lang]))  {
          $form['locale'][$lang] = array(
            '#type' => 'radio',
            '#return_value' => $lang,
            '#default_value' => FALSE,
            '#title' => $name,
            '#parents' => array('locale')
          );
        }    
      }
    }
  }
  $form['#submit'][] = 'atrium_translation_select_locale_form_submit';
}
*/