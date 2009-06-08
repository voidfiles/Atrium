<?php
// $Id: features.admin.inc,v 1.1.2.15 2009/06/07 15:43:57 yhahn Exp $

/**
 * admin/build/features page callback.
 */
function features_admin_form($feature = NULL) {
  // Load export functions to use in comparison.
  module_load_include('inc', 'features', 'features.export');

  // Clear the module cache
  module_rebuild_cache();
  features_rebuild();

  $form = array('#theme' => 'features_form');

  $form['feature'] =
  $form['links'] =
  $form['version'] =
  $form['weight'] =
  $form['status'] = array(
    '#tree' => TRUE,
  );

  $modules = features_get_modules('', TRUE);

  // Generate features form.
  foreach (features_get_features('', TRUE) as $name => $module) {
    $unmet_dependencies = array();
    if (!empty($module->info['dependencies'])) {
      $dependencies = _features_export_maximize_dependencies($module->info['dependencies']);
      foreach ($dependencies as $dependency) {
        if (empty($modules[$dependency])) {
          $unmet_dependencies[] = theme('features_module_status', FEATURES_MODULE_MISSING, $dependency);
        }
      }
    }

    $form['feature'][$name] = array(
      '#type' => 'value',
      '#value' => $module,
    );

    $form['status'][$name] = array(
      '#type' => 'checkbox',
      '#title' => $module->info['name'],
      '#description' => !empty($unmet_dependencies) ? t('Unmet dependencies: !dependencies', array('!dependencies' => implode(', ', $unmet_dependencies))) : $module->info['description'],
      '#default_value' => $module->status,
      '#disabled' => !empty($unmet_dependencies) ? TRUE : FALSE,
    );

    $uri = !empty($module->info['feature_uri']) ? $module->info['feature_uri'] : t('Unavailable');
    $timestamp = !empty($module->info['feature_timestamp']) ? format_date($module->info['feature_timestamp'], 'small') : '';
    $timestamp = !empty($timestamp) ? "<div class='description'>$timestamp</div>" : '';
    $sign = "$uri $timestamp";

    $form['sign'][$name] = array(
      '#type' => 'markup',
      '#value' => $sign,
    );

    $actions = l(t('View'), "admin/build/features/{$name}");
    $actions .= '<span class="admin-overridden"> | </span>';
    $actions .= l(t('Re-export'), "admin/build/features/{$name}/export", array(
      'attributes' => array('class' => 'admin-overridden')
    ));

    if ($module->status) {
      $state = '<span class="admin-loading">' . t('Checking...') . '</span>';
      $state .= l(t('Check'), "admin/build/features/{$name}/status", array('attributes' => array('class' => 'admin-check')));
      $state .= l(theme('features_storage', FEATURES_OVERRIDDEN), "admin/build/features/{$name}/compare", array(
        'html' => TRUE, 
        'attributes' => array('class' => 'admin-overridden')
      ));
      $state .= theme('features_storage', FEATURES_DEFAULT);
    }
    else {
      $state = t('Disabled');
    }

    $form['state'][$name] = array(
      '#type' => 'markup',
      '#value' => !empty($state) ? $state : '',
    );
    $form['actions'][$name] = array(
      '#type' => 'markup',
      '#value' => !empty($actions) ? $actions : '',
    );
  }

  $form['buttons'] = array(
    '#theme' => 'features_form_buttons',
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
    '#submit' => array('features_form_submit'),
  );
  return $form;
}

/**
 * Display the components of a feature.
 */
