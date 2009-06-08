<div class='form <?php print $form_classes ?>'>

<?php if (!empty($form_message)) print $form_message ?>

<?php if ($sidebar): ?>
  <div id='right'><?php print drupal_render($sidebar) ?></div>
<?php endif; ?>

<div id='main'><div id='content' class='clear-block'>
  <?php
    $form_settings = variable_get('seed_forms', array());
    print !empty($form_settings['numbered']) ? seed_number_form($form) : drupal_render($form)
  ?>
</div></div>

<?php if ($buttons): ?>
  <div class='buttons clear-block'><?php print drupal_render($buttons) ?></div>
<?php endif; ?>

</div>
