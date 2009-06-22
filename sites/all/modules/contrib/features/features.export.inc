<?php
// $Id: features.export.inc,v 1.1.2.24 2009/06/22 03:20:46 yhahn Exp $

/**
 * Update form.
 */
function features_update_form($form_state, $module) {
  features_include();
  $export = array_merge($module->info, features_populate($module->info['features'], $module->name));

  $form['markup'] = array(
    '#type' => 'markup',
    '#value' => "<h3>". t('Update !module_name', array('!module_name' => $module->name)) ."</h3>",
  );
  $form['export'] = array(
    '#type' => 'value',
    '#value' => $export,
  );
  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($module->info['name']) ? $module->info['name'] : '',
  );
  $form['module_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine-readable name'),
    '#value' => $module->name,
    '#default_value' => $module->name,
    '#disabled' => TRUE,
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => !empty($module->info['description']) ? $module->info['description'] : '',
  );
  $form['optional'] = array(
    '#title' => t('Optional information'),
    '#type' => 'fieldset',
    '#tree' => FALSE,
  );
  $form['optional']['project_status_url'] = array(
    '#title' => t('Update feed'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => !empty($module->info['project status url']) ? $module->info['project status url'] : '',
  );
  $form['optional']['version'] = array(
    '#title' => t('Version'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#default_value' => !empty($module->info['version']) ? $module->info['version'] : '',
  );
  $form['download'] = array(
    '#type' => 'submit',
    '#value' => t('Download updated feature'),
  );
  return $form;
}

/**
 * Update form submit.
 */
function features_update_form_submit(&$form, &$form_state) {
  $export = $form_state['values']['export'];
  $export['name'] = $form_state['values']['name'];
  $export['description'] = $form_state['values']['description'];
  if (!empty($form_state['values']['version'])) {
    $export['version'] = $form_state['values']['version'];
  }
  if (!empty($form_state['values']['project_status_url'])) {
    $export['project status url'] = $form_state['values']['project_status_url'];
  }

  $module_name = $form_state['values']['module_name'];
  $filename = !empty($export['version']) ? "{$module_name}-{$export['version']}" : $module_name;

  $files = features_export_render($export, $module_name, TRUE);
  features_export_download_files($files, $module_name, $filename);
}

/**
 * Export form.
 */
function features_export_form($form_state, $module = NULL) {
  features_include();

  $steps = array(
    t('Step 1: provide basic information'),
    t('Step 2: choose sources'),
    t('Step 3: confirm components'),
    t('Step 4: download your feature'),
  );

  // retrieve storage variables
  $module_name = !empty($form_state['storage']['module_name']) ? $form_state['storage']['module_name'] : '';
  $export = !empty($form_state['storage']['export']) ? $form_state['storage']['export'] : array();

  // we are re-exporting a module -- load up data and export
  if (!empty($module)) {
    $step = $form_state['storage']['step'] = 3;
    $steps[3] = t('Update your feature: !module_name', array('!module_name' => $module->name));
    $module_name = $module->name;
    $export = array_merge($module->info, features_populate($module->info['features'], $module->name));
  }
  // we are coming in without a step, so default to step 1
  else {
    $step =
    $form_state['storage']['step'] = empty($form_state['storage']['step']) ? 0 : $form_state['storage']['step'];
  }

  $form = array();
  $form['step'] = array(
    '#type' => 'markup',
    '#value' => "<h3>{$steps[$step]}</h3>",
  );

  switch ($step) {

    // Provide additional information =================================
    case 0:
      $form['name'] = array(
        '#title' => t('Name'),
        '#description' => t('Provide a name for your feature.'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#default_value' => '',
        '#attributes' => array('class' => 'feature-name'),
      );
      $form['module_name'] = array(
        '#type' => 'textfield',
        '#title' => t('Machine-readable name'),
        '#description' => t('Provide a machine-readable name for your feature. This may only contain lowercase letters, numbers and underscores. <strong>It should also avoid conflicting with the names of any existing Drupal modules.</strong>'),
        '#required' => TRUE,
        '#default_value' => '',
        '#attributes' => array('class' => 'feature-module-name'),
      );
      $form['description'] = array(
        '#title' => t('Description'),
        '#description' => t('Provide a description for your feature.'),
        '#type' => 'textfield',
        '#required' => TRUE,
        '#default_value' => '',
      );
      $form['optional'] = array(
        '#title' => t('Optional information'),
        '#type' => 'fieldset',
        '#tree' => FALSE,
      );
      $form['optional']['project_status_url'] = array(
        '#title' => t('Update feed'),
        '#description' => t('The URL of the update XML feed for this feature.'),
        '#type' => 'textfield',
        '#required' => FALSE,
        '#default_value' => '',
      );
      $form['optional']['version'] = array(
        '#title' => t('Version'),
        '#description' => t('The version information for this feature.'),
        '#type' => 'textfield',
        '#required' => FALSE,
        '#default_value' => '',
      );
      drupal_add_js(drupal_get_path('module', 'features') .'/features.js');
      break;

    // Choose a context ===============================================
    case 1:
      $form['sources'] = array('#tree' => TRUE);
      $modules = features_get_modules();
      foreach (module_implements('features_api') as $module_name) {
        $info = module_invoke($module_name, 'features_api');
        if (!empty($info['feature_source']) && $options = module_invoke($module_name, 'features_export_options')) {
          $form['sources'][$module_name] = array(
            '#type' => 'checkboxes',
            '#options' => $options,
            '#title' => $modules[$module_name]->name,
          );
        }
      }
      break;

    // Confirm components =============================================
    case 2:
      $form['#theme'] = 'features_export_form_confirm';
      $form['detected'] =
      $form['added'] = array('#tree' => TRUE);

      foreach ($export['conflicts'] as $type => $messages) {
        foreach ($messages as $msg) {
          drupal_set_message($msg, $type);
        }
      }

      // Display each set of components and options for adding to the components
      foreach (module_implements('features_api') as $module_name) {
        $module = features_get_modules($module_name);
        $export_options = module_hook($module_name, 'features_export_options') ? module_invoke($module_name, 'features_export_options') : array();
        $detected_components = !empty($export['features'][$module_name]) ? $export['features'][$module_name] : array();

        if (!empty($detected_components) || !empty($export_options)) {
          if (!empty($detected_components)) {
            $form['detected'][$module_name] = array(
              '#type' => 'markup',
              '#value' => theme('item_list', array_keys($detected_components)),
            );
          }
          if (!empty($export_options)) {
            $form['added'][$module_name] = array(
              '#type' => 'checkboxes',
              '#title' => $module->info['name'],
              '#options' => array_diff_key($export_options, $detected_components),
            );
          }
          else {
            $form['added'][$module_name] = array(
              '#type' => 'markup',
              '#title' => $module->info['name'],
              '#value' => "<em>". t('This module does not support additional options.') ."</em>",
            );
          }
        }
      }

      // Dependencies
      $form['detected']['dependencies'] = array(
        '#type' => 'markup',
        '#value' => theme('item_list', array_keys($export['dependencies'])),
      );

      $options = array();
      foreach (features_get_modules() as $module_name => $info) {
        if ($info->status && !empty($info->info)) {
          $options[$module_name] = $info->info['name'];
        }
      }
      $options = array_diff_key($options, $export['dependencies']);

      $form['added']['dependencies'] = array(
        '#tree' => TRUE,
        '#title' => t('Module dependencies'),
        '#type' => 'checkboxes',
        '#options' => $options,
      );
      break;

    // Download/export ================================================
    case 3:
      if ($files = features_export_render($export, $module_name, TRUE)) {
        $filename = !empty($export['version']) ? "{$module_name}-{$export['version']}" : $module_name;
        $module_display = function_exists('gzencode') ? "{$filename}.tgz" : "{$filename}.tar";

        $form['module_display'] = array(
          '#type' => 'markup',
          '#value' => "<h3 class='features-download'>{$module_display}</h3>",
        );

        $form['download'] = array('#tree' => TRUE, '#theme' => 'features_form_buttons');
        $form['download']['module_name'] = array('#type' => 'value', '#value' => $module_name);
        $form['download']['filename'] = array('#type' => 'value', '#value' => $filename);
        $form['download']['files'] = array('#type' => 'value', '#value' => $files);

        $form['download']['download'] = array(
          '#type' => 'submit',
          '#value' => t('Download feature'),
          '#submit' => array('features_export_download_submit'),
        );
      }
      break;
  }

  // Add Next/Prev step buttons
  $form['buttons'] = array('#tree' => FALSE, '#theme' => 'features_form_buttons');
  if ($step > 0 && $step != count($steps) - 1) {
    $form['buttons']['prev'] = array('#value' => t('Previous'), '#type' => 'submit');
  }
  if ($step < count($steps) - 1) {
    $form['buttons']['next'] = array('#value' => t('Next'), '#type' => 'submit');
    if (drupal_get_messages('error', FALSE)) {
      $form['buttons']['message'] = array(
        '#type' => 'markup',
        '#value' => "<div class='description'>". t('You should resolve all errors with your feature before continuing.') ."</div>",
      );
    }
  }

  return $form;
}

/**
 * Export form submit handler.
 */
function features_export_form_submit($form, &$form_state) {
  // tell Drupal we are redrawing the same form
  $form_state['rebuild'] = TRUE;

  switch ($form_state['storage']['step']) {

    // Step 0: Store info
    case 0:
      $export = array(
        'name' => $form_state['values']['name'],
        'description' => $form_state['values']['description'],
      );
      if (!empty($form_state['values']['version'])) {
        $export['version'] = $form_state['values']['version'];
      }
      if (!empty($form_state['values']['project_status_url'])) {
        $export['project status url'] = $form_state['values']['project_status_url'];
      }
      $form_state['storage']['export'] = $export;
      $form_state['storage']['module_name'] = $form_state['values']['module_name'];
      break;

    // Step 1: Convert sources into export object
    case 1:
      $module_name = $form_state['storage']['module_name'];
      $export = $form_state['storage']['export'];

      // Retrieve export
      $feature = array();
      foreach (element_children($form['sources']) as $elem) {
        if (!empty($form_state['values']['sources'][$elem])) {
          foreach ($form_state['values']['sources'][$elem] as $identifier => $value) {
            if ($value) {
              $feature[$elem][] = $identifier;
            }
          }
        }
      }

      $export = array_merge($export, features_populate($feature, $module_name));
      $form_state['storage']['export'] = $export;
      break;

    // Step 2: Update export object based on user input
    case 2:
      $module_name = $form_state['storage']['module_name'];
      $export = $form_state['storage']['export'];

      // Update export array based on what's been selected
      foreach ($form_state['values']['added'] as $module_name => $items) {
        foreach ($items as $item => $value) {
          if ($value) {
            $export['features'][$module_name][$item] = $item;
          }
          else if (!empty($export['features'][$module_name][$item])) {
            unset($export['features'][$module_name][$item]);
          }
        }
      }
      // Update dependencies
      if (!empty($form_state['values']['added']['dependencies'])) {
        foreach ($form_state['values']['added']['dependencies'] as $item => $value) {
          if ($value) {
            $export['dependencies'][$item] = $item;
          }
          else if (!empty($export['dependencies'][$item])) {
            unset($export['dependencies'][$item]);
          }
        }
      }

      // Build final export array
      $populated = features_populate($export['features'], $module_name);
      $export['features'] = array_merge($export['features'], $populated['features']);
      $export['dependencies'] = array_merge($export['dependencies'], $populated['dependencies']);
      $export['dependencies'] = _features_export_minimize_dependencies($export['dependencies'], $module_name);

      $form_state['storage']['export'] = $export;
      break;
  }

  // check the button that was clicked and action the step chagne
  if ($form_state['clicked_button']['#id'] == 'edit-prev') {
    $form_state['storage']['step']--;
  }
  elseif ($form_state['clicked_button']['#id'] == 'edit-next') {
    $form_state['storage']['step']++;
  }
}

/**
 * Download submit handler.
 */
function features_export_download_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['download']['files'])) {
    $files = $form_state['values']['download']['files'];
    $module_name = $form_state['values']['download']['module_name'];
    $filename = $form_state['values']['download']['filename'];
    features_export_download_files($files, $module_name, $filename);
  }
}

