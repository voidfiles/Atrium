// $Id$

Drupal.behaviors.coldbrew = function (context) {
  $('#growl > div:not(.processed)').each(function() {
    $(this).addClass('processed');
    $('span.close', this).click(function() {
      $(this).parent().hide('fast');
    });
    if ($(this).is('.autoclose')) {
      $(this).animate(
        {opacity:.9},
        3000,
        'linear',
        function() {
          $(this).hide('fast');
        }
      );
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
}

// @TODO: write proper behavior attachers for this shiz
$(document).ready(function() {

  // Crossref
  $('div.xref div.label').click(function() {
    $(this).parents('div.xref').toggleClass('xref-active');
  });

  if ($('a.sidebar-toggle').size() > 0) {
    $('a.sidebar-toggle').click(function() {
      if ($(this).is('.selected')) {
        $(this).removeClass('selected');
        $('div.sidebar').addClass('hidden');
        $(this).parents('div.form').removeClass('form-sidebar').addClass('form-collapsed');
        $.cookie('atrium_sidebar', 0);
      }
      else {
        $(this).addClass('selected');
        $('div.sidebar').removeClass('hidden');
        $(this).parents('div.form').addClass('form-sidebar').removeClass('form-collapsed');
        $.cookie('atrium_sidebar', 1);
      }
      return false;
    });
  }

});
