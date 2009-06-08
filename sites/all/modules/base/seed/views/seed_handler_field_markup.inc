<?php
class seed_handler_field_markup extends views_handler_field_markup {
  function option_definition() {
    $options = parent::option_definition();
    $options['truncate'] = array('default' => 0);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['truncate'] = array(
      '#type' => 'textfield',
      '#title' => t('Text length (in characters)'),
      '#size' => 4,
      '#description' => t('Enter 0 or leave blank to use full text. Truncating strings will have their HTML formatting stripped.'),
      '#default_value' => isset($this->options['truncate']) ? $this->options['truncate'] : '',
    );
  }

  function render($values) {
    $value = $values->{$this->field_alias};
    $format = is_numeric($this->format) ? $this->format : $values->{$this->aliases['format']};
    $output = check_markup($value, $format, FALSE);
    if (!empty($this->options['truncate']) && is_numeric($this->options['truncate'])) {
      $output = strip_tags($output);
      $output = truncate_utf8($output, $this->options['truncate'], true, true);
    }
    return $output;
  }

}
