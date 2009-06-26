// $Id$

Drupal.behaviors.coldbrew = function (context) {
  $('#growl > div:not(.processed)').each(function() {
    $(this).addClass('processed');
    $('span.close', this).click(function() {
      $(this).parent().hide('fast');
    });
    if ($(this).is('.autoclose')) {
      // If a message contains a link, autoclosing is probably a bad idea.
      if ($('a', this).size() > 0) {
        $(this).removeClass('autoclose');
      }
      else {
        // This essentially adds a 3 second pause before hiding the message.
        $(this).animate({opacity:.95}, 3000, 'linear', function() {
          $(this).hide('fast');
        });
      }
    }
  });

  // Dropdown blocks
  $('ul.dropdown a:not(.coldbrew)').each(function() {
    $(this).addClass('coldbrew').click(function() {
      var index = $('ul.dropdown a').index(this);
      var blockwrap = $('div.dropdown-blocks');
      if ($('div.block', blockwrap).eq(index).is('.selected')) {
        blockwrap.css('height', 'auto');
        $('div.block.selected', blockwrap).removeClass('selected').slideUp('fast');
        $('ul.dropdown li').removeClass('selected');
      }
      else if ($('div.block.selected', blockwrap).size() > 0) {
        var target = $('div.block', blockwrap).eq(index);
        var targeth = target.height();
        blockwrap.animate({'height': targeth}, "fast"),
        $('div.block.selected', blockwrap).removeClass('selected').hide();
        $('div.block', blockwrap).eq(index).addClass('selected').show();
        $('ul.dropdown li').removeClass('selected');
        $(this).parents('li').addClass('selected');
      }
      else {
        $('div.block', blockwrap).eq(index).addClass('selected').show('fast');
        $('ul.dropdown li').removeClass('selected');
        $(this).parents('li').addClass('selected');
      }
      return false;
    });
  });

  // Crossref
  $('div.xref div.label').each(function() {
    $(this). click(function() {
      $(this).parents('div.xref').toggleClass('xref-active');
    });
  });
}
