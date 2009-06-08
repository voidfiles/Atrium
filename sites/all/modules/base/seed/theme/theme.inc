<?php

/**
 * Implementation of hook_theme_registry_alter().
 */
function seed_theme_registry_alter(&$theme_registry) {
  $path = drupal_get_path('module', 'seed');
  foreach ($theme_registry as $hook => $data) {
    switch ($hook) {
      // Hijack functions
      case 'upload_attachments':
      case 'filter_tips_more_info':
        if (!isset($theme_registry[$hook]['type']) || !in_array($theme_registry[$hook]['type'], array('base_theme_engine', 'theme_engine'))) {
          $theme_registry[$hook]['function'] = 'seed_'. $hook;
        }
        break;
      // Hijack preprocess / templates
      case 'node_form':
      case 'user_picture':
      case 'views_ui_list_views':
      case 'views_view_summary':
        unset($theme_registry[$hook]['file']);
        unset($theme_registry[$hook]['function']);
        if (!isset($theme_registry[$hook]['path'])) {
          $theme_registry[$hook]['path'] = "$path/theme";
        }
        else {
          array_unshift($theme_registry[$hook]['theme paths'], "$path/theme");
        }
        $theme_registry[$hook]['template'] = $hook;

        // For a select few, disable theme-level overriding
        switch ($hook) {
          case 'views_ui_list_views':
          case 'views_view_summary':
            $theme_registry[$hook]['path'] = "$path/theme";
            $theme_registry[$hook]['template'] = $hook;
            break;
        }
        break;
    }
  }
}

/**
 * Implementation of hook_theme().
 */
function seed_theme() {
  $path = drupal_get_path('module', 'seed');
  $items = array(
    'seed_audio' => array(),
    'seed_thickbox' => array(),

    'seed_byline' => array(),

    'seed_crayon' => array(),
    'seed_crayon_popup' => array(),
    'seed_crayon_swatch' => array(),

    'seed_taxonomy_split' => array('sorted_terms' => array()),

    'seed_filter_form' => array(),

    'user_profile_form' => array(
      'arguments' => array('form' => array()),
      'template' => 'node_form',
      'path' => "$path/theme",
    ),
    'user_login' => array(
      'arguments' => array('form' => array()),
      'template' => 'user_form',
      'path' => "$path/theme",
    ),
    'user_pass' => array(
      'arguments' => array('form' => array()),
      'template' => 'user_form',
      'path' => "$path/theme",
    ),

    'seed_term_list' => array(),
    'seed_numbered_element' => array(),
    'seed_taxonomy_display_form' => array(),
  );
  if (module_exists('content')) {
    $cckpath = drupal_get_path('module', 'content');
    $items['seed_faux_field'] = array(
      'arguments' => array('element' => NULL),
      'template' => 'content-field',
      'path' => "$cckpath/theme",
    );
  }
  return $items;
}

/**
 * API FUNCTIONS ======================================================
 */

/**
 * Custom date formatter which tries to provide the most easily
 * understood date format given the date's proximity to the current time.
 */
function seed_rel_date($timestamp) {
  $now = time();
  $day = format_date($timestamp, 'custom', 'MjY');

  // Some callback / data abstraction to make things shorter.
  $callback = module_exists('date_api') ? 'date_format_date' : 'format_date';
  $date = module_exists('date_api') ? date_make_date($timestamp, NULL, DATE_UNIX) : $timestamp;

  if ($day == format_date($now, 'custom', 'MjY')) {
    $format = variable_get('date_format_time', 'g:ia');
    $formatted = call_user_func($callback, $date, 'custom', $format);
    return t('!time Today', array('!time' => $formatted));
  }
  else if ($day == format_date($now - (24*60*60), 'custom', 'MjY')) {
    $format = variable_get('date_format_time', 'g:ia');
    $formatted = call_user_func($callback, $date, 'custom', $format);
    return t('!time Yesterday', array('!time' => $formatted));
  }
  // 30 days
  else if ($now - $timestamp <= 3600 * 24 * 30) {
    $format = variable_get('date_format_month_within', 'g:ia D M j');
    return call_user_func($callback, $date, 'custom', $format);
  }
  else {
    $format = variable_get('date_format_month_after', 'g:ia M j, Y');
    return call_user_func($callback, $date, 'custom', $format);
  }
}

