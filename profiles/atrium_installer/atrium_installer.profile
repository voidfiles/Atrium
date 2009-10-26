<?php
// $Id$

/**
 * Implementation of hook_profile_details().
 */
function atrium_installer_profile_details() {
  return array(
    'name' => 'Atrium',
    'description' => 'Atrium by Development Seed.'
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function atrium_installer_profile_modules() {
  $modules = array(
     // Drupal core
    'block',
    'comment',
    'dblog',
    'filter',
    'help',
    'menu',
    'node',
    'openid',
    'search',
    'system', 
    'taxonomy',
    'upload',
    'user',
    // Admin
    'admin',
    // Views
    'views', 'litenode',
    // OG
    'og', 'og_access', 'og_actions', 'og_views',
    // Context
    'context', 'context_contrib',
    // Features
    'features',
    // Image
    'imageapi', 'imageapi_gd', 'imagecache',
    // Token
    'token',
    // Transliteration
    'transliteration',
    // Messaging
    'messaging', 'messaging_mail',
    // Notifications
    'notifications', 'notifications_content', 'notifications_views',
    // Open ID
    'openidadmin',
    // PURL
    'purl',
    // Seed
    'seed',
    // Spaces
    'spaces', 'spaces_site', 'spaces_user', 'spaces_og',
    // Ucreate
    'ucreate', 'ucreate_og',
    // Atrium
    'atrium',
  );

  // If language is not English we add the 'atrium_translate' module the first
  // To get some modules installed properly we need to have translations loaded
  // We also use it to check connectivity with the translation server on hook_requirements()
  if (_atrium_installer_language_selected()) {
    // We need locale before l10n_update because it adds fields to locale tables
    $modules[] = 'locale';
    $modules[] = 'l10n_update';
    $modules[] = 'atrium_translate';
  }

  return $modules;
}

/**
 * Returns an array list of atrium features (and supporting) modules.
 */
function _atrium_installer_atrium_modules() {
  return array(
    // Strongarm
    'strongarm',
    // Core features
    'book',
    // Casetracker
    'casetracker', 'casetracker_basic',
    // Calendar, date
    'date', 'date_api', 'date_popup', 'litecal',
    // CCK
    'content', 'nodereference', 'text', 'optionwidgets',
    // FeedAPI
    'feedapi', 'feedapi_node', 'feedapi_mapper', 'feedapi_inherit', 'parser_ical',
    // Messaging
    'messaging_shoutbox',
    // Notifications
    'notifications_team', 'mail2web', 'mailhandler',
    // Content profile
    'content_profile',
    // Atrium features
    'atrium_blog', 'atrium_book', 'atrium_calendar', 'atrium_dashboard', 'atrium_casetracker', 'atrium_profile', 'atrium_shoutbox',
    // Formats
    'codefilter', 'markdown',
    // Others
    'comment_upload', 'diff', 'prepopulate', 'xref',
    // Spaces design customizer
    'color', 'spaces_design',
    // VBO
    'views_bulk_operations',
    // Atrium intranet distro module
    'atrium_groups', 'atrium_members', 'atrium_intranet',
  );
}

/**
 * Implementation of hook_profile_task_list().
 */
function atrium_installer_profile_task_list() {
  if (_atrium_installer_language_selected()) {
    $tasks['intranet-translation-batch'] = st('Download and import translation');
  }
  $tasks['intranet-modules-batch'] = st('Install intranet modules');
  $tasks['intranet-configure-batch'] = st('Configure intranet');
  return $tasks;
}

/**
 * Implementation of hook_profile_tasks().
 */
function atrium_installer_profile_tasks(&$task, $url) {
  global $profile, $install_locale;
  
  // Just in case some of the future tasks adds some output
  $output = '';

  // Download and install translation if needed
  if ($task == 'profile') {
    if (_atrium_installer_language_selected() && module_exists('atrium_translate')) {
      module_load_install('atrium_translate');
      if ($batch = atrium_translate_create_batch($install_locale, 'install')) {
        $batch['finished'] = '_atrium_installer_translate_batch_finished';
        // Remove temporary variables and set install task
        variable_del('install_locale_batch_components');
        variable_set('install_task', 'intranet-translation-batch');
        batch_set($batch);
        batch_process($url, $url);
        // Jut for cli installs. We'll never reach here on interactive installs.
        return;
      }
    }
    // If we reach here, means no language install, move on to the next task
    $task = 'intranet-modules';
  }

  // We are running a batch task for this profile so basically do nothing and return page
  if (in_array($task, array('intranet-modules-batch', 'intranet-translation-batch', 'intranet-configure-batch'))) {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }
  
  // Install some more modules and maybe localization helpers too
  if ($task == 'intranet-modules') {
    $modules = _atrium_installer_atrium_modules();
    $files = module_rebuild_cache();
    // Create batch
    foreach ($modules as $module) {
      $batch['operations'][] = array('_install_module_batch', array($module, $files[$module]->info['name']));
    }    
    $batch['finished'] = '_atrium_installer_profile_batch_finished';
    $batch['title'] = st('Installing @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['error_message'] = st('The installation has encountered an error.');

    // Start a batch, switch to 'intranet-modules-batch' task. We need to
    // set the variable here, because batch_process() redirects.
    variable_set('install_task', 'intranet-modules-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }

  // Run additional configuration tasks
  // @todo Review all the cache/rebuild options at the end, some of them may not be needed
  // @todo Review for localization, the time zone cannot be set that way either
  if ($task == 'intranet-configure') {
    $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));
    $batch['operations'][] = array('_atrium_installer_intranet_configure', array());
    $batch['operations'][] = array('_atrium_installer_intranet_configure_check', array());
    $batch['finished'] = '_atrium_installer_intranet_configure_finished';
    variable_set('install_task', 'intranet-configure-batch');
    batch_set($batch);
    batch_process($url, $url);
    // Jut for cli installs. We'll never reach here on interactive installs.
    return;
  }  

  return $output;
}

/**
 * Check whether we are installing in a language other than English
 */
function _atrium_installer_language_selected() {
  global $install_locale;
  return !empty($install_locale) && ($install_locale != 'en');
}

/**
 * Configuration. First stage.
 */
function _atrium_installer_intranet_configure() {
  global $install_locale;

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
    'nodes' => array('blog' => 1, 'book' => 1, 'casetracker_basic_case' => 1, 'casetracker_basic_project' => 1, 'event' => 1),
    'tags' => TRUE,
    'help' => t('Enter tags related to your post.'),
  );
  taxonomy_save_vocabulary($vocab);

  // Set time zone
  $tz_offset = date('Z');
  variable_set('date_default_timezone', $tz_offset);

  // Set a default footer message.
  variable_set('site_footer', '&copy; 2009 '. l('Development Seed', 'http://www.developmentseed.org', array('absolute' => TRUE)));

  // Set default theme. This needes some more set up on next page load
  // We cannot do everything here because of _system_theme_data() static cache
  system_theme_data();
  db_query("UPDATE {system} SET status = 0 WHERE type = 'theme' and name ='%s'", 'garland');
  variable_set('theme_default', 'ginkgo');
  db_query("UPDATE {blocks} SET status = 0, region = ''"); // disable all DB blocks

  // Revert the filter that messaging provides to our default.  
  $component = 'filter';
  $module = 'atrium_intranet';
  module_load_include('inc', 'features', "features.{$component}");
  module_invoke($component, 'features_revert', $module);  
}

/**
 * Configuration. Second stage.
 */
function _atrium_installer_intranet_configure_check() {
  // Rebuild key tables/caches
  module_rebuild_cache(); // Detects the newly added bootstrap modules
  node_access_rebuild();
  drupal_get_schema(NULL, TRUE); // Clear schema DB cache
  drupal_flush_all_caches();    
  system_theme_data();  // Rebuild theme cache.
   _block_rehash();      // Rebuild block cache.
  views_invalidate_cache(); // Rebuild the views.
  // This one is done by the installer alone
  //menu_rebuild();       // Rebuild the menu.
  features_rebuild();   // Features rebuild scripts.
}

/**
 * Finish configuration batch
 * 
 * @todo Handle error condition
 */
function _atrium_installer_intranet_configure_finished($success, $results) {
  variable_set('atrium_install', 1);
  // Get out of this batch and let the installer continue. If loaded translation,
  // we skip the locale remaining batch and move on to the next.
  // However, if we didn't make it with the translation file, or they downloaded
  // an unsupported language, we let the standard locale do its work.
  if (variable_get('atrium_translate_done', 0)) {
    variable_set('install_task', 'finished');
  }
  else {
    variable_set('install_task', 'profile-finished');
  } 
}

/**
 * Finished callback for the modules install batch.
 *
 * Advance installer task to language import.
 */
function _atrium_installer_profile_batch_finished($success, $results) {
  variable_set('install_task', 'intranet-configure');
}

/**
 * Finished callback for the first locale import batch.
 *
 * Advance installer task to the configure screen.
 */
function _atrium_installer_translate_batch_finished($success, $results) {
  include_once 'includes/locale.inc';
  // Let the installer now we've already imported locales
  variable_set('atrium_translate_done', 1);
  variable_set('install_task', 'intranet-modules');
  _locale_batch_language_finished($success, $results);
}

/**
 * Alter some forms implementing hooks in system module namespace
 * 
 * This is a trick for hooks to get called, otherwise we cannot alter forms
 */

// Set Atrium as default profile
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  foreach($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'atrium_installer';
  }
}

/**
 * Set English as default language.
 * 
 * If no language selected, the installation crashes. I guess English should be the default 
 * but it isn't in the default install. @todo research, core bug?
 */
function system_form_install_select_locale_form_alter(&$form, $form_state) {
  $form['locale']['en']['#value'] = 'en';
}
