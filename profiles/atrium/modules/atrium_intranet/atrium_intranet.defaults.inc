<?php

/**
 * Helper to implemetation of hook_content_default_fields().
 */
function _atrium_intranet_content_default_fields() {
  $fields = array();

  // Exported field: field_profile_address
  $fields[] = array(
    'field_name' => 'field_profile_address',
    'type_name' => 'profile',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'weight' => 0,
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 1,
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => NULL,
      'size' => NULL,
      'label' => 'Address',
      'weight' => '10',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_profile_organization
  $fields[] = array(
    'field_name' => 'field_profile_organization',
    'type_name' => 'profile',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'weight' => 0,
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 0,
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => NULL,
      'size' => NULL,
      'label' => 'Organization',
      'weight' => 0,
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_profile_telephone
  $fields[] = array(
    'field_name' => 'field_profile_telephone',
    'type_name' => 'profile',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'weight' => 0,
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 0,
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => NULL,
      'size' => NULL,
      'label' => 'Telephone',
      'weight' => 0,
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_profile_url
  $fields[] = array(
    'field_name' => 'field_profile_url',
    'type_name' => 'profile',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'weight' => 0,
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 0,
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => NULL,
      'size' => NULL,
      'label' => 'URL',
      'weight' => '9',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  return $fields;
}

/**
 * Helper to implemetation of hook_context_default_contexts().
 */
function _atrium_intranet_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'groups',
    'menu' => 'groups',
    'views' => array(
      '0' => 'atrium_groups',
    ),
    'theme_section' => array(
      'title' => 'Groups',
      'subtitle' => '',
      'class' => '',
    ),
    'block' => array(),
  );
  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'members',
    'menu' => 'members',
    'views' => array(
      '0' => 'atrium_members',
    ),
    'theme_section' => array(
      'title' => 'Members',
      'subtitle' => '',
      'class' => '',
    ),
    'block' => array(
      'views_-exp-atrium_members-default' => array(
        'module' => 'views',
        'delta' => '-exp-atrium_members-default',
        'region' => 'right',
        'weight' => '-10',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'global',
    'value' => 'blocks',
    'description' => 'Sitewide blocks',
    'sitewide' => array(
      '0' => '1',
    ),
    'block' => array(
      'admin_message_admin_message' => array(
        'module' => 'admin_message',
        'delta' => 'admin_message',
        'weight' => 20,
        'region' => 'console',
        'status' => '0',
        'label' => 'Admin messages',
        'type' => 'context_ui',
      ),
      'views_atrium_groups-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_groups-block_1',
        'weight' => 21,
        'region' => 'header',
        'status' => '0',
        'label' => 'atrium_groups: Block',
        'type' => 'context_ui',
      ),
    ),
  );
  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'section',
    'value' => 'admin',
    'description' => '',
    'node' => array(
      '0' => 'admin_message',
    ),
    'path' => array(
      '0' => 'atrium',
    ),
    'views' => array(
      '0' => 'atrium_admin_messages',
    ),
  );
  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'section',
    'value' => 'search',
    'views' => array(
      '0' => 'atrium_search',
    ),
    'theme_section' => array(
      'title' => 'Search',
    ),
  );
  $items[] = array(
    'namespace' => 'atrium',
    'attribute' => 'section',
    'value' => 'taxonomy',
    'views' => array(
      '0' => 'atrium_taxonomy',
    ),
    'theme_section' => array(
      'title' => 'Tags',
    ),
    'block' => array(
      'views_atrium_taxonomy-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_taxonomy-block_1',
        'region' => 'right',
        'weight' => '10',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implemetation of hook_imagecache_default_presets().
 */
function _atrium_intranet_imagecache_default_presets() {
  $items = array(
    'fileview' => array(
      'presetname' => 'fileview',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_deprecated_scale',
          'data' => array(
            'fit' => 'inside',
            'width' => '60',
            'height' => '40',
          ),
        ),
      ),
    ),
    'user-m' => array(
      'presetname' => 'user-m',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '60',
            'height' => '60',
          ),
        ),
      ),
    ),
    'user-s' => array(
      'presetname' => 'user-s',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '30',
            'height' => '30',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implemetation of hook_menu_default_items().
 */
function _atrium_intranet_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Groups',
    'path' => 'groups',
    'weight' => '0',
    'description' => 'Provides a group management feature',
  );
  $items[] = array(
    'title' => 'Members',
    'path' => 'members',
    'weight' => '0',
    'description' => 'Provides a member directory and user management feature',
  );

  return $items;
}