/**
 * Delivers files to the user through a tarball download.
 */
function features_export_download_files($files, $module_name, $filename = '') {
  $tar = array();
  foreach ($files as $path => $file_contents) {
    $tar["{$module_name}/{$module_name}.$path"] = $file_contents;
  }
  $tar = features_tar_create($tar);

  $header = function_exists('gzencode') ? 'Content-type: application/x-gzip' : 'Content-type: application/x-tar';
  $filename = !empty($filename) ? $filename : $module_name;
  $filename = function_exists('gzencode') ? "{$filename}.tgz" : "{$filename}.tar";

  drupal_set_header($header);
  drupal_set_header('Content-Disposition: attachment; filename="'. $filename .'"');
  print $tar;
  exit;
}

/**
 * @param $items
 * @param $module_name
 * @return
 */
function features_populate($items, $module_name) {
  $stub = array('features' => array(), 'dependencies' => array(), 'conflicts' => array());
  $export = _features_populate($items, $stub, $module_name);
  $export['dependencies'] = _features_export_minimize_dependencies($export['dependencies'], $module_name);
  return $export;
}

/**
 * Iterate and descend into a feature definition to extract module
 * dependencies and feature definition. Calls hook_features_export for modules
 * that implement it.
 *
 * @param $pipe
 *  Associative of array of module => info-for-module
 * @param $export
 *  Associative array of items, and module dependencies which define a feature.
 *  Passed by reference.
 *
 * @return fully populated $export array.
 */
