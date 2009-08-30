<?php

/**
 * Implementation of space_setting.
 */
class atrium_members_setting_members implements space_setting {
  var $id;

  function __construct($id = NULL) {
    $this->id = 'atrium_members';
  }

  function form($space, $value = array()) {
    $options = array(0 => t('Show all members'), 1 => t('Show only members in current user\'s groups'));
    $form = array(
      '#title' => t('Members'),
      '#type' => 'select',
      '#description' => t('Choose the display mode for normal users when viewing the member directory. Administrators and managers will still be able to see all members in administrative views.'),
      '#options' => $options,
      '#default_value' => !empty($value) ? $value : 0,
    );
    return $form;
  }

  function validate($space, $value) {
  }

  function submit($space, $value) {
    return $value;
  }
}
