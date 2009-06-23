<?php
// $Id: base.inc,v 1.2 2008/06/06 19:29:03 merlinofchaos Exp $
/**
 * @file
 *
 * Provides the basic object definitions used by plugins and handlers.
 */

/**
 * Basic definition for many views objects
 */
class views_object {
  /**
   * Except for displays, options for the object will be held here.
   */
  var $options = array();
  /**
   * Information about options for all kinds of purposes will be held here.
   * @code
   * 'option_name' => array(
   *  - 'default' => default value,
   *  - 'translatable' => TRUE/FALSE (use a localization plugin on display and
   *      wrap in t() on export if true),
   *  - 'contains' => array of items this contains, with its own defaults, etc.
   *      If contains is set, the default will be ignored and assumed to
   *      be array()
   *
   *  ),
   *  @endcode
   * Each option may have any of the following functions:
   *  - export_option_OPTIONNAME -- Special export handling if necessary.
   */
  function option_definition() { return array(); }

  /**
   * Views handlers use a special construct function so that we can more
   * easily construct them with variable arguments.
   */
  function construct() { $this->set_default_options(); }

  /**
   * Set default options on this object. Called by the constructor in a
   * complex chain to deal with backward compatibility.
   */
  function options() { }

  /**
   * Set default options.
   * For backward compatibility, it sends the options array; this is a
   * feature that will likely disappear at some point.
   */
  function set_default_options() {
    $this->_set_option_defaults($this->options, $this->option_definition());

    // Retained for complex defaults plus backward compatibility.
    $this->options($this->options);
  }

  function _set_option_defaults(&$storage, $options, $level = 0) {
    foreach ($options as $option => $definition) {
      if (isset($definition['contains']) && is_array($definition['contains'])) {
        $storage[$option] = array();
        $this->_set_option_defaults($storage[$option], $definition['contains'], $level++);
      }
      elseif (!empty($definition['translatable']) && !empty($definition['default'])) {
        $storage[$option] = t($definition['default']);
      }
      else {
        $storage[$option] = isset($definition['default']) ? $definition['default'] : NULL;
      }
    }
  }

  /**
   * Unpack options over our existing defaults, drilling down into arrays
   * so that defaults don't get totally blown away.
   */
  function unpack_options(&$storage, $options, $definition = NULL, $localization_keys = array()) {
    if (!is_array($options)) {
      return;
    }

    if (!isset($definition)) {
      $definition = $this->option_definition();
    }

    foreach ($options as $key => $value) {
      // Ensure we have a localization plugin.
      $this->view->init_localization();

      if (is_array($value)) {
        if (!isset($storage[$key]) || !is_array($storage[$key])) {
          $storage[$key] = array();
        }

        $this->unpack_options($storage[$key], $value, isset($definition[$key]) ? $definition[$key] : array(), array_merge($localization_keys, array($key)));
      }

      // Don't localize strings during editing. When editing, we need to work with
      // the original data, not the translated version.
      else if (!$this->view->editing && (!empty($definition[$key]['translatable']) || !empty($definition['contains'][$key]['translatable'])) && !empty($value)) {
        // Allow other modules to make changes to the string before it's
        // sent for translation.
        // Look for a propertyname_format property.
        $translation_data = $this->view->invoke_translation_process($value, isset($options[$key . '_format']) ? $options[$key . '_format'] : NULL, 'pre');
        if ($this->view->is_translatable()) {
          // The $keys array is built from the view name, any localization keys
          // sent in, and the name of the property being processed.
          $storage[$key] = $this->view->localization_plugin->translate($value, array_merge(array($this->view->name), $localization_keys, array($key)));
        }
        // Otherwise, this is a code-based string, so we can use t().
        else {
          $storage[$key] = t($value);
        }
        $this->view->invoke_translation_process($value, $translation_data, 'post');
      }
      else {
        $storage[$key] = $value;
      }
    }
  }

  /**
   * Let the handler know what its full definition is.
   */
  function set_definition($definition) {
    $this->definition = $definition;
    if (isset($definition['field'])) {
      $this->real_field = $definition['field'];
    }
  }

  function destroy() {
    if (isset($this->view)) {
      unset($this->view);
    }

    if (isset($this->display)) {
      unset($this->display);
    }

    if (isset($this->query)) {
      unset($this->query);
    }
  }
}
