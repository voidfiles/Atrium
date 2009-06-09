<?php
// $Id: purl.admin.inc,v 1.1.2.2 2009/05/14 03:58:13 yhahn Exp $
/**
 * @file
 *
 * Admin pages for the purl module.
 */

/**
 * Page callback for the purl administration page.
 */
function purl_admin() {
  global $pager_page_array, $pager_total, $pager_total_items;
  $page = isset($_GET['page']) ? $_GET['page'] : 0;
  $element = 0;
  $limit = 20;
  $providers = purl_providers();

  // Convert $page to an array, used by other functions.
  $pager_page_array = array($page);

  $methods = _purl_options();

  $merged = array();
  foreach(array_keys($methods) as $method) {
    foreach(purl_modifiers($method) as $value => $info) {
      $info['value'] = $value;
      $merged[] = $info;
    }
  }

  $rows = array();
  for ($i = $page * $limit; $i < ($page+1) * $limit && $i < count($merged); $i++) {
    $rows[] = array(
      $providers[$merged[$i]['provider']]['name'],
      $merged[$i]['value'],
      $merged[$i]['id'],
      $methods[variable_get('purl_method_'. $merged[$i]['provider'], PURL_PATH)],
    );
  }

  // We calculate the total of pages as ceil(items / limit).
  $pager_total_items[$element] = count($merged);
  $pager_total[$element] = ceil($pager_total_items[$element] / $limit);
  $pager_page_array[$element] = max(0, min((int)$pager_page_array[$element], ((int)$pager_total[$element]) - 1));

  if ($rows) {
    $output = theme('table', array(t('Provider'), t('Modifier'), t('ID'), t('Method')), $rows);
    $output .= theme('pager');
  }
  else {
    $output = "<p>". t('No persistent urls have been registered.') ."</p>";
  }
  return $output;
}

/**
 * Settings form for choosing the operating mode of purl
 */
function purl_settings_form() {
  global $base_url;
  $form = array();

  $options = _purl_options();

  foreach (purl_providers() as $id => $provider) {
    // Check to see whether provider has limited the available valueing methods
    if (isset($provider['methods']) && count($provider['methods'])) {
      $provider_options = array();
      foreach ($provider['methods'] as $method) {
        $provider_options[$method] = $options[$method];
      }
    }
    else {
      $provider_options = $options;
    }

    $form[$id] = array(
      '#fieldset' => true,
      '#provider' => true,
      '#title' => $provider['name'],
      '#description' => $provider['description'],
    );
    $form[$id]['purl_method_'. $id] = array(
      '#title' => t('Method'),
      '#type' => 'select',
      '#options' => $provider_options,
      '#default_value' => variable_get('purl_method_'. $id, PURL_PATH),
    );
    $form[$id]['purl_method_'. $id .'_key'] = array(
      '#title' => t('Key'),
      '#type' => 'textfield',
      '#size' => 12,
      '#default_value' => variable_get('purl_method_'. $id .'_key', ''),
    );
  }

  if (!empty($options[PURL_DOMAIN]) || !empty($options[PURL_SUBDOMAIN])) {
    $form['purl_location'] = array(
      '#type' => 'fieldset',
    );
    $form['purl_location']['purl_base_domain'] = array(
      '#type' => 'textfield',
      '#title' => t('Default domain'),
      '#description' => t('Enter the default domain if you are using domain modifiers.'),
      '#required' => FALSE,
      '#default_value' => variable_get('purl_base_domain', $base_url),
    );
  }

  $form = system_settings_form($form);
  $form['#theme'] = 'purl_settings_form';
  return $form;
}

/**
 * Theme function for purl_settings_form()
 */
function theme_purl_settings_form($form) {
  $output = '';
  $rows = array();
  foreach (element_children($form) as $id) {
    $row = array();
    if (isset($form[$id]['#provider'])) {
      $name = $form[$id]['#title'];
      $description = $form[$id]['#description'];
      unset($form[$id]['#title']);
      unset($form[$id]['#description']);
      $row[] = "<strong>$name</strong><div class='description'>$description</div>";

      $cell = '';
      foreach (element_children($form[$id]) as $item) {
        unset($form[$id][$item]['#title']);
        $cell .= drupal_render($form[$id][$item]);
      }
      $row[] = $cell;
    }
    $rows[] = $row;
  }
  $output .= theme('table', array(t('Provider'), t('Modifier type')), $rows);
  $output .= drupal_render($form);
  drupal_add_js(drupal_get_path("module", "purl") ."/purl.admin.js");
  return $output;
}

/**
 * Allow administrators to enable purl methods.
 */
function purl_types_form() {
  $form = array();
  $form['purl_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Types'),
    '#options' => _purl_options(false),
    '#default_value' => variable_get('purl_types', array(PURL_PATH)),
    '#description' => t('Enabled URL modification types.'),
  );
  return system_settings_form($form);
}