<?php 
// $Id$
/**
 * @file
 *   Reusable API for l10n remote updates
 */

include_once './includes/locale.inc';

/**
 * Download and import remote file
 */
function l10n_update_download_import($download_url, $locale, $mode = LOCALE_IMPORT_OVERWRITE) {
  if ($file = l10n_update_download_file($download_url)) {
    $result = l10n_update_import_file($file, $locale, $mode);
    file_delete($file);
    return $result;
  }
}

/**
 * Import local file into the database
 * @param $file
 * @param $locale
 * @param $mode
 * @return unknown_type
 */
function l10n_update_import_file($file, $locale, $mode = LOCALE_IMPORT_OVERWRITE) {   
  $t = get_t();
  // If the file is a filepath, create a $file object
  if (is_string($file)) {
    $filepath = $file;
    $file = new Stdclass();
    $file->filepath = $filepath;
    $file->filename = $filepath;
  }
  return _locale_import_po($file, $locale, $mode , 'default');
}

/**
 * Get remote file and download it to a temporary path
 */
function l10n_update_download_file($download_url, $destination = NULL) {
  $t = get_t();
  $variables['%download_link'] = $download_url;
  
  $file = $destination ? $destination : tempnam(file_directory_temp(), 'translation-');

  if ($file) {
    $variables['%tmpfile'] = $file;
    if (($contents = drupal_http_request($download_url)) && file_put_contents($file, $contents->data)) {
      watchdog('l10n_update', 'Successfully downloaded %download_link to %tmpfile', $variables);
      return $file; 
    }
    else {
      watchdog('l10n_update', 'Unable to download and save %download_link file to %tmpfile.', $variables, WATCHDOG_ERROR);
    }
  }
  else {
    $variables['%tmpdir'] = file_directory_temp();
    watchdog('l10n_update', 'Error creating temporary file for download in %tmpdir. Remote file is %download_link.', $variables, WATCHDOG_ERROR);
  }
  
}

/**
 * Check remote l10n server
 */
function l10n_update_check_remote_server($server = NULL) {
  $t = get_t();
  $server = $server ? $server : variable_get('l10n_client_server', NULL);  
  if ($server) {
    $response = xmlrpc($server .'/xmlrpc.php', 'l10n.server.test', '2.0');
    if ($response && !empty($response['name']) && !empty($response['version'])) {
      if (empty($response['supported']) || !$response['supported']) {
        $response['error'] = $t('The given server could not handle the v2.0 remote submission API.');
      }
      else {
        $response['message'] = $t('Verified that the specified server can handle remote string submissions. Supported languages: %languages.', array('%languages' => $response['languages']));
      }
    }
    else {
      $response['error'] = $t('Invalid localization server address specified. Make sure you specified the right server address.');
    }
  }
  else {
    $response['error'] = $t('No remote server URL found.');
  }
  return $response;
}


/**
 * Get supported language list from remote server
 * 
 */
function l10n_update_get_language_list($server = NULL, $refresh = FALSE) {
  if (!$refresh && ($languages = variable_get('atrium_supported_languages', NULL))) {
    return $languages;
  }
  elseif ($response = l10n_update_check_remote_server($server)) {    
    if (empty($response['error']) && !empty($response['languages'])) {
      $languages = array_map('trim', explode(',', $response['languages']));
      if ($refresh) variable_set('atrium_supported_languages', $languages);
      return $languages;
    }    
  }
}

/**
 * Get names for the language list from locale system
 */
function l10n_update_get_language_names($string_list) {
  include_once './includes/locale.inc';
  $t = get_t();
  $language_codes = array_map('trim', explode(',', $string_list));
  $languages = _locale_get_predefined_list();
  $result = array();
  foreach ($language_codes as $lang) {      
    if (array_key_exists($lang, $languages)) {
      // Try to use verbose locale name
      $name = $lang;
      $name = $languages[$name][0] . (isset($languages[$name][1]) ? ' '. $t('(@language)', array('@language' => $languages[$name][1])) : '');
      $result[$lang] = $name;
    }
  }
  return $result;
}

/**
 * Get remote path for updating
 */
function l10n_update_download_url($module, $version, $locale) {
  if ($path = variable_get('l10n_update_path', NULL)) {
    $replace = array(
      '%module' => $module,
      '%version' => $version,
      '%locale' => $locale,
    );
    return strtr($path, $replace);
  }
}