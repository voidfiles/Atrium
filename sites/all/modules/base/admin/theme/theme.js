// $Id: theme.js,v 1.1 2009/06/03 06:50:54 yhahn Exp $

Drupal.behaviors.admin_theme = function(context) {
  // Toggle help
  $('a.help-toggle:not(.processed)').each(function() {
    $(this).addClass('processed').click(function() {
      $(this).toggleClass('help-expanded');
      $('#help').toggle();
      return false;
    });
  });

  // Toggle help
  $('a.subnav-toggle:not(.processed)').each(function() {
    $(this).addClass('processed').click(function() {
      $(this).toggleClass('subnav-expanded');
      $('#secondary-links').toggle();
      return false;
    });
  });

  // Fieldset
  $('div.fieldset:not(.processed)').each(function() {
    $(this).addClass('processed');
    if ($(this).is('.collapsible')) {
      if ($('input.error, textarea.error, select.error', this).size() > 0) {
        $(this).removeClass('collapsed');
      }
      // Note that .children() only returns the immediate ancestors rather than
      // recursing down all children.
      $(this).children('.fieldset-title').click(function() {
        if ($(this).parent().is('.collapsed')) {
          $(this).siblings('.fieldset-content').show();
          $(this).parent().removeClass('collapsed');
        }
        else {
          $(this).siblings('.fieldset-content').hide();
          $(this).parent().addClass('collapsed');
        }
        return false;
      });
    }
  });
}
