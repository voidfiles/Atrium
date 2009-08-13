<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
  <head>
    <?php print $head ?>
    <?php print $styles ?>
    <title><?php print $head_title ?></title>
  </head>
  <body <?php print drupal_attributes($attr) ?>>

  <?php if ($admin) print $admin ?>

  <?php if ($messages || $console): ?>
    <div id='growl'>
      <?php print $messages; ?>
      <?php if ($logged_in && $console) print $console; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($header)): ?>
    <div id='header'><div class='limiter clear-block'>
      <?php print $header; ?>
    </div></div>
  <?php endif; ?>

  <div id='global' class='atrium-skin'><div class='limiter clear-block'>
    <?php if (!empty($site_name)): ?><h1 class='site-name atrium-skin'><?php print $site_name ?></h1><?php endif; ?>
    <?php if (!empty($picture)) print $picture ?>
    <?php if (!empty($user_links)) print $user_links ?>
    <?php if (!empty($dropdown_links)) print $dropdown_links ?>
  </div></div>

  <div id='branding' class='atrium-skin'><div class='limiter clear-block'>
    <?php if (!empty($spaces_logo)): ?>
      <?php print $spaces_logo ?>
    <?php elseif ($space_title): ?>
      <h1 class='space-title'><?php print $space_title ?></h1>
    <?php endif; ?>
    <?php if ($search_box) print $search_box ?>
  </div></div>

  <?php if ($primary_links): ?>
  <div id='navigation' class='atrium-skin'><div class='limiter clear-block'>
    <?php if (isset($primary_links)) print theme('links', $primary_links, array('id' => 'features-menu', 'class' => 'links primary-links')) ?>
    <?php if (isset($space_links)) print $space_links ?>
  </div></div>
  <?php endif; ?>

  <?php if ($title || $tabs): ?>
  <div id='page-header'><div class='limiter clear-block'>
    <div class='context-links'><?php if (!empty($context_links)) print $context_links ?></div>
    <?php if ($title): ?><h2 class='page-title'><?php print $title ?></h2><?php endif; ?>
    <?php if ($tabs) print $tabs ?>
  </div></div>
  <?php endif; ?>

  <div id='page'><div class='limiter clear-block'>

    <?php if ($tabs2) print $tabs2 ?>

    <?php if (!empty($custom_layout)): ?>
      <?php print $content ?>
    <?php else: ?>
      <?php if ($mission): ?><div class="mission"><?php print $mission ?></div><?php endif; ?>
      <div id='main' class='clear-block'>
          <div id='content' class='clear-block'><?php print $content ?></div>
      </div>
      <?php if ($right): ?>
        <div id='right' class='clear-block'><?php print $right ?></div>
      <?php endif; ?>
    <?php endif; ?>

  </div></div>

  <div id="footer"><div class='limiter clear-block'>
    <?php if (isset($secondary_links)) : ?>
      <?php print theme('links', $secondary_links, array('class' => 'links secondary-links')) ?>
    <?php endif; ?>
    <?php if (!empty($feed_icons)) print $feed_icons ?>
    <?php if (!empty($footer)) print $footer ?>
    <?php if (!empty($footer_message)) print $footer_message ?>
  </div></div>

  <?php print $scripts ?>
  <?php print $closure ?>

  </body>
</html>
