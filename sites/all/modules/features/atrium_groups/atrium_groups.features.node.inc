<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_groups_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Group'),
      'module' => 'features',
      'description' => t(''),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => t('Body'),
    ),
  );
  return $items;
}
