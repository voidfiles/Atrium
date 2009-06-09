<?php
/**
 * Override of views-view-fields.tpl.php
 * Adds a check for whether the field content is empty -- if so, bail and
 * do not display the wrapper markup.
 */
$excluded = array('atrium_profile');

if (get_class($view->style_plugin) == 'views_plugin_style_list' && !in_array($view->name, $excluded)) {
  $enable_grouping = TRUE;
  // Array of fields to move into lefthand column
  $left = array(
    'published',
    'picture',
    'name',
    'atrium_reader-title_1',
  );
  $grouped = array('left' => array(), 'right' => array());
  foreach ($fields as $id => $field) {
    $power_id = "{$view->name}-$id";
    if (in_array($id, $left)) {
      $grouped['left'][$id] = $field;
    }
    else if (in_array($power_id, $left)) {
      $grouped['left'][$power_id] = $field;
    }
    else {
      $grouped['right'][$id] = $field;
    }
  }
  // If the listing doesn't have any fields that will be grouped
  // left, we can safely fallback to default (non-grouped) formatting.
  if (empty($grouped['left'])) {
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
    <div class='grouped-<?php print $group ?>'>
  <?php endif; ?>

    <?php foreach ($fields as $id => $field): ?>
      <?php if (!empty($field->content)): ?>
      <?php if (!empty($field->separator)): ?>
        <?php print $field->separator; ?>
      <?php endif; ?>

      <<?php print $field->inline_html;?> class="views-field-<?php print $field->class; ?>">
        <?php if ($field->label): ?>
          <label class="views-label-<?php print $field->class; ?>">
            <?php print $field->label; ?>
          </label>
        <?php endif; ?>
          <?php
          // $field->element_type is either SPAN or DIV depending upon whether or not
          // the field is a 'block' element type or 'inline' element type.
          ?>
          <<?php print $field->element_type; ?> class="field-content"><?php print $field->content; ?></<?php print $field->element_type; ?>>
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
