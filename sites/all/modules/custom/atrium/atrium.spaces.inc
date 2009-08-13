<?php

/**
 * Implementation of space_setting.
 */
class atrium_setting_sitemode implements space_setting {
  var $id;

  function __construct($id = NULL) {
    $this->id = 'atrium_sitemode';
    $this->types = array('site');
  }

  function form($space, $value = array()) {
    $options = array(
      ATRIUM_SITEMODE_PRIVATE => t('Private access only'),
      ATRIUM_SITEMODE_PUBLIC => t('Public access, open registration'),
      ATRIUM_SITEMODE_CONTROLLED => t('Public access, moderated registration'),
    );
    $form = array(
      '#title' => t('Site mode'),
      '#type' => 'select',
      '#description' => t('Choose the access level for the site.'),
      '#options' => $options,
      '#default_value' => !empty($value) ? $value : ATRIUM_SITEMODE_PRIVATE,
    );
    return $form;
  }

  function validate($space, $value) { }

  function submit($space, $value) {
    // Set user registration mode variable
    variable_set('user_register', $value);

    // Toggle access content, comments perms
    features_include();
    $roles = _user_features_get_roles();
    switch ($value) {
      case ATRIUM_SITEMODE_PRIVATE:
        $this->ensure_perm($roles, 'authenticated user', 'access content');
        $this->ensure_perm($roles, 'authenticated user', 'access comments');
        $this->remove_perm($roles, 'anonymous user', 'access content');
        $this->remove_perm($roles, 'anonymous user', 'access comments');
        break;
      case ATRIUM_SITEMODE_PUBLIC:
      case ATRIUM_SITEMODE_CONTROLLED:
        $this->ensure_perm($roles, 'authenticated user', 'access content');
        $this->ensure_perm($roles, 'authenticated user', 'access comments');
        $this->ensure_perm($roles, 'anonymous user', 'access content');
        $this->ensure_perm($roles, 'anonymous user', 'access comments');
        break;
    }
    _user_features_save_roles($roles);

    return $value;
  }

  function ensure_perm(&$roles, $role, $perm) {
    if (!in_array($perm, $roles[$role]['perm'])) {
      $roles[$role]['perm'][] = $perm;
    }
  }

  function remove_perm(&$roles, $role, $perm) {
    if (in_array($perm, $roles[$role]['perm'])) {
      $position = array_search($perm, $roles[$role]['perm']);
      unset($roles[$role]['perm'][$position]);
    }
  }
}
