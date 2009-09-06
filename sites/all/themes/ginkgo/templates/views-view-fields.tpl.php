<?php
/**
 * Override of views-view-fields.tpl.php
 * Adds a check for whether the field content is empty -- if so, bail and
 * do not display the wrapper markup.
 */
$excluded = array('atrium_profile');

if (get_class($view->style_plugin) == 'views_plugin_style_list' && !in_array($view->name, $excluded)) {
  $enable_grouping = TRUE;

  // Array of field classes to group together
  $meta = array('date', 'user-picture', 'username');
  $grouped = array('meta' => array(), 'content' => array());
  foreach ($fields as $id => $field) {
    if (in_array($field->class, $meta)) {
      $grouped['meta'][$id] = $field;
    }
    else if (in_array("{$view->name}-{$field->class}", $meta)) {
      $grouped['meta'][$id] = $field;
    }
    else {
      $grouped['content'][$id] = $field;
    }
  }

  // If the listing doesn't have any fields that will be grouped
  // fallback to default (non-grouped) formatting.
  if (empty($grouped['meta'])) {
    $enable_grouping = FALSE;
    $grouped = array($fields);
  }
}
else {
  $enable_grouping = FALSE;
  $grouped = array($fields);
}
?>

<?php if ($enable_grouping): ?>
  <div class='grouped clear-block'>
<?php endif; ?>

<?php foreach ($grouped as $group => $fields): ?>

  <?php if ($enable_grouping): ?>
    <div class='grouped-<?php print $group ?> clear-block'>
  <?php endif; ?>

    <?php foreach ($fields as $id => $field): ?>

      <?php if (!empty($field->content)): ?>
        <?php if (!empty($field->separator)): ?>
          <?php print $field->separator; ?>
        <?php endif; ?>
        <<?php print $field->inline_html;?> class="views-field <?php print $field->class; ?>">
          <?php if ($field->label): ?>
            <label><?php print $field->label; ?></label>
            <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
          <?php else: ?>
            <?php print $field->content; ?>
          <?php endif; ?>
        </<?php print $field->inline_html;?>>
      <?php endif; ?>

    <?php endforeach; ?>

  <?php if ($enable_grouping): ?>
    </div>
  <?php endif; ?>

<?php endforeach; ?>

<?php if ($enable_grouping): ?>
  </div>
<?php endif; ?>
