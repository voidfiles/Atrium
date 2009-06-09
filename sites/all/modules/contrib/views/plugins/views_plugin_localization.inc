<?php
// $Id: $

/**
 * @file
 * Contains the base class for views localization plugins.
 */

/**
 * The base plugin to handle localization of Views strings.
 *
 * @ingroup views_localization_plugins
 */
class views_plugin_localization extends views_plugin {
  /**
   * Initialize the plugin.
   *
   * @param $view
   *   The view object.
   */
  function init(&$view) {
    $this->view = &$view;
  }

  /**
   * Translate a string.
   *
   * @param $string
   *   The string to be translated.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function translate($string, $keys = array()) { }

  /**
   * Save a string for translation.
   *
   * @param $string
   *   The string to be saved.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function save($string, $keys = array()) { }

  /**
   * Delete a string.
   *
   * @param $string
   *   The string to be deleted.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function delete($string, $keys = array()) { }

  /**
   * Collect strings to be exported to code.
   *
   * @param $string
   *   The string to be deleted.
   * @param $keys
   *   An array of keys to identify the string. Generally constructed from
   *   view name, display_id, and a property, e.g., 'header'.
   */
  function export($string, $keys = array()) { }

  /**
   * Render any collected exported strings to code.
   *
   * @param $indent
   *   An optional indentation for prettifying nested code.
   */
  function export_render($indent = '  ') { }
}
