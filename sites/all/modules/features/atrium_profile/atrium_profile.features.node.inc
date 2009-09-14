<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_profile_node_info() {
  $items = array(
    'profile' => array(
      'name' => t('Profile'),
      'module' => 'features',
      'description' => t('Profile.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'has_body' => '0',
      'body_label' => t(''),
    ),
  );
  return $items;
}
