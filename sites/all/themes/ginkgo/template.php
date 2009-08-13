<?php

/**
 * Implementation of hook_theme().
 */
function ginkgo_theme($existing, $type, $theme, $path) {
  return array(
    'blocks_header' => array(),
    'user_profile_form' => array(
      'arguments' => array('form' => array()),
      'template' => 'node_form',
      'path' => drupal_get_path('theme', 'ginkgo') . "/templates",
    ),
  );
}

/**
 * Add an href-based class to links for themers to implement icons.
 */
function ginkgo_icon_links(&$links) {
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

/**
 * Preprocess overrides ===============================================
 */

/**
 * Preprocessor for theme_page().
 */
function ginkgo_preprocess_page(&$vars) {
  // Add icon markup to main menu
  ginkgo_icon_links($vars['primary_links']);

  // Grab the header dropdown links
  $vars['header'] = theme('blocks_header', array());
  $vars['dropdown_links'] = theme('blocks_header', array(), TRUE);

  // If tabs are active, the title is likely shown in them. Don't show twice.
  $vars['title'] = !empty($vars['tabs']) ? '' : $vars['title'];

  // Respect anything people are requesting through context.
  if (module_exists('context')) {
    if (context_get('theme', 'layout') == 'custom') {
      $vars['custom_layout'] = TRUE;
    }
    if ($classes = context_get('theme', 'body_classes')) {
      $vars['attr']['class'] .= " {$classes}";
    }
  }

  // Add a smarter body class than "not logged in" for determining whether
  // we are on a login/password/user registration related page.
  global $user;
  $vars['mission'] = '';
  if (!$user->uid && arg(0) == 'user') {
    $vars['attr']['class'] .= ' anonymous-login';
    $vars['mission'] = filter_xss_admin(variable_get('site_mission', ''));
  }

  // Theme specific settings
  $settings = theme_get_settings('ginkgo');

  // Show site title/emblem ?
  if (isset($settings['emblem']) && !$settings['emblem']) {
    $vars['site_name'] = '';
  }

  // Add spaces design CSS back in
  if (empty($vars['spaces_design_styles'])) {
    global $theme_info;
    $space = spaces_get_space();

    // Retrieve default colors from info file
    if (isset($theme_info->info["spaces_design_{$space->type}"])) {
      $default = $theme_info->info["spaces_design_{$space->type}"];
    }
    else {
      $default = '#3399aa';
    }

    $color = !empty($settings["color_{$space->type}"]) ? $settings["color_{$space->type}"] : $default;
    $vars['styles'] .= theme('spaces_design', $color);
    $vars['attr']['class'] .= ' spaces-design';
  }
  else {
    $vars['styles'] .= $vars['spaces_design_styles'];
  }
}

/**
 * Preprocessor for theme_node().
 */
function ginkgo_preprocess_node(&$vars) {
    $vars['submitted'] = !empty($vars['submitted']) ? theme('seed_byline', $vars['node']) : ''; 
  if (!empty($vars['terms'])) {
    $label = t('Tagged');
    $terms = "<div class='field terms clear-block'><span class='field-label'>{$label}:</span> {$vars['terms']}</div>";
    $vars['content'] =  $terms . $vars['content'];
  }
  if (context_get('comment', 'preview') == TRUE) {
    $vars = array();
  }
  if (!empty($vars['xref_links'])) {
    $vars['title'] = $vars['xref_links'] . $vars['title'];
  }
}

/**
 * Preprocessor for theme_comment().
 */
function ginkgo_preprocess_comment(&$vars) {
  $vars['submitted'] = theme('seed_byline', $vars['comment']);

  // We're totally previewing a comment... set a context so others can bail.
  if (module_exists('context')) {
    if (empty($vars['comment']->cid) && !empty($vars['comment']->form_id)) {
      context_set('comment', 'preview', TRUE);
    }
    else if (context_isset('comment', 'preview')) {
      $vars = array();
    }
  }
}

/**
 * Charts theming override.
 */
function ginkgo_preprocess_flot_views_summary_style(&$vars) {
  global $theme_key;
  if ($theme_key == 'ginkgo_thin') {
    $vars['element']['style'] = "width:220px; height:80px;";
  }
  else {
    $vars['element']['style'] = "width:280px; height:100px;";
  }

  $vars['options']->colors = array('#666', '#ccc', '#999');
  $vars['options']->grid->tickColor = '#eee';
  $vars['options']->grid->backgroundColor = '#fff';
}

/**
 * Preprocessor for theme_spaces_design().
 */
function ginkgo_preprocess_spaces_design(&$vars) {
  if (module_exists('color') && !empty($vars['color'])) {
    if ($rgb = _color_unpack($vars['color'], TRUE)) {
      $classes = context_get('theme', 'body_classes');
      $classes .= ' color';
      context_set('theme', 'body_classes', $classes);

      $hsl = _color_rgb2hsl($rgb);

      if ($hsl[2] > .8) {
        $hsl[2] = .7;
        $rgb = _color_hsl2rgb($hsl);
      }

      // This code generates color values that are blended against
      // Black/White -- IT DOES NOT PRESERVE SATURATION.
      $modifiers = array(
        'upshift' => ($hsl[2] < .25) ? array('+', .1) : array('+', .25),
        'downshift' => array('-', .38),
      );
      foreach ($modifiers as $id => $modifier) {
        $color = $rgb;
        foreach ($rgb as $k => $v) {
          switch ($modifier[0]) {
            case '-':
              $color[$k] = $color[$k] * (1 - $modifier[1]);
              break;
            default:
              $color[$k] = $color[$k] + ((1 - $color[$k]) * $modifier[1]);
              break;
          }
        }
        $vars[$id] = _color_pack($color, TRUE);
      }
      $vars['color'] = _color_pack($rgb, TRUE);
    }
  }
}

/**
 * Preprocessor for theme_node_form().
 * Better theming of spaces privacy messages on node forms.
 */
function ginkgo_preprocess_node_form(&$vars) {
  context_set('theme', 'layout', 'custom');
  context_set('theme', 'body_classes', 'one-sidebar');

  if (!empty($vars['form']['spaces'])) {
    $spaces_info = $vars['form']['spaces'];
    switch ($vars['form']['#node']->og_public) {
      case OG_VISIBLE_GROUPONLY:
        $class = 'form-message-private';
        break;
      case OG_VISIBLE_BOTH:
        $class = 'form-message-public';
        break;
    }
    $form_message = "<div class='form-message $class'><span class='icon'></span>{$spaces_info['#description']}</div>";
    $vars['form_message'] = $form_message;

    unset($vars['form']['spaces']);
  }

  // Add node preview to top of the form if present
  $preview = theme('node_preview', NULL, TRUE);
  $vars['form']['preview'] = array('#type' => 'markup', '#weight' => -1000, '#value' => $preview);

  if (!empty($vars['form']['archive'])) {
    $vars['sidebar']['archive'] = $vars['form']['archive'];
    unset($vars['form']['archive']);
  }
}

/**
 * Preprocessor for theme_user_profile_form().
 */
function ginkgo_preprocess_user_profile_form(&$vars) {
  context_set('theme', 'layout', 'custom');
  context_set('theme', 'body_classes', 'one-sidebar');
}

/**
 * Preprocessor for theme_admin_message_message().
 */
function ginkgo_preprocess_admin_message_message(&$vars) {
  $vars['timestamp'] = module_exists('seed') ? seed_rel_date($vars['node']->created) : '';
  $vars['title'] = check_plain($vars['node']->title);
  $vars['content'] = drupal_render($vars['node']->content);
}

/**
 * Function overrides =================================================
 */

/**
 * Themes header region blocks into dropdowns
 */
function ginkgo_blocks_header($blocks, $get_links = FALSE) {
  static $links;
  static $dropdown;
  if (!isset($dropdown)) {
    $dropdown = '';
    $links = array();
    if (menu_get_active_help()) {
      $helpblock = new StdClass();
      $helpblock->module =
      $helpblock->delta = 'help';
      $helpblock->subject = t('Need help?');
      $helpblock->content = theme('help');
      $helpblock->region = 'header';
      $blocks[] = $helpblock;
    }
    foreach ($blocks as $block) {
      $links["{$block->module}-{$block->delta}"] = array(
        'title' => $block->subject,
        'href' => $_GET['q'],
        'fragment' => "{$block->module}-{$block->delta}",
      );
      $dropdown .= theme('block', $block);
    }
    $dropdown = "<div class='dropdown-blocks'>{$dropdown}</div>";
    $links = module_exists('atrium') ? atrium_skin_links($links) : $links;
    $links = theme('links', $links, array('class' => 'links dropdown'));
  }
  return $get_links ? $links : $dropdown;
}

/**
 * Override of theme_help().
 */
function ginkgo_help() {
  $help = menu_get_active_help();
  $test = strip_tags($help);
  if (!empty($test)) {
    return "<div class='prose'>{$help}</div>";
    $output = "<div class='messages help clear-block'>";
    $output .= "<div class='message-label'>". t('Need help?') ."</div>";
    $output .= "<div class='message-content filter-text'>$help</div>";
    $output .= "</div>";
    return $output;
  }
}

/**
 * Override of theme_status_message().
 */
function ginkgo_status_messages($display = NULL) {
  $output = '';
  $first = TRUE;

  // Theme specific settings
  $settings = theme_get_settings('ginkgo');
  $autoclose = isset($settings['autoclose']) ? $settings['autoclose'] : array('status' => 1, 'warning' => 0, 'error' => 0);

  foreach (drupal_get_messages($display) as $type => $messages) {
    $class = $first ? 'first' : '';
    $class .= !empty($autoclose[$type]) || !isset($autoclose[$type]) ? ' autoclose' : '';
    $first = FALSE;

    $output .= "<div class='messages clear-block $type $class'>";
    $output .= "<span class='close'>". t('Hide') ."</span>";
    $output .= "<div class='message-label'>{$type}</div>";
    $output .= "<div class='message-content'>";
    if (count($messages) > 1) {
      $output .= "<ul>";
      foreach ($messages as $k => $message) {
        if ($k == 0) {
          $output .= "<li class='message-item first'>$message</li>";
        }
        else if ($k == count($messages) - 1) {
          $output .= "<li class='message-item last'>$message</li>";
        }
        else {
          $output .= "<li class='message-item'>$message</li>";
        }
      }
      $output .= "</ul>";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>";
    $output .= "</div>";
  }
  return $output;
}

/**
 * Make logo markup overridable.
 */
function ginkgo_spaces_design_logo($filepath) {
  $url = imagecache_create_url('spaces-logo', $filepath);
  $space = spaces_get_space();
  $options = array(
    'attributes' => array(
      'class' => 'spaces-logo',
      'style' => 'background-image:url(\''. $url .'\')'
    ),
  );
  return l($space->title, '<front>', $options);
}

/**
 * Marker theming override.
 */
function ginkgo_mark($type = MARK_NEW) {
  global $user;
  if ($user->uid) {
    if ($type == MARK_NEW) {
      return ' <span class="marker"><span>'. t('new') .'</span></span>';
    }
    else if ($type == MARK_UPDATED) {
      return ' <span class="marker"><span>'. t('updated') .'</span></span>';
    }
  }
}

/**
 * More link theme override.
 */
function ginkgo_more_link($url, $title) {
  return '<div class="more-link">'. t('<a href="@link" title="@title">View more</a>', array('@link' => check_url($url), '@title' => $title)) .'</div>';
}

/**
 * Menu item theme override. Adds a child element to expanded/expandable
 * elements so that a spite icon can be added.
 */
function ginkgo_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
  if ($has_children) {
    // Allow the parent class to determine the icon's actual styling.
    $icon = "<span class='icon'></span>";
    $link = "{$icon} $link";
  }
  return theme_menu_item($link, $has_children, $menu, $in_active_trail, $extra_class);
}

/**
 * Implementation of hook_preprocess_user_picture().
 */
function ginkgo_preprocess_user_picture(&$vars) {
  $account = $vars['account'];
  if (isset($account->picture) && module_exists('imagecache')) {
    $attr = array('class' => 'user-picture');
    $preset = variable_get('seed_imagecache_user_picture', '30x30_crop');
    if ($view = views_get_current_view()) {
      switch ($view->name) {
        case 'og_members_faces':
        case 'atrium_members':
        case 'atrium_profile':
          $preset = 'user-m';
          break;
      }
    }
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

/**
 * Override of theme_pager(). Tao has already done the hard work for us.
 * Just exclude last/first links.
 */
function ginkgo_pager($tags = array(), $limit = 10, $element = 0, $parameters = array(), $quantity = 9) {
  $pager_list = theme('pager_list', $tags, $limit, $element, $parameters, $quantity);

  $links = array();
  $links['pager-previous'] = theme('pager_previous', ($tags[1] ? $tags[1] : t('Prev')), $limit, $element, 1, $parameters);
  $links['pager-next'] = theme('pager_next', ($tags[3] ? $tags[3] : t('Next')), $limit, $element, 1, $parameters);
  $pager_links = theme('links', $links, array('class' => 'links pager pager-links'));

  if ($pager_list) {
    return "<div class='pager clear-block'>$pager_list $pager_links</div>";
  }
}

/**
 * Override of theme_node_preview().
 * We remove the teaser check / view here ... for nearly all use cases
 * this is more confusing and overbearing than anything else. We also
 * add a static variable as a trigger so that we can render node_preview
 * inside our form, rather than separate.
 */
function ginkgo_node_preview($node = NULL, $show = FALSE) {
  static $output;
  if (!isset($output) && $node) {
    $output = '<div class="preview node-preview">';
    $output .= '<h2 class="preview-title">'. t('Preview') .'</h2>';
    $output .= '<div class="preview-content clear-block">'. node_view($node, 0, FALSE, 0) .'</div>';
    $output .= "</div>";
  }
  return $show ? $output : '';
}