/**
 * Helper to implemetation of hook_node_info().
 */
function _atrium_intranet_node_info() {
  $items = array(
    'group' => array(
      'name' => t('Group'),
      'module' => 'node',
      'description' => t(''),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => t('Body'),
    ),
  );
  return $items;
}

/**
 * Helper to implemetation of hook_views_default_views().
 */
function _atrium_intranet_views_default_views() {
  $views = array();

  // Exported view: atrium_admin_messages
  $view = new view;
  $view->name = 'atrium_admin_messages';
  $view->description = 'Atrium > Admin messages';
  $view->tag = 'atrium';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'created' => array(
      'label' => 'Post date',
      'date_format' => 'reldate',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Title',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'sticky' => array(
      'label' => 'Show message',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 0,
      'id' => 'sticky',
      'table' => 'node',
      'field' => 'sticky',
      'relationship' => 'none',
    ),
    'edit_node' => array(
      'label' => 'Edit',
      'text' => 'Edit',
      'exclude' => 0,
      'id' => 'edit_node',
      'table' => 'node',
      'field' => 'edit_node',
      'relationship' => 'none',
    ),
    'delete_node' => array(
      'label' => '',
      'text' => 'Delete',
      'exclude' => 0,
      'id' => 'delete_node',
      'table' => 'node',
      'field' => 'delete_node',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'sticky' => array(
      'order' => 'DESC',
      'id' => 'sticky',
      'table' => 'node',
      'field' => 'sticky',
      'relationship' => 'none',
    ),
    'created' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'admin_message' => 'admin_message',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'administer atrium',
  ));
  $handler->override_option('title', 'Messages & alerts');
  $handler->override_option('empty', 'No messages found.');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'created' => 'created',
      'title' => 'title',
      'sticky' => 'sticky',
      'edit_node' => 'edit_node',
      'delete_node' => 'edit_node',
    ),
    'info' => array(
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'sticky' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'edit_node' => array(
        'separator' => ' | ',
      ),
      'delete_node' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'admin/atrium/messages');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Messages & alerts',
    'description' => '',
    'weight' => '5',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $translatables['atrium_admin_messages'] = array(
    t('Defaults'),
    t('Messages & alerts'),
    t('No messages found.'),
    t('Page'),
  );

  $views[$view->name] = $view;

  // Exported view: atrium_contentstats
  $view = new view;
  $view->name = 'atrium_contentstats';
  $view->description = 'Atrium > Content stats';
  $view->tag = 'atrium';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'nid' => array(
      'label' => '',
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'created_shortdate' => array(
      'default_action' => 'summary desc',
      'style_plugin' => 'flot_summary',
      'style_options' => array(
        'type' => 'bar',
        'size' => '400x200',
        'xaxis' => 'endpoints',
        'yaxis' => '3',
        'reverse' => 1,
        'pad_y' => 1,
      ),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'id' => 'created_shortdate',
      'table' => 'node',
      'field' => 'created_shortdate',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
        '4' => 0,
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'admin_message' => 0,
        'casetracker_basic_project' => 0,
        'casetracker_basic_case' => 0,
        'shoutbox' => 0,
        'blog' => 0,
        'book' => 0,
        'event' => 0,
        'feed_ical' => 0,
        'feed_ical_item' => 0,
        'profile' => 0,
        'group' => 0,
        'feedapi_node' => 0,
        'imageset' => 0,
        'page' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        '5' => 0,
        '1' => 0,
        '2' => 0,
        '6' => 0,
        '4' => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_is_member' => 0,
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'blog' => 'blog',
        'admin_message' => 'admin_message',
        'casetracker_basic_project' => 'casetracker_basic_project',
        'casetracker_basic_case' => 'casetracker_basic_case',
        'book' => 'book',
        'event' => 'event',
        'feed_ical' => 'feed_ical',
        'imageset' => 'imageset',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
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
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'current' => array(
      'operator' => 'active',
      'value' => 'all',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'current',
      'table' => 'spaces',
      'field' => 'current',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Content stats');
  $handler->override_option('items_per_page', 30);
  $handler = $view->new_display('block', 'Content stats', 'block_1');
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $translatables['atrium_contentstats'] = array(
    t('Defaults'),
    t('Content stats'),
  );

  $views[$view->name] = $view;

  // Exported view: atrium_groups
  $view = new view;
  $view->name = 'atrium_groups';
  $view->description = 'Atrium > Groups';
  $view->tag = 'atrium';
  $view->view_php = '';
  $view->base_table = 'node';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'post_count_new' => array(
      'label' => '',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'post_count_new',
      'table' => 'og',
      'field' => 'post_count_new',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => '',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'title' => array(
      'order' => 'ASC',
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
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
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'uid' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid',
      'table' => 'og_uid',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'perm',
    'perm' => 'access content',
  ));
  $handler->override_option('title', 'My groups');
  $handler->override_option('items_per_page', 0);
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(),
    'separator' => '',
  ));
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->override_option('fields', array(
    'title' => array(
      'label' => '',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('block', 'Block', 'block_2');
  $handler->override_option('items_per_page', 15);
  $handler->override_option('use_more', 1);
  $handler->override_option('block_description', '');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('fields', array(
    'private' => array(
      'label' => '',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'private',
      'table' => 'og',
      'field' => 'private',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Group',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'post_count' => array(
      'label' => 'Total posts',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'post_count',
      'table' => 'og',
      'field' => 'post_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'member_count' => array(
      'label' => 'Members',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'member_count',
      'table' => 'og',
      'field' => 'member_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Created',
      'date_format' => 'reldate',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'private' => 'private',
      'title' => 'title',
      'post_count_new' => 'title',
      'post_count' => 'post_count',
      'member_count' => 'member_count',
      'created' => 'created',
    ),
    'info' => array(
      'private' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'post_count_new' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'post_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'member_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('row_options', array());
  $handler->override_option('path', 'groups/my');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'My groups',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Groups',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Page', 'page_2');
  $handler->override_option('fields', array(
    'private' => array(
      'label' => '',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'private',
      'table' => 'og',
      'field' => 'private',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Group',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'selective' => array(
      'label' => 'Type',
      'exclude' => 0,
      'id' => 'selective',
      'table' => 'og',
      'field' => 'selective',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'member_count' => array(
      'label' => 'Members',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'member_count',
      'table' => 'og',
      'field' => 'member_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'post_count' => array(
      'label' => 'Total posts',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'post_count',
      'table' => 'og',
      'field' => 'post_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Created',
      'date_format' => 'reldate',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'subscribe' => array(
      'label' => 'Join',
      'exclude' => 0,
      'id' => 'subscribe',
      'table' => 'og',
      'field' => 'subscribe',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
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
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'directory' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'directory',
      'table' => 'og',
      'field' => 'directory',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Directory');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'private' => 'private',
      'title' => 'title',
      'selective' => 'selective',
      'member_count' => 'member_count',
      'post_count' => 'post_count',
      'created' => 'created',
      'subscribe' => 'subscribe',
    ),
    'info' => array(
      'private' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'selective' => array(
        'separator' => '',
      ),
      'member_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'post_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'subscribe' => array(
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'title' => 'title',
      'post_count_new' => 'post_count_new',
    ),
    'separator' => '',
  ));
  $handler->override_option('path', 'groups/directory');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Directory',
    'description' => '',
    'weight' => '1',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('page', 'Page', 'page_3');
  $handler->override_option('fields', array(
    'private' => array(
      'label' => '',
      'type' => 'yes-no',
      'not' => 0,
      'exclude' => 1,
      'id' => 'private',
      'table' => 'og',
      'field' => 'private',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'Group',
      'link_to_node' => 1,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'selective' => array(
      'label' => 'Type',
      'exclude' => 0,
      'id' => 'selective',
      'table' => 'og',
      'field' => 'selective',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'member_count' => array(
      'label' => 'Members',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'member_count',
      'table' => 'og',
      'field' => 'member_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'post_count' => array(
      'label' => 'Total posts',
      'set_precision' => FALSE,
      'precision' => 0,
      'decimal' => '.',
      'separator' => ',',
      'prefix' => '',
      'suffix' => '',
      'exclude' => 0,
      'id' => 'post_count',
      'table' => 'og',
      'field' => 'post_count',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'created' => array(
      'label' => 'Created',
      'date_format' => 'reldate',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'type_groups_all' => array(
      'operator' => '=',
      'value' => '',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type_groups_all',
      'table' => 'og',
      'field' => 'type_groups_all',
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => '=',
      'value' => 0,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'uid' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'uid',
      'table' => 'og_uid',
      'field' => 'uid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Archived groups');
  $handler->override_option('empty', 'No archived groups found.');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'private' => 'private',
      'title' => 'title',
      'post_count_new' => 'title',
      'post_count' => 'post_count',
      'member_count' => 'member_count',
      'created' => 'created',
    ),
    'info' => array(
      'private' => array(
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'post_count_new' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'post_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'member_count' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'created' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => '-1',
  ));
  $handler->override_option('path', 'groups/archived');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Archived',
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
  $translatables['atrium_groups'] = array(
    t('Defaults'),
    t('My groups'),
    t('Block'),
    t('Page'),
    t('Directory'),
    t('Archived groups'),
    t('No archived groups found.'),
  );

  $views[$view->name] = $view;

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
      'db4e570c092ffef012179fe5713e6c27' => 'db4e570c092ffef012179fe5713e6c27',
      '2ee09d423aa91460cebfc6453deeab42' => '2ee09d423aa91460cebfc6453deeab42',
      'adde2fa9520d724f8f100bae202dfdeb' => 'adde2fa9520d724f8f100bae202dfdeb',
      '35d389062d295b91c958b2b2eb68a4a7' => '35d389062d295b91c958b2b2eb68a4a7',
      '126df8a04e3f32d42ce1ffd3bb430097' => '126df8a04e3f32d42ce1ffd3bb430097',
      'fdeff1ebc27598a915af7cbe1360fea1' => 0,
      'e52c7d4b8ccc8fd7b8f7a59ca8e0e013' => 0,
      'e620912b6bfc590784848cf00c05b42f' => 0,
      'ffd4dd7c59102655f73303c040b08914' => 0,
      '4d6bb5d91d988f6e1575a5fb96ff9f23' => 0,
      '686f4a5ca4cc828a25e63e200104f2f2' => 0,
      '4e54a2646a6ab092340fd2eb6a600453' => 0,
      'a8cbec3ba69c8a6ba95ad7e2e4f45e67' => 0,
      'b6f96e1d58adbd211c6a14b2bbe8bf21' => 0,
      '0477aaf91878af69b08470773a1490d4' => 0,
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
  $translatables['atrium_members'] = array(
    t('Defaults'),
    t('Active users'),
    t('Blocked users'),
    t('Member directory'),
  );

  $views[$view->name] = $view;

  return $views;
}
