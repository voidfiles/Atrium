<?php

/**
 * Maintenance API ====================================================
 */

/**
 * Implementation of hook_atrium_admin().
 */
function atrium_atrium_admin() {
  return array(
    'atrium_update_permissions' => t('Permissions'),
    'atrium_update_filter' => t('Input filter formats'),
  );
}

/**
 * API function for updating the permissions of an Atrium install.
 */
function atrium_update_permissions() {
  $modules = module_implements('atrium_permissions');
  if (empty($modules)) {
    drupal_set_message(t('No modules were found that implement a permission map.'), 'error');
    return FALSE;
  }
  else if (count($modules) > 1) {
    drupal_set_message(t('More than 1 module implements a permission map.'), 'error');
    return FALSE;
  }

  $module = array_shift($modules);
  $permissions = module_invoke($module, 'atrium_permissions');

  if (!empty($permissions)) {
    foreach ($permissions as $role_name => $perms) {
      $rid = db_result(db_query("SELECT rid FROM {role} WHERE name ='%s'", $role_name));
      if ($rid) {
        db_query("UPDATE permission SET perm = '' WHERE rid = %d", $rid);
      }
      else {
        $role = array('name' => $role_name);
        drupal_write_record('role', $role);
        $rid = $role['rid'];
      }
      db_query("DELETE FROM {permission} WHERE rid = %d", $rid);
      $perms = array(
        'rid' => $rid,
        'perm' => implode(', ', $perms),
      );
      drupal_write_record('permission', $perms);
    }
    drupal_set_message(t('The permissions for this instance of Atrium have been updated. Permission map used: <strong>!module</strong>.', array('!module' => $module)));
    return TRUE;
  }
  drupal_set_message(t('There was an error maintaining the permissions of this instance of Atrium.'), 'error');
  return FALSE;
}

/**
 * API function for maintaining input filter formats.
 * Will wipe and replace any filter formats defined by the subprofile.
 * Leaves all other filter formats alone.
 */
function atrium_update_filter() {
  $modules = module_implements('atrium_filter');
  if (empty($modules)) {
    drupal_set_message(t('No modules were found that implement a permission map.'), 'error');
    return FALSE;
  }
  else if (count($modules) > 1) {
    drupal_set_message(t('More than 1 module implements a permission map.'), 'error');
    return FALSE;
  }

  $module = array_shift($modules);
  $filter = module_invoke($module, 'atrium_filter');

  if (!empty($filter)) {
    foreach ($filter as $info) {
      // Update or insert the format
      $format = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = '%s'", $info['format']['name']));
      if ($format) {
        $info['format']['format'] = $format;
        drupal_write_record('filter_formats', $info['format'], 'format');
      }
      else {
        drupal_write_record('filter_formats', $info['format']);
      }

      // Update the filters for the format
      if ($info['format']['format']) {
        db_query("DELETE FROM {filters} WHERE format = %d", $info['format']['format']);
        foreach ($info['filters'] as $filter) {
          $filter['format'] = $info['format']['format'];
          drupal_write_record('filters', $filter);
        }
      }
    }
    drupal_set_message(t('The filter formats this instance of Atrium have been updated. Filter formats used: <strong>!module</strong>.', array('!module' => $module)));
  }
}

/**
 * Administration =====================================================
 */

/**
 * 8 atrium maintenance form.
 */
function atrium_admin() {

  drupal_set_title(t('Maintenance'));
  context_set('atrium', 'section', 'admin');
  $form = array();

  $script_options = module_invoke_all('atrium_admin');
  $form['updates'] = array(
    '#type' => 'fieldset',
    '#title' => t('Updates'),
    '#description' => t('Run the selected scripts to ensure your site is up to date.'),
  );
  $form['updates']['scripts'] = array(
    '#type' => 'checkboxes',
    '#options' => $script_options,
    '#default_value' => array_keys($script_options),
  );
  $form['updates']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#submit' => array('atrium_admin_submit_updates'),
  );

  $form['cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Clear caches'),
    '#description' => t('When your site has been updated you may need to clear Drupal\'s caches.'),
  );
  $form['cache']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Clear all caches'),
    '#submit' => array('atrium_admin_clear_caches'),
  );

  $form['atrium_admin_mode'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show all administration pages'),
    '#description' => t('Enable this to access all of Drupal\'s administration pages.'),
    '#default_value' => variable_get('atrium_admin_mode', FALSE),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Submit handler for atrium_admin form.
 */
function atrium_admin_submit(&$form, &$form_state) {
  // Save admin mode variable and rebuild menu cache if mode changes.
  $old = variable_get('atrium_admin_mode', FALSE);
  variable_set('atrium_admin_mode', $form_state['values']['atrium_admin_mode']);
  if ($old != $form_state['values']['atrium_admin_mode']) {
    menu_rebuild();
  }
}

/**
 * 8 atrium update script submit handler.
 */
function atrium_admin_submit_updates($form, &$form_state) {
  foreach ($form_state['values']['scripts'] as $script => $enabled) {
    if ($enabled && function_exists($script)) {
      $script();
      // Allow modules to run post-script cleanup.
      module_invoke_all('atrium_post_admin', $script);
    }
  }
}

/**
 * 8 atrium admin script to clear all caches.
 */
function atrium_admin_clear_caches($form, &$form_state) {
  drupal_flush_all_caches();

  views_invalidate_cache();
  cache_clear_all('schema', 'cache');
  _block_rehash();
  drupal_set_message(t('All site caches have been cleared'));
}