function features_admin_components($feature) {
  module_load_include('inc', 'features', 'features.export');
  $conflict = features_detect_overrides($feature);

  // Retrieve basic information
  $info = array();
  $info['name'] = $feature->info['name'];
  $info['description'] = $feature->info['description'];

  // Iterate over dependencies and retrieve status for display
  $dependencies = array();
  if (!empty($feature->info['dependencies'])) {
    foreach ($feature->info['dependencies'] as $dependency) {
      $status = features_get_module_status($dependency);
      $dependencies[$dependency] = $status;
    }
  }

  // Iterate over components and retrieve status for display
  $components = $feature->info['features'];
  $conflicts = array();
  foreach ($feature->info['features'] as $type => $items) {
    if (!empty($conflict[$type])) {
      $conflicts[$type] = l(theme('features_storage', FEATURES_OVERRIDDEN), "admin/build/features/{$feature->name}/compare", array('html' => TRUE));
      unset($conflict[$type]);
    }
    else {
      $conflicts[$type] = theme('features_storage', FEATURES_DEFAULT);
    }
  }
  // There are new additions -- show
  if (!empty($conflict)) {
    foreach ($conflict as $type => $items) {
      // If exportables are standardized with keyed arrays, this would work much better!
      $components[$type] = array();
      $conflicts[$type] = l(theme('features_storage', FEATURES_OVERRIDDEN), "admin/build/features/{$feature->name}/compare", array('html' => TRUE));
    }
  }

  return theme('features_admin_components', $info, $dependencies, $components, $conflicts);
}

/**
 * Submit handler for the 'manage features' form
 */
function features_form_submit(&$form, &$form_state) {
  module_load_include('inc', 'features', 'features.export');

  $features = $form_state['values']['feature'];
  $install = array();
  $disable = array();
  if (!empty($features)) {
    foreach ($features as $name => $feature) {
      // Enable feature
      if ($form_state['values']['status'][$name] && !module_exists($name)) {
        if (!empty($feature->info['dependencies'])) {
          $dependencies = _features_export_maximize_dependencies($feature->info['dependencies']);
          foreach ($dependencies as $dependency) {
            if (!module_exists($dependency)) {
              $install[] = $dependency;
            }
          }
        }
        $install[] = $name;
      }
      // Disable feature
      else if (!$form_state['values']['status'][$name] && module_exists($name)) {
        $disable[] = $name;
      }
    }

    if (!empty($install)) {
      $install = array_unique($install);
      module_enable($install);

      // Make sure the install API is available.
      include_once './includes/install.inc';
      drupal_install_modules($install);
    }
    if (!empty($disable)) {
      module_disable($disable);
    }
  }

  drupal_flush_all_caches();
}

/**
 * Page callback to display the differences between what's in code and
 * what is in the db.
 *
 * @param $module
 *  The name of the feature module to check display differences for.
 *
 * @return Themed display of what is different.
 */
function features_feature_comparison($feature) {
  drupal_add_css(drupal_get_path('module', 'features') .'/features.css');
  module_load_include('inc', 'features', 'features.export');

  $conflict = features_detect_overrides($feature);

  // There are differences
  if (!empty($conflict)) {
    // Diff is installed
    if (module_exists('diff')) {
      module_load_include('php', 'diff', 'DiffEngine');
      $formatter = new DrupalDiffFormatter();
      foreach ($conflict as $k => $v) {
        if (module_exists('diff')) {
          if (is_object($v['default']) && get_class($v['default']) == 'view' ){
            $old = $v['default']->export();
            $new = $v['current']->export();
          }
          else {
            $old = features_var_export($v['default']);
            $new = features_var_export($v['current']);
          }
          // Eliminate whitespace differences
          $old = _features_linetrim(explode("\n", $old));
          $new = _features_linetrim(explode("\n", $new));

          $diff = new Diff($old, $new);
          $output .= '<h3>' . $k . '</h3>';
          $output .= theme('diff_table', array(t('Default'), '', t('Current'), ''), $formatter->format($diff), array('class' => 'diff'));
        }
        else {
          $items[] = $k;
        }
      }
    }
    // Diff is not installed
    else {
      $output = "<div class='features-empty'>". t('Please install the diff module to view changes.') ."</div>";
    }
  }
  // No changes
  else {
    $output = "<div class='features-empty'>". t('No changes have been made to this feature.') ."</div>";
  }
  $output = "<div class='features-comparison'>{$output}</div>";
  return $output;
}

/**
 * Javascript call back that returns the status of a feature.
 */
function features_feature_status($feature) {
  module_load_include('inc', 'features', 'features.export');
  $storage = count(features_detect_overrides($feature)) ? FEATURES_OVERRIDDEN : FEATURES_DEFAULT;
  return drupal_json(array('status' => $storage));
}