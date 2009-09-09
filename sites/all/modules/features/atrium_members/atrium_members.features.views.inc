<?php

/**
 * Helper to implementation of hook_views_default_views().
 */
function _atrium_members_views_default_views() {
  $views = array();

  // Exported view: atrium_members
  $view = new view;
  $view->name = 'atrium_members';
  $view->description = 'Atrium > Members';
  $view->tag = 'atrium';
  $view->view_php = '';
  $view->base_table = 'users';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'nid' => array(
      'label' => 'Group node (member)',
      'required' => 0,
      'id' => 'nid',
      'table' => 'og_uid',
      'field' => 'nid',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Name',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
    'mail' => array(
      'label' => 'E-mail',
      'link_to_user' => 'mailto',
      'exclude' => 0,
      'id' => 'mail',
      'table' => 'users',
      'field' => 'mail',
      'relationship' => 'none',
    ),
    'groups' => array(
      'label' => 'Groups',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'type' => 'separator',
      'separator' => ', ',
      'empty' => '',
      'exclude' => 0,
      'id' => 'groups',
      'table' => 'og_uid',
      'field' => 'groups',
      'relationship' => 'none',
    ),
    'rid' => array(
      'label' => 'Roles',
      'type' => 'separator',
      'separator' => ', ',
      'empty' => '',
      'exclude' => 0,
      'id' => 'rid',
      'table' => 'users_roles',
      'field' => 'rid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'name' => array(
      'order' => 'ASC',
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'users',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'uid' => array(
      'operator' => 'in',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'uid_op',
        'identifier' => 'uid',
        'label' => 'Username',
        'optional' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
    ),
    'mail' => array(
      'operator' => 'word',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'mail_op',
        'identifier' => 'mail',
        'label' => 'E-mail',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'mail',
      'table' => 'users',
      'field' => 'mail',
      'relationship' => 'none',
    ),
    'rid' => array(
      'operator' => 'or',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'rid_op',
        'identifier' => 'rid',
        'label' => 'Roles',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'rid',
      'table' => 'users_roles',
      'field' => 'rid',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
    'uid_1' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid_1',
      'table' => 'og_uid',
      'field' => 'uid',
      'relationship' => 'nid',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'create users',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Active users');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('distinct', 1);
  $handler->override_option('style_plugin', 'bulk');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'name' => 'name',
      'mail' => 'name',
      'groups' => 'groups',
      'rid' => 'rid',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 0,
        'separator' => '<br/>',
      ),
      'mail' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'groups' => array(
        'separator' => '',
      ),
      'rid' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
    'execution_type' => '1',
    'display_type' => '0',
    'skip_confirmation' => 1,
    'display_result' => 1,
    'merge_single_action' => 1,
    'selected_operations' => array(
      '4d075a755ad70f936bf89570e66196f1' => '4d075a755ad70f936bf89570e66196f1',
      'c44f2481b4ceb88d43611363418d9e23' => 'c44f2481b4ceb88d43611363418d9e23',
      '73e0815d78610c8e7538ec8c5ad0be0c' => '73e0815d78610c8e7538ec8c5ad0be0c',
      '0b68c1d8f0a1e145e8ef80c7625ed356' => '0b68c1d8f0a1e145e8ef80c7625ed356',
      'daa75f478e3093ab107e657da6620a91' => 'daa75f478e3093ab107e657da6620a91',
      '4f0422e074b9504b834fd2449892f1ec' => '4f0422e074b9504b834fd2449892f1ec',
      '4bd509ad947296ffe30e8092a438e096' => '4bd509ad947296ffe30e8092a438e096',
      '0c3e96a3ccd70cf9a29c1beea1148707' => '0c3e96a3ccd70cf9a29c1beea1148707',
      'a8caceb3ec007d71fefb0000e7d525c4' => 0,
      'dfdea479cc7ae8cb9d3e8749e57f86b4' => 0,
      '4fff50383fdc48042390841723c0d719' => 0,
      'a011c04389ff75f79af39bb612089bca' => 0,
      'b2893e5d0da3d724c359b719997053fd' => 0,
      '132fddcb3f367a243bee632db31985c1' => 0,
      '334d20af1ae7ac4b770b7ec3210b2638' => 0,
      '52aec7fee2070ce530da1304653ae1ec' => 0,
    ),
  ));
  $handler->override_option('exposed_block', TRUE);
  $handler = $view->new_display('page', 'Active users', 'page_1');
  $handler->override_option('path', 'members/all');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'All users',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Users',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Blocked users', 'page_2');
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'users',
      'field' => 'status',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'uid' => array(
      'operator' => 'in',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'uid_op',
        'identifier' => 'uid',
        'label' => 'Username',
        'optional' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'none',
    ),
    'mail' => array(
      'operator' => 'word',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'mail_op',
        'identifier' => 'mail',
        'label' => 'E-mail',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 0,
      'id' => 'mail',
      'table' => 'users',
      'field' => 'mail',
      'relationship' => 'none',
    ),
    'rid' => array(
      'operator' => 'or',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'rid_op',
        'identifier' => 'rid',
        'label' => 'Roles',
        'optional' => 1,
        'single' => 1,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'rid',
      'table' => 'users_roles',
      'field' => 'rid',
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
  ));
  $handler->override_option('title', 'Blocked users');
  $handler->override_option('path', 'members/blocked');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Blocked users',
    'description' => '',
    'weight' => '2',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('page', 'Member directory', 'page_3');
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'strip_tags' => 0,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'spaces_feature',
    'spaces_feature' => 'atrium_intranet',
  ));
  $handler->override_option('title', 'Member directory');
  $handler->override_option('items_per_page', 30);
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '5',
    'alignment' => 'horizontal',
  ));
  $handler->override_option('path', 'members/directory');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'Directory',
    'description' => '',
    'weight' => '-10',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Members',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Add users page', 'page_4');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'name' => 'name',
      'mail' => 'name',
      'groups' => 'groups',
      'rid' => 'rid',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 0,
        'separator' => '<br/>',
      ),
      'mail' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'groups' => array(
        'separator' => '',
      ),
      'rid' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
    'execution_type' => '1',
    'display_type' => '0',
    'skip_confirmation' => 1,
    'display_result' => 1,
    'merge_single_action' => 1,
    'selected_operations' => array(
      '598c4c0e356e66e85f78c2d61cac3fac' => '598c4c0e356e66e85f78c2d61cac3fac',
      '0c478c83f8bd0b8019e9ae38b0f15fe5' => '0c478c83f8bd0b8019e9ae38b0f15fe5',
      'a8caceb3ec007d71fefb0000e7d525c4' => 0,
      'dfdea479cc7ae8cb9d3e8749e57f86b4' => 0,
      '4fff50383fdc48042390841723c0d719' => 0,
      '4d075a755ad70f936bf89570e66196f1' => 0,
      'a011c04389ff75f79af39bb612089bca' => 0,
      'c44f2481b4ceb88d43611363418d9e23' => 0,
      'b2893e5d0da3d724c359b719997053fd' => 0,
      '132fddcb3f367a243bee632db31985c1' => 0,
      '334d20af1ae7ac4b770b7ec3210b2638' => 0,
      '73e0815d78610c8e7538ec8c5ad0be0c' => 0,
      '0b68c1d8f0a1e145e8ef80c7625ed356' => 0,
      '52aec7fee2070ce530da1304653ae1ec' => 0,
      'daa75f478e3093ab107e657da6620a91' => 0,
      '4f0422e074b9504b834fd2449892f1ec' => 0,
      '4bd509ad947296ffe30e8092a438e096' => 0,
      '0c3e96a3ccd70cf9a29c1beea1148707' => 0,
    ),
  ));
  $handler->override_option('path', 'og/users/%/add_user');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Add users',
    'description' => '',
    'weight' => '20',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $translatables['atrium_members'] = array(
    t('Defaults'),
    t('Active users'),
    t('Blocked users'),
    t('Member directory'),
    t('Add users page'),
  );

  $views[$view->name] = $view;

  return $views;
}