/**
 * Turn string into CSS id/class -- from Zen theme
 */ 
function seed_id_safe($string) {
  if (is_numeric($string{0})) {
    // if the first character is numeric, add 'n' in front
    $string = 'n'. $string;
  }
  return strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', $string));
}

/**
 * Groups taxonomy terms by their vocabulary
 * @param $taxonomy: Array of taxonomy terms to sort
 * @return $sorted_terms: Array of sorted taxonomy terms
 */
function seed_taxonomy_split($taxonomy) {
  $sorted_terms = array();
  foreach ($taxonomy as $term) {
    if(array_key_exists($term->vid, $sorted_terms)) {
      array_push($sorted_terms[$term->vid], $term);
    }
    else {
      $sorted_terms[$term->vid] = array($term);
    }
  }
  return $sorted_terms;
}

/**
 * PREPROCESS =========================================================
 */

/**
 * Implementation of hook_preprocess_views_view_summary().
 */
function seed_preprocess_views_view_summary(&$vars) {
  if (count($vars['rows']) > 8) {
    $form = drupal_get_form('seed_views_view_summary_form', $vars['rows']);
    $vars['form'] = $form;
  }
}

/**
 * Form for handling archive override.
 */
function seed_views_view_summary_form(&$form, $rows) {  
  $form = array();
  $options = array(0 => '----');
  $base = base_path();
  foreach ($rows as $row) {
    $url = substr($row->url, strlen($base));
    $options[$url] = t('!date (!count)', array('!date' => $row->link, '!count' => $row->count));
  }
  $form['summary'] = array(
    '#type' => 'select',
    '#options' => $options,
  );
  $form['submit'] = array(
    '#submit' => array('seed_views_view_summary_form_submit'),
    '#type' => 'submit',
    '#value' => t('Go'),
  );
  return $form;
}

/**
 * Submit handler for summary form.
 */
function seed_views_view_summary_form_submit($form, &$form_state) {
  $url = $form_state['values']['summary'];
  if ($url != 0) {
    drupal_goto($url);
  }
}

/**
 * Implementation of hook_preprocess_node_form().
 */
function seed_preprocess_node_form(&$vars) {
  $form = $vars['form'];

  context_set('theme', 'layout', 'wide');

  $vars['type'] = $form['#node']->type ? $form['#node']->type : '';

  // Move form elements to the sidebar if their name starts with sidebar.
  foreach ($form as $k => $elem) {
    if (strpos($k, 'group_sidebar') === 0) {
      $vars['sidebar'][$k] = $form[$k];
      unset($form[$k]);
    }
  }

  foreach (array('i18n', 'spaces_og') as $key) {
    if (isset($form[$key])) {
      $vars['sidebar'][$key] = $form[$key];
      unset($form[$key]);
    }
  }

  foreach (array('taxonomy', 'options') as $key) {
    if (isset($form[$key])) {
      $form[$key]['#collapsible'] = false;
      $vars['sidebar'][$key] = $form[$key];
      unset($form[$key]);
    }
  }

  foreach (array('comment_settings', 'author', 'path', 'menu', 'revision_information') as $key) {
    if (isset($form[$key])) {
      $vars['sidebar'][$key] = $form[$key];
      unset($form[$key]);
    }
  }

  $vars['buttons'] = $form['buttons'];
  unset($form['buttons']);  

  $vars['form'] = $form;
  $vars['form_classes'] = !empty($vars['sidebar']) ? 'form-sidebar' : '';
}

/**
 * Implementation of hook_preprocess_user_profile_form().
 */
