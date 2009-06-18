<?php

/**
 * Administration =====================================================
 */

/**
 * Atrium maintenance form.
 */
function atrium_admin() {

  drupal_set_title(t('Maintenance'));
  context_set('atrium', 'section', 'admin');
  $form = array();

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
 * Atrium admin script to clear all caches.
 */
function atrium_admin_clear_caches($form, &$form_state) {
  drupal_flush_all_caches();

  views_invalidate_cache();
  cache_clear_all('schema', 'cache');
  _block_rehash();
  drupal_set_message(t('All site caches have been cleared'));
}
