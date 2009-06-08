<div class="admin-message sticky">

  <?php // Changing the class on the link will make the javascript no longer function. ?>
  <?php print l(t('Close'), 'admin_message/close/'. $node->nid, array('attributes'=>array('class' => 'admin-message-close', 'title' => t('Close this message')))); ?>

  <?php print node_view($node); ?>

</div>