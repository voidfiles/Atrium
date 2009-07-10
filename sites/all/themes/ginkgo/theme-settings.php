<?php
// $Id$

/**
 * Implementation of hook_settings() for themes.
 */
function ginkgo_settings($settings) {
  // Add js & css
  drupal_add_css('misc/farbtastic/farbtastic.css', 'module', 'all', FALSE);
  drupal_add_js('misc/farbtastic/farbtastic.js');
  drupal_add_css(drupal_get_path('theme', 'ginkgo') .'/settings.css');
  drupal_add_js(drupal_get_path('theme', 'ginkgo') .'/js/settings.js');

  $form = array();
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Settings'),
  );
  $form['settings']['emblem'] = array(
    '#title' => t('Show site emblem'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['emblem']) ? $settings['emblem'] : 1,
  );

  $form['messages'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Autoclose messages'),
    '#descriptions' => t('Select the message types to close automatically after a few seconds.'),
  );
  $form['messages']['autoclose'] = array(
    '#type' => 'checkboxes',
    '#options' => array('status' => t('Status'), 'warning' => t('Warning'), 'error' => t('Error')),
    '#default_value' => !empty($settings['autoclose']) ? $settings['autoclose'] : array('status'),
  );

  $form['color'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Color'),
    '#value' => "<div class='description'>". t('These color settings can be overridden by color customizations per space.') ."</div>",
  );
  $form['color']['color_site'] = array(
    '#title' => t('Default site color'),
    '#type' => 'textfield',
    '#size' => '7',
    '#maxlength' => '7',
    '#default_value' => !empty($settings['color_site']) ? $settings['color_site'] : '',
    '#suffix' => '<div class="colorpicker" id="edit-color-site-colorpicker"></div>',
    '#attributes' => array('class' => 'colorpicker'),
  );
  $form['color']['color_og'] = array(
    '#title' => t('Default group color'),
    '#type' => 'textfield',
    '#size' => '7',
    '#maxlength' => '7',
    '#default_value' => !empty($settings['color_og']) ? $settings['color_og'] : '',
    '#suffix' => '<div class="colorpicker" id="edit-color-og-colorpicker"></div>',
    '#attributes' => array('class' => 'colorpicker'),
  );
  $form['color']['color_user'] = array(
    '#title' => t('Default profile color'),
    '#type' => 'textfield',
    '#size' => '7',
    '#maxlength' => '7',
    '#default_value' => !empty($settings['color_user']) ? $settings['color_user'] : '',
    '#suffix' => '<div class="colorpicker" id="edit-color-user-colorpicker"></div>',
    '#attributes' => array('class' => 'colorpicker'),
  );
  return $form;
}
