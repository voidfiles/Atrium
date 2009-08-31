<?php
// $Id: flot_views_plugin_summary_style.inc,v 1.1.2.1 2009/05/07 20:10:33 yhahn Exp $

/**
 * Summary style plugin for flot.
 */
class flot_views_plugin_summary_style extends views_plugin_style_summary {
  function option_definition() {
    $options = parent::option_definition();
    $options['type'] = array('default' => 'line');
    $options['size'] = array('default' => '400x200');
    $options['xaxis'] = array('default' => 'auto');
    $options['yaxis'] = array('default' => 'auto');
    $options['reverse'] = array('default' => '1');
    $options['pad_y'] = array('default' => '1');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    // parent::options_form($form, $form_state);

    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Graph type'),
      '#options' => array('line' => t('Line'), 'bar' => t('Bar'), 'point' => t('Point')),
      '#description' => t("Choose the type of chart you would like to display."),
      '#default_value' => $this->options['type'],
    );

    $form['size'] = array(
      '#type' => 'textfield',
      '#title' => t('Size'),
      '#description' => t("Enter the dimensions for the chart. Format: WIDTHxHEIGHT (e.g. 200x100)"),
      '#default_value' => $this->options['size'],
    );

    $yaxis_options =
    $xaxis_options = array(
      'auto' => t('Auto generate'),
      'endpoints' => t('Endpoints only'),
    );
    for ($i = 3; $i < 10; $i++) {
      $yaxis_options[$i] = t('Granularity: !count ticks', array('!count' => $i));
    }
    $form['xaxis'] = array(
      '#type' => 'select',
      '#options'=> $xaxis_options,
      '#title' => t('X Axis'),
      '#default_value' => $this->options['xaxis'],
    );

    $form['yaxis'] = array(
      '#type' => 'select',
      '#options'=> $yaxis_options,
      '#title' => t('Y Axis'),
      '#default_value' => $this->options['yaxis'],
    );

    $form['reverse'] = array(
      '#type' => 'checkbox',
      '#title' => t('Reverse data series'),
      '#default_value' => $this->options['reverse'],
    );

    $form['pad_y'] = array(
      '#type' => 'checkbox',
      '#title' => t('Pad Y axis'),
      '#description' => t('Add some breathing room to Y Axis and bottom out baseline at 0'),
      '#default_value' => $this->options['pad_y'],
    );
  }
}