function seed_preprocess_user_profile_form(&$vars) {
  $vars['#form'] = $vars['form']; // Preserve form for other preprocesses down the line.
  $form = $vars['form'];

  context_set('theme', 'layout', 'wide');

  // Move picture + messaging to sidebar
  foreach (array('picture', 'messaging') as $key) {
    $vars['sidebar'][$key] = $form[$key];
    unset($form[$key]);
  }

  // Move user status + roles into sidebar fieldset
  if (isset($form['account']['status'])) {
    $status = array(
      '#type' => 'fieldset',
      '#title' => t('User administration'),
    );
    $status['#children'] = drupal_render($form['account']['status']);
    $status['#children'] .= drupal_render($form['account']['roles']);
    $vars['sidebar']['user_admin'] = $status;
  }

  // Hide theme settings
  $vars['hidden']['theme_select'] = $form['theme_select'];

  foreach ($form as $id => $element) {
    if (!empty($element['#type']) && in_array($element['#type'], array('submit', 'button'))) {
      $vars['buttons'][] = $form[$id];
      unset($form[$id]);
    }
  }

  $vars['form'] = $form;
  $vars['form_classes'] = !empty($vars['sidebar']) ? 'form-sidebar' : '';
}

/**
 * Implementation of hook_preprocess_user_login().
 */
function seed_preprocess_user_login(&$vars) {
  $vars['buttons'] = $vars['form']['submit'];
  unset($vars['form']['submit']);
}

/**
 * Implementation of hook_preprocess_user_pass().
 */
function seed_preprocess_user_pass(&$vars) {
  $vars['buttons'] = $vars['form']['submit'];
  unset($vars['form']['submit']);
}

/**
 * Implementation of hook_preprocess_user_picture().
 */
function seed_preprocess_user_picture(&$vars) {
  $account = $vars['account'];
  if (isset($account->picture) && module_exists('imagecache')) {
    $attr = array('class' => 'user-picture');
    $preset = variable_get('seed_imagecache_user_picture', '30x30_crop');
    $attr['class'] .= ' picture-'. $preset;
    if (file_exists($account->picture)) {
      $image = imagecache_create_url($preset, $account->picture);
      $attr['style'] = 'background-image: url('. $image .')';
    }
    $path = 'user/'. $account->uid;
    $vars['picture'] = l($account->name, $path, array('attributes' => $attr));
    $vars['preset'] = $preset;
  }
}

function seed_preprocess_views_ui_list_views(&$vars) {
}

function template_preprocess_seed_faux_field(&$vars) {
  $vars = array_merge($vars, $vars['element']);
  unset($vars['element']);
}

/**
 * FUNCTION OVERRIDES =================================================
 */

/**
 * Helper function to number a form tree intelligently.
 */
function seed_number_form($form) {
  // Element numbering loop
  $output = '';
  foreach (element_children($form) as $element) {
    if (seed_is_empty($form[$element])) {
      $output .= drupal_render($form[$element]);
    }
    else {
      $output .= theme('seed_numbered_element', drupal_render($form[$element]));
    }
  }
  return $output;
}

/**
 * Helper function to recurse down a FAPI element and determine whether
 * it has any visible elements to the user.
 */
function seed_is_empty($form) {
  $empty = TRUE;
  if (empty($form['#type'])) {
    foreach (element_children($form) as $e) {
      $empty = $empty && seed_is_empty($form[$e]);
    }
  }
  else if (!in_array($form['#type'], array('value', 'hidden', 'token'))) {
    $empty = FALSE;
  }
  return $empty;
}

/**
 * Theme function to add numbering markup to form elements.
 */
function theme_seed_numbered_element($markup) {
  drupal_add_css(drupal_get_path('module', 'seed') .'/theme/seed.css');
  static $counter;
  $output = '';
  if (!empty($markup)) {
    if (!isset($counter)) {
      $counter = 1;
    }
    $output .= "<div class='form-item-counter'><span class='counter'>$counter</span>$markup</div>";
    $counter++;
  }
  return $output;
}

/**
 * Theme a filter form element
 */
function theme_seed_filter_form($form) {
  drupal_add_css(drupal_get_path('module', 'seed') .'/theme/seed.css');
  unset($form['#title']);
  if (!empty($form['#options'])) {
    $select = theme('select', $form);
  }
  $help = theme('filter_tips_more_info');
  $output = "<div class='filter-options clear-block'>{$select} {$help}</div>";
  return $output;
}

/**
 * Override of theme_filter_tips_more_info().
 */
function seed_filter_tips_more_info() {
  return '<div class="filter-help">'. l(t('Formatting help'), 'filter/tips', array('attributes' => array('target' => '_blank'))) .'</div>';
}

