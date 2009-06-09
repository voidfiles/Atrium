<p><?php print $help; ?></p>
<?php print $widgets; ?>
<?php foreach ($views as $view): ?>
  <table class="views-entry <?php print $view->classes; ?>">
    <tbody>
      <tr>
        <td class="view-name">
          <span class='right'>
            <?php if (!empty($view->tag)) print $view->tag; ?>
          </span>
          <?php print $help_type_icon; ?>
          <strong><?php print $view->name ?></strong>
          <?php print t('<em>@type</em> @base', array('@type' => $view->type, '@view' => $view->name, '@base' => $view->base)); ?>
        </td>          
        <td class="view-ops"><?php print $view->ops ?></td>
      </tr>
      <tr>
        <td>
          <?php if ($view->title): ?>
            <?php print t('Title: @title', array('@title' => $view->title)); ?> <br />
          <?php endif; ?>
          <?php if ($view->path): ?>
            <?php print t('Path: !path', array('!path' => $view->path)); ?> <br />
          <?php endif; ?>
          <?php if ($view->displays): ?>
            <em><?php print $view->displays; ?> </em><br />
          <?php endif; ?>
        </td>
        <td colspan="2" class="description">
          <?php print $view->description; ?>
        </td>
      </tr>
    </tbody>
  </table>
<?php endforeach; ?>