function _features_populate($pipe, &$export, $module_name = '') {
  features_include();
  foreach ($pipe as $module => $data) {
    if (module_hook($module, 'features_export')) {
      $function = "{$module}_features_export";
      // Pass module-specific data and export array (should be done by reference)
      $more = $function($data, $export, $module_name);
      // Allow for export functions to request additional exports.
      if (!empty($more)) {
        _features_populate($more, $export, $module_name);
      }
    }
  }
  return $export;
}

/**
 * Iterates over a list of dependencies and kills modules that are
 * captured by other modules 'higher up'.
 */
function _features_export_minimize_dependencies($dependencies, $module_name = '') {
  // Ensure that the module doesn't depend upon itself
  if (!empty($module_name) && !empty($dependencies[$module_name])) {
    unset($dependencies[$module_name]);
  }
  foreach ($dependencies as $k => $v) {
    if (empty($v)) {
      unset($dependencies[$k]);
    }
    else {
      $module = features_get_modules($v);
      if ($module && !empty($module->info['dependencies'])) {
        // If this dependency depends on the module itself, we have a circular dependency.
        // Don't let it happen. Only you can prevent forest fires.
        if (in_array($module_name, $module->info['dependencies'])) {
          unset($dependencies[$k]);
        }
        // Iterate through the dependency's dependencies and remove any dependencies
        // that are captured by it.
        else {
          foreach ($module->info['dependencies'] as $j => $dependency) {
            if (array_search($dependency, $dependencies) !== FALSE) {
              $position = array_search($dependency, $dependencies);
              unset($dependencies[$position]);
            }
          }
        }
      }
    }
  }
  return $dependencies;
}

