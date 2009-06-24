<div class="messages admin-message">
  <?php // Changing the class on the link will make the javascript no longer function. ?>
  <?php print l(t('Close'), 'admin_message/close/'. $node->nid, array('attributes' => array('class' => 'admin-message-close', 'title' => t('Close this message')))); ?>
  <div class='message-label'><?php print $timestamp ?></div>
  <div class="message-content clear-block">
    <h2><?php print $title ?></h2>
    <?php print $content ?>
  </div>
</div>
