<?php

/**
 * Helper to implementation of hook_node_info().
 */
function _atrium_calendar_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'module' => 'features',
      'description' => t(''),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
    ),
    'feed_ical' => array(
      'name' => t('iCal Feed'),
      'module' => 'features',
      'description' => t('An ical feed within a group.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => t(''),
    ),
    'feed_ical_item' => array(
      'name' => t('iCal Event'),
      'module' => 'features',
      'description' => t('An ical event within a group.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
    ),
  );
  return $items;
}