/**
 * Iterates over a list of dependencies and maximize the list of modules.
 */
function _features_export_maximize_dependencies($dependencies, $module_name = '', $first = TRUE) {
  $maximized = $dependencies;
  foreach ($dependencies as $k => $v) {
    $module = features_get_modules($v);
    if ($module && !empty($module->info['dependencies'])) {
      $maximized = array_merge($maximized, _features_export_maximize_dependencies($module->info['dependencies'], $module_name, FALSE));
    }
  }
  return array_unique($maximized);
}

/**
 * Render feature export into an array representing its files.
 *
 * @param $export
 *  An exported feature definition.
 * @param $module_name
 *  The name of the module to be exported.
 * @param $reset
 *  Boolean flag for resetting the module cache. Only set to true when
 *  doing a final export for delivery.
 *
 * @return array of info file and module file contents.
 */
function features_export_render($export, $module_name, $reset = FALSE) {
  features_include();

  $code = array();
  $existing = features_get_modules($module_name, $reset);

  // Prepare info string -- if module exists, merge into its existing info file
  $info = $existing ? $existing->info : array('core' => '6.x', 'package' => 'Features', 'project' => $module_name);
  $export = array_merge($info, $export);

  // A couple of special cases.
  if (!empty($export['dependencies'])) {
    $export['dependencies'] = array_values($export['dependencies']);
  }
  if (!empty($export['conflicts'])) {
    unset($export['conflicts']);
  }
  $code['info'] = features_export_info($export);

  // Prepare the defaults & features files
  $code['defaults.inc'] = $code['features.inc'] = array();

  ksort($export['features']);
  foreach ($export['features'] as $module => $data) {
    if (!empty($data)) {
      // Sort the items so that we don't generate different exports based on order
      asort($data);
      if (module_hook($module, 'features_export_render')) {
        $hooks = module_invoke($module, 'features_export_render', $module_name, $data);
        foreach ($hooks as $hook_name => $hook_code) {
          $code['features.inc'][$hook_name] = features_export_render_features($module_name, $hook_name, $hook_code);
          $code['defaults.inc'][$hook_name] = features_export_render_defaults($module_name, $hook_name, $hook_code);
        }
      }
    }
  }
  $code['features.inc'] = implode("\n\n", $code['features.inc']);
  $code['features.inc'] = "<?php\n\n{$code['features.inc']}\n";

  $code['defaults.inc'] = implode("\n\n", $code['defaults.inc']);
  $code['defaults.inc'] = "<?php\n\n{$code['defaults.inc']}\n";

  // Prepare the module
  // If module exists, let it be and include it in the files
  if ($existing) {
    $code['module'] = file_get_contents($existing->filename);
  }
  // Add a stub module to include the defaults
  else {
    $code['module'] = "<?php\n\ninclude_once('{$module_name}.features.inc');\n";
  }
  return $code;
}

