<?php
// $Id: $

/**
 * @file
 * Contains the Drupal core localization plugin.
 */

/**
 * Localization plugin to pass translatable strings through t().
 *
 * @ingroup views_localization_plugins
 */
class views_plugin_localization_core extends views_plugin_localization {

  /**
   * Translate a string.
   *
   * @param $string
   *   The string to be translated.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function translate($string, $keys = array()) {
    return t($string);
  }

  /**
   * Save a string for translation.
   *
   * @param $string
   *   The string to be saved.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function save($string, $keys = array()) {
    global $language;

    // If the current language is 'en', we need to reset the language
    // in order to trigger an update.
    // TODO: add test for number of languages.
    if ($language->language == 'en') {
      $changed = TRUE;
      $languages = language_list();
      $cached_language = $language;
      unset($languages['en']);
      $language = current($languages);
    }

    t($string);

    if (isset($cached_language)) {
      $language = $cached_language;
    }
    return TRUE;
  }

  /**
   * Delete a string.
   *
   * Deletion is not supported.
   *
   * @param $string
   *   The string to be deleted.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function delete($string, $keys = array()) {
    return FALSE;
  }

  /**
   * Collect strings to be exported to code.
   *
   * String identifiers are not supported so strings are anonymously in an array.
   *
   * @param $string
   *   The string to be deleted.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function export($string, $keys = array()) {
    if (!isset($this->export_strings)) {
      $this->export_strings = array();
    }
    if (!empty($string)) {
      $this->export_strings[] = $string;
    }
  }

  /**
   * Render any collected exported strings to code.
   *
   * @param $indent
   *   An optional indentation for prettifying nested code.
   */
  function export_render($indent = '  ') {
    $output = '';
    if (!empty($this->export_strings)) {
      $this->export_strings = array_unique($this->export_strings);
      $output = $indent . '$translatables[\'' . $this->view->name . '\'] = array(' . "\n";
      foreach ($this->export_strings as $string) {
        $output .= $indent . "  t('" . str_replace("'", "\'", $string) . "'),\n";
      }
      $output .= $indent . ");\n";
    }
    return $output;
  }
}
