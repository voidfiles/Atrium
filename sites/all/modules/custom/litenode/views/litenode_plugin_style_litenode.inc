<?php
// $Id$
/**
 * @file
 * Contains the litenode style plugin.
 */

/**
 * Style plugin to render each item in an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class litenode_plugin_style_litenode extends views_plugin_style {
  
  function uses_fields() {
    return TRUE;
  }

  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['modules'] = array('default' => array('node' => 1, 'user' => 1));
    $options['teaser'] = array('default' => TRUE);
    $options['cullen'] = array('default' => TRUE);
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['modules'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Modules'),
      '#description' => t('Enable support for the following modules'),
    );

    foreach (module_invoke_all('litenode') as $module => $info) {
      if (empty($info['required'])) {
        $form['modules'][$module] = array(
          '#type' => 'checkbox',
          '#title' => $info['module'],
          '#default_value' => !empty($this->options['modules'][$module]) ? TRUE : FALSE,
        );
      }
      else {
        $form['modules'][$module] = array(
          '#type' => 'checkbox',
          '#title' => $info['module'],
          '#default_value' => TRUE,
          '#value' => TRUE,
          '#disabled' => TRUE,
        );
      }
    }

    $form['teaser'] = array(
      '#type' => 'radios',
      '#title' => t('View type'),
      '#options' => array(TRUE => t('Teaser'), FALSE => t('Full view')),
      '#default_value' => $this->options['teaser'],
    );

    $form['cullen'] = array(
      '#type' => 'checkbox',
      '#title' => t('Cullen query'),
      '#description' => t('Use the Cullen subselect method for improving query performance. (May break your view! Test thoroughly.)'),
      '#default_value' => $this->options['cullen'],
    );
  }
}