/**
 * Detect the difference of a feature.
 */
function features_detect_overrides($module) {
  static $cache;
  if (!isset($cache)) {
    $cache = array();
  }
  if (!isset($cache[$module->name])) {
    // Make necessary inclusions
    if (module_exists('views')) {
      views_include('view');
    }

    // Rebuild feature from .info file description.
    $export = features_populate($module->info['features'], $module->name);

    // Render and run an export of the current state.
    $export = array_merge($export, $module->info);
    $eval_namespace = "_features_comparison_{$module->name}";
    $code = features_export_render($export, $eval_namespace);
    $php = $code['defaults.inc'];
    $php = substr_replace($php, '', strpos($php, "<?php"), 5);

    ob_start();
    eval($php);
    ob_end_clean();

    $overridden = array();

    // Retrieve default hooks & compare against eval'd versions
    $export_functions = features_get_default_hooks();

    // Merge items from both
    $merged = array_merge($export['features'], $module->info['features']);

    foreach ($merged as $i => $data) {
      if (isset($export_functions[$i])) {
        // Call the eval'd function and collect results
        // Use the underscore version of the function name as we don't want
        // to go through module_load_include().
        $fname = "_{$eval_namespace}_{$export_functions[$i]}";
        if (function_exists($fname)) {
          $current[$i] = call_user_func($fname);
        }

        // Call the existing in-code function and collect results
        $fname = $module->name .'_'. $export_functions[$i];
        if (function_exists($fname)) {
          $default[$i] = call_user_func($fname);
        }

        // Compare, and push differences into the overrides array
        if (isset($current[$i])) {
          foreach ($current[$i] as $j => $k) {
            // Special cases for objects -- some (views) provide their own
            // export methods which we need to respect.
            if (is_object($current[$i][$j])) {
              switch (get_class($current[$i][$j])) {
                case 'view':
                  $a = $current[$i][$j]->export();
                  if ($default[$i][$j]) {
                    $b = $default[$i][$j]->export();
                  }
                  break;
                default:
                  $a = features_var_export($current[$i][$j]);
                  $b = features_var_export($default[$i][$j]);
                  break;
              }
              $a = _features_linetrim(explode("\n", $a));
              $b = _features_linetrim(explode("\n", $b));

              $different = $a !== $b;
            }
            else {
              $different = $current[$i][$j] !== $default[$i][$j];
            }
            if ($different) {
              $overridden[$i] = array(
                'default' => $default[$i][$j],
                'current' => $current[$i][$j],
              );
            }
          }
        }
      }
    }
    $cache[$module->name] = $overridden;
  }
  return $cache[$module->name];
}

