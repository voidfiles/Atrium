<?php
// $Id: $

/**
 * @file
 * Contains the 'none' localization plugin.
 */

/**
 * Localization plugin for no localization.
 *
 * @ingroup views_localization_plugins
 */
class views_plugin_localization_none extends views_plugin_localization {

  /**
   * Translate a string; simply return the string.
   */
  function translate($string, $keys = array()) {
    return $string;
  }

  /**
   * Save a string for translation; not supported.
   */
  function save($string, $keys = array()) {
    return FALSE;
  }

  /**
   * Delete a string; not supported.
   */
  function delete($string, $keys = array()) {
    return FALSE;
  }
}

