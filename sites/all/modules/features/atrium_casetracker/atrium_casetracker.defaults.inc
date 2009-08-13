<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _atrium_casetracker_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'spaces',
    'attribute' => 'feature',
    'value' => 'casetracker',
    'node' => array(
      '0' => 'casetracker_basic_case',
      '1' => 'casetracker_basic_project',
    ),
    'menu' => 'casetracker',
    'views' => array(
      '0' => 'atrium_casetracker',
      '1' => 'atrium_casetracker_projects',
    ),
    'spaces' => array(
      'label' => 'Case Tracker',
      'description' => 'Provides an issue and task tracker',
      'menu' => array(
        '0' => array(
          'title' => 'Case Tracker',
          'href' => 'casetracker',
        ),
      ),
      'types' => array(
        '0' => 'og',
        '1' => 'user',
      ),
    ),
    'block' => array(
      'atrium_casetracker-book' => array(
        'module' => 'atrium_casetracker',
        'delta' => 'book',
        'weight' => -13,
        'region' => 'right',
      ),
      'atrium_casetracker-filters' => array(
        'module' => 'atrium_casetracker',
        'delta' => 'filters',
        'weight' => -12,
        'region' => 'right',
      ),
      'views_atrium_casetracker-block_2' => array(
        'module' => 'views',
        'delta' => 'atrium_casetracker-block_2',
        'weight' => -11,
        'region' => 'right',
      ),
      'views-atrium_casetracker-block_1' => array(
        'module' => 'views',
        'delta' => 'atrium_casetracker-block_1',
        'weight' => 11,
        'region' => 'content',
      ),
    ),
  );
  return $items;
}

/**
 * Helper to implementation of hook_menu_default_items().
 */
function _atrium_casetracker_menu_default_items() {
  $items = array();

  $items[] = array(
    'title' => 'Case Tracker',
    'path' => 'casetracker',
    'weight' => '0',
    'description' => 'The casetracker lets you assign tasks to yourself and others and track the progress on a project.',
  );
  // Translatables
  array(
    t('Case Tracker'),
    t('The casetracker lets you assign tasks to yourself and others and track the progress on a project.'),
  );


  return $items;
}

/**
 * Helper to implementation of hook_user_default_permissions().
 */
function _atrium_casetracker_user_default_permissions() {
  $permissions = array();

  // Exported permission: access case tracker
  $permissions[] = array(
    'name' => 'access case tracker',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: create cases
  $permissions[] = array(
    'name' => 'create cases',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: create projects
  $permissions[] = array(
    'name' => 'create projects',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  // Exported permission: edit own cases
  $permissions[] = array(
    'name' => 'edit own cases',
    'roles' => array(
      '0' => 'authenticated user',
      '1' => 'admin',
      '2' => 'manager',
    ),
  );

  // Exported permission: edit own projects
  $permissions[] = array(
    'name' => 'edit own projects',
    'roles' => array(
      '0' => 'admin',
      '1' => 'manager',
    ),
  );

  return $permissions;
}