/**
 * Theme a links array into a comma-separated term list.
 */
function theme_seed_term_list($links = array()) {
  $list = array();
  foreach ($links as $link) {
    $list[] = l($link['title'], $link['href'], $link);
  }
  return implode(', ', $list);
}

/**
 * Generate a nice looking byline
 */
function theme_seed_byline($object) {
  static $accounts;
  $output = '';

  // This is a comment
  if (isset($object->cid)) {
    $date = $object->timestamp;
    $uid = !empty($object->uid) ? $object->uid : NULL;
    $name = !empty($object->name) ? $object->name : NULL;
  }
  // This is a node
  else if ($object->nid) {
    $date = $object->created;
    $uid = !empty($object->uid) ? $object->uid : NULL;
    $name = !empty($object->name) ? $object->name : NULL;
  }

  // Build output
  $date = seed_rel_date($date);
  if ($uid) {
    if (!isset($accounts[$uid])) {
      $accounts[$uid] = user_load(array('uid' => $uid));
    }
    if (!empty($accounts[$uid])) {
      $picture = theme('user_picture', $accounts[$uid]);
      $username = theme('username', $accounts[$uid]);
    }
  }
  if (empty($username)) {
    $username = theme('username', $object);
  }
  return "$picture $username <span class='date'>$date</span>";
}

/**
 * Use mod math to generate an integer for crayon coloring.
 */
function theme_seed_crayon($id) {
  drupal_add_css(drupal_get_path('module', 'seed') .'/theme/seed.css');
  static $crayon;
  static $strings;

  // Initialize static vars.
  if (!isset($crayon)) {
    $crayon = array();
    $strings = array();
  }

  // Do a string to int conversion if necessary
  if (!is_numeric($id)) {
    if (!isset($strings[$id])) {
      // @TODO: Determine the best distinct string to distinct int conversion here.
      $strings[$id] = abs(crc32($id));
    }
    $id = $strings[$id];
  }

  // Return the modulo crayon color id
  if (isset($crayon[$id])) {
    return $crayon[$id];
  }
  else {
    $crayon[$id] = $id % 40;
    return $crayon[$id];
  }
}

/**
 * A generalized hover popup style.
 */
function theme_seed_crayon_popup($id, $label, $color = NULL) {
  $style = $output = '';

  $crayon = !empty($id) ? theme('seed_crayon', $id) : NULL;
  if (!empty($color)) {
    $style = (strpos($color, '#') !== FALSE) ? "background-color: {$color}" : "background-color: #{$color}";
  }
  $content = empty($content) ? $label : $content;

  $output .= "<span class='crayon-popup'>";
  $output .= "<span class='crayon-popup-label'>";
  if ($crayon) {
    $output .= "<span class='crayon-marker crayon-{$crayon}' style='{$style}'></span>";
  }
  $output .= $label;
  $output .= "</span>";
  $output .= "</span>";
  return $output;
}

/**
 * A small swatch of color with label that has a popup with more info on hover.
 */
function theme_seed_crayon_swatch($id, $label, $popup = NULL, $path = NULL, $color = NULL) {
  $popup = empty($popup) ? $label : $popup;
  $popup = theme('seed_crayon_popup', $id, $popup, $color);

  $crayon = theme('seed_crayon', $id);
  if (!empty($color)) {
    $style = (strpos($color, '#') !== FALSE) ? "background-color: {$color}" : "background-color: #{$color}";
  }
  $options = array(
    'html' => true,
    'attributes' => array(
      'class' => 'crayon crayon-swatch crayon-'. $crayon,
      'style' => !empty($style) ? $style : NULL,
    ),
  );

  $content = "<span class='label'>$label</span>$popup";

  if (!empty($path)) {
    return l($content, $path, $options);
  }
  else {
    $attr = drupal_attributes($options['attributes']);
    return "<span $attr>$content</span>";
  }
}

/** 
 * Theme function for split taxonomies
 */