/**
 * Return an array of default hooks for each implementing module.
 * Currently this limits us to a single item per module.
 * @TODO: consider refactoring to allow more than 1 exportable type for a given module.
 */
function features_get_default_hooks() {
  static $hooks;
  if (!isset($hooks)) {
    $hooks = array();
    features_include();
    foreach (module_implements('features_api') as $module) {
      $info = module_invoke($module, 'features_api');
      if (!empty($info['default_hook'])) {
        $hooks[$module] = $info['default_hook'];
      }
    }
  }
  return $hooks;
}

/**
 * Return a code string representing an implementation of a module hook.
 * Includes the module's defaults .inc and calls the private helper function.
 */
function features_export_render_features($module, $hook, $code) {
  $output = array();
  $output[] = "/**";
  $output[] = " * Implementation of hook_{$hook}().";
  $output[] = " */";
  $output[] = "function {$module}_{$hook}() {";
  $output[] = "  module_load_include('inc', '{$module}', '{$module}.defaults');";
  $output[] = "  return _{$module}_{$hook}();";
  $output[] = "}";
  return implode("\n", $output);
}

/**
 * Return a code string representing an implementation of a defaults module hook.
 */
function features_export_render_defaults($module, $hook, $code) {
  $output = array();
  $output[] = "/**";
  $output[] = " * Helper to implemetation of hook_{$hook}().";
  $output[] = " */";
  $output[] = "function _{$module}_{$hook}() {";
  $output[] = $code;
  $output[] = "}";
  return implode("\n", $output);
}

/**
 * Generate code friendly to the Drupal .info format from a structured array.
 *
 * @param $info
 *   An array of parameters to put in a module's .info file.
 *
 * @return
 *   A code string ready to be written to a module's .info file.
 */
