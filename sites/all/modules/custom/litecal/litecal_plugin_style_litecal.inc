<?php
/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render each item in an ordered or unordered list.
 *
 * @ingroup views_style_plugins
 */
class litecal_plugin_style_litecal extends views_plugin_style {
  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['style'] = array('default' => 'full');
    $options['colorby'] = array('default' => 0);
    $options['quickadd'] = array('default' => 0);
    return $options;
  }

  /**
   * Extend the options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Style types
    $options = array(
      'full' => t('Full calendar'),
      'compact' => t('Compact calendar'),
    );
    $form['style'] = array(
      '#title' => t('Display style'),
      '#description' => t('Choose the display style for this litecal.'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $this->options['style'],
    );

    // Style types
    $fields = array(0 => '<'. t('None') .'>');
    foreach ($this->view->display_handler->get_option('fields') as $field => $definition) {
      $fields[$field] = !empty($definition['label']) ? $definition['label'] : $field;
    }
    $form['colorby'] = array(
      '#title' => t('Color by'),
      '#description' => t('Choose a field to be used for coloring items.'),
      '#type' => 'select',
      '#options' => $fields,
      '#default_value' => $this->options['colorby'],
    );    

    // Quick add type
    if (module_exists('prepopulate')) {
      $nodetypes = node_get_types();
      $options = array(0 => '---'. t('Disabled') .'---');
      foreach (content_types() as $type => $info) {
        foreach ($info['fields'] as $field) {
          if ($field['type'] == 'date') {
            $options["{$field['type_name']}:{$field['field_name']}"] = check_plain($nodetypes[$field['type_name']]->name);
          }
        }
      }
      $form['quickadd'] = array(
        '#title' => t('Quickadd type'),
        '#description' => t('Choose the content type to use for quick event add links.'),
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $this->options['quickadd'],
      );
    }
  }

  /**
   * Validate options.
   */
  function options_validate(&$form, &$form_state) {
    $valid = FALSE;

    // Find argument handler
    $arguments = $this->view->display_handler->get_option('arguments');
    foreach ($arguments as $id => $handler) {
      if ($id == 'date_argument') {
        $valid = TRUE;
        break;
      }
    }

    if (!$valid) {
      drupal_set_message(t('The litecal style requires you to add a <strong>Date argument</strong> to your view.'), 'error');
    }
  }
}