function theme_seed_taxonomy_split($sorted_terms) {
  foreach ($sorted_terms as $key => $term_group) {

    // HTML wrapper per vocabulary
    $output .= '<div class="taxonomy-groups" id="taxonomy_vocabulary_'. $key .'">';

    // Name of vocabulary
    $output .= '<span class="taxonomy-label">'. taxonomy_vocabulary_load($key)->name .'</span>: ';
  
    // Prepare links to terms
    $links = array();
	  foreach ($term_group as $term) {		
      if (is_object($term)) {
        $links['taxonomy_term_'. $term->tid] = array(
          'title' => $term->name,
          'href' => taxonomy_term_path($term),
          'attributes' => array('rel' => 'tag', 'title' => strip_tags($term->description))
        );
      }
    }
    $output .= theme('links', $links, array('class' => 'links inline'));
  }
  return $output;
}

/**
 *  Attachments
 */
function seed_upload_attachments($files) {
  drupal_add_css(drupal_get_path('module', 'seed') .'/theme/seed.css');
  $output = '';
  $header = array(t('Preview'), t('Attachment'), t('Size'));
  $rows = $cells = array();
  foreach ($files as $file) {
    if ($file->list) {
      $href = check_url(($file->fid ? file_create_url($file->filepath) : url(file_create_filename($file->filename, file_create_path()))));
      $text = check_plain($file->description ? $file->description : $file->filename);
      $fileview = seed_fileview($file);
      $rows[] = array(
        array('data' => $fileview, 'class' => 'preview'),
        array('data' => l($text, $href), 'class' => 'attachment'),
        array('data' => format_size($file->filesize), 'class' => 'filesize'),
      );
    }
  }
  if (count($rows)) {
    $output .= theme('table', $header, $rows, array('id' => 'attachments'));
  }
  return $output;
}

/**
 * Image Attachments use Thickbox.
 */
function theme_seed_thickbox($images) {
  $seed_attachments = variable_get('seed_attachments', array());
  $imagecache = $seed_attachments['imagecache_setting'];
  $items_per_row = $seed_attachments['items_per_row'];
  foreach($images as $v) {
    $image = theme('imagecache', $imagecache, $v->filepath, $v->filename, $v->description, array('class' =>'thickbox-image'));
    $items[] = array(
      'data' => l($image, $v->filepath, array('attributes' => array('class' =>'thickbox'), 'html' => TRUE)),
      );
    }
  $header = NULL;
  $rows = array_chunk($items, $items_per_row, TRUE);
  $output .= theme('table', $header, $rows);
  return $output;
}

/**
 * Audio Attachments use Audio Player
 */
function theme_seed_audio($audio) {
  $output = '';
  foreach ($audio as $k => $v) {
    $output .= theme('mp3player', 'Default', url($v->filepath)); 
  }
  return $output;
}

/**
 * Show icons or a preview of image filetypes
 */
function seed_fileview($file) {
  drupal_add_css(drupal_get_path('module', 'seed') .'/theme/seed.css');
  $o = '';
  $href = check_url(($file->fid ? file_create_url($file->filepath) : url(file_create_filename($file->filename, file_create_path()))));
  switch($file->filemime) {
    case 'image/jpeg':
    case 'image/gif':
    case 'image/png':
      if (module_exists('imagecache')) {
        $preset = variable_get('seed_imagecache_attachment', 'attachment');
        $imagecache_path =  imagecache_create_url($preset, $file->filepath);
        $o = l('', $href, array('attributes' => array('style' => "background-image: url('$imagecache_path')")));
      }
      break;
    default:
      $o = l('', $href, array('attributes' => array('class' => 'icon ' . seed_id_safe($file->filemime))));
    break;
  }
  return "<div class='fileview'>$o</div>";
}

/**
 * Add an href-based class to links for themers to implement icons.
 */
function seed_icon_links(&$links) {
  if (!empty($links)) {
    foreach ($links as $k => $v) {
      if (empty($v['attributes'])) {
        $v['attributes'] = array('class' => '');
      }
      else if (empty($v['attributes']['class'])) {
        $v['attributes']['class'] = '';
      }
      $v['attributes']['class'] .= ' icon-'. seed_id_safe(drupal_get_path_alias($v['href']));
      $v['title'] = "<span class='icon'></span><span class='label'>". $v['title'] ."</span>";
      $v['html'] = true;
      $links[$k] = $v;
    }
  }
}