function features_export_info($info) {
  $code = array();
  foreach ($info as $k => $v) {
    if (is_array($v)) {
      $first = array_shift(array_keys($v));
      if (is_numeric($first)) {
        sort($v);
      }
      else {
        ksort($v);
      }

      foreach ($v as $l => $m) {
        if (is_numeric($l)) {
          $key = '';
        }
        else {
          $key = $l;
        }
        if (is_array($m)) {
          sort($m);
          foreach ($m as $n => $o) {
            $code[] = "{$k}[$key][] = \"{$o}\"";
          }
        }
        else {
          $code[] = "{$k}[$key] = \"{$m}\"";
        }
      }
    }
    else {
      $code[] = "{$k} = \"{$v}\"";
    }
  }
  $code = implode("\n", $code) ."\n";
  return $code;
}

/**
 * Tar creation function. Written by dmitrig01.
 *
 * @param $files
 *   A keyed array where the key is the filepath and the value is the
 *   string contents of the file.
 *
 * @return
 *   A string of the tar file contents.
 */
function features_tar_create($files) {
  $tar = '';
  foreach ($files as $name => $contents) {
    $binary_data_first = pack("a100a8a8a8a12A12",
      $name,
      '100644 ', // File permissions
      '   765 ', // UID,
      '   765 ', // GID,
      sprintf("%11s ", decoct(strlen($contents))), // Filesize,
      sprintf("%11s", decoct(time())) // Creation time
    );
    $binary_data_last = pack("a1a100a6a2a32a32a8a8a155a12", '', '', '', '', '', '', '', '', '', '');

    $checksum = 0;
    for ($i = 0; $i < 148; $i++) {
      $checksum += ord(substr($binary_data_first, $i, 1));
    }
    for ($i = 148; $i < 156; $i++) {
      $checksum += ord(' ');
    }
    for ($i = 156, $j = 0; $i < 512; $i++, $j++) {
      $checksum += ord(substr($binary_data_last, $j, 1));
    }

    $tar .= $binary_data_first;
    $tar .= pack("a8", sprintf("%6s ", decoct($checksum)));
    $tar .= $binary_data_last;

    $buffer = str_split($contents, 512);
    foreach ($buffer as $item) {
      $tar .= pack("a512", $item);
    }
  }
  if (function_exists('gzencode')) {
    $tar = gzencode($tar);
  }
  return $tar;
}

/**
 * Export var function -- from Views.
 */
function features_var_export($var, $prefix = '', $init = TRUE) {
  if (is_array($var)) {
    if (empty($var)) {
      $output = 'array()';
    }
    else {
      $output = "array(\n";
      foreach ($var as $key => $value) {
        $output .= "  '$key' => " . features_var_export($value, '  ', FALSE) . ",\n";
      }
      $output .= ')';
    }
  }
  else if (is_bool($var)) {
    $output = $var ? 'TRUE' : 'FALSE';
  }
  else if (is_string($var) && strpos($var, "\n") !== FALSE) {
    // Replace line breaks in strings with a token for replacement
    // at the very end. This protects whitespace in strings from
    // unintentional indentation.
    $var = str_replace("\n", "***BREAK***", $var);
    $output = var_export($var, TRUE);
  }
  else {
    $output = var_export($var, TRUE);
  }

  if ($prefix) {
    $output = str_replace("\n", "\n$prefix", $output);
  }

  if ($init) {
    $output = str_replace("***BREAK***", "\n", $output);
  }

  return $output;
}

/**
 * Helper function to return an array of t()'d translatables strings.
 * Useful for providing a separate array of translatables with your
 * export so that string extractors like potx can detect them.
 */
function features_translatables_export($translatables, $prefix = '') {
  sort($translatables);
  $translatables = array_unique($translatables);

  $output = $prefix . "// Translatables\n";
  $output .= $prefix . "array(\n";
  foreach ($translatables as $string) {
    $output .= $prefix . "  t('" . strtr($string, array("'" => "\'")) . "'),\n";
  }
  $output .= $prefix . ");\n";
  return $output;
}

/**
 * Helper function to eliminate whitespace differences in code.
 */
function _features_linetrim($code) {
  foreach ($code as $k => $line) {
    $code[$k] = trim($line);
  }
  return $code;
}
