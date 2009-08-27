<?php

/**
 * Implementation of space_setting.
 */
class atrium_setting_sitemode implements space_setting {
  var $id;
  var $types;

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
    $roles = _features_get_roles();
    switch ($value) {
      case ATRIUM_SITEMODE_PRIVATE:
        _atrium_ensure_perm($roles, 'authenticated user', 'access user profiles');
        _atrium_ensure_perm($roles, 'authenticated user', 'access content');
        _atrium_ensure_perm($roles, 'authenticated user', 'access comments');
        _atrium_ensure_perm($roles, 'authenticated user', 'view revisions');

        _atrium_remove_perm($roles, 'anonymous user', 'access user profiles');
        _atrium_remove_perm($roles, 'anonymous user', 'access content');
        _atrium_remove_perm($roles, 'anonymous user', 'access comments');
        _atrium_remove_perm($roles, 'anonymous user', 'view revisions');
        break;
      case ATRIUM_SITEMODE_PUBLIC:
      case ATRIUM_SITEMODE_CONTROLLED:
        _atrium_ensure_perm($roles, 'authenticated user', 'access user profiles');
        _atrium_ensure_perm($roles, 'authenticated user', 'access content');
        _atrium_ensure_perm($roles, 'authenticated user', 'access comments');
        _atrium_ensure_perm($roles, 'authenticated user', 'view revisions');

        _atrium_ensure_perm($roles, 'anonymous user', 'access user profiles');
        _atrium_ensure_perm($roles, 'anonymous user', 'access content');
        _atrium_ensure_perm($roles, 'anonymous user', 'access comments');
        _atrium_ensure_perm($roles, 'anonymous user', 'view revisions');
        break;
    }
    _user_features_save_roles($roles);

    return $value;
  }
}

/**
 * Implementation of space_setting.
 */
class atrium_setting_members implements space_setting {
  var $id;
  var $types;

  function __construct($id = NULL) {
    $this->id = 'atrium_members';
    $this->types = array('site');
  }

  function form($space, $value = array()) {
    $form = array(
      '#title' => t('Members'),
      '#type' => 'select',
      '#description' => t('Choose the access mode for the member directory and profiles. Administrators and managers will be able to see all members regardless of this setting.'),
      '#options' => array(
        ATRIUM_MEMBERS_ALL => t('Users can view all members'),
        ATRIUM_MEMBERS_GROUP => t('Users can only view members that belong to their groups')
      ),
      '#default_value' => !empty($value) ? $value : 0,
    );
    return $form;
  }

  function validate($space, $value) { }

  function submit($space, $value) {
    features_include();
    $roles = _features_get_roles();
    switch ($value) {
      case ATRIUM_MEMBERS_ALL:
        _atrium_ensure_perm($roles, 'authenticated user', 'view users outside groups');
        _atrium_ensure_perm($roles, 'anonymous user', 'view users outside groups');
        _atrium_ensure_perm($roles, 'manager', 'view users outside groups');
        _atrium_ensure_perm($roles, 'admin', 'view users outside groups');
        break;
      case ATRIUM_MEMBERS_GROUP:
        _atrium_remove_perm($roles, 'authenticated user', 'view users outside groups');
        _atrium_remove_perm($roles, 'anonymous user', 'view users outside groups');
        _atrium_ensure_perm($roles, 'manager', 'view users outside groups');
        _atrium_ensure_perm($roles, 'admin', 'view users outside groups');
        break;
    }
    _user_features_save_roles($roles);
    return $value;
  }
}
