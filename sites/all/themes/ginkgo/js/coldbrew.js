// $Id$

Drupal.behaviors.coldbrew = function (context) {
  // Hide messages
  $('div.messages span.close:not(.coldbrew)').each(function() {
    $(this).addClass('coldbrew').click(function() {
      $(this).parents('div.messages').slideUp('fast');
    });
  });

  // Help text
  if ($.cookie) {
    $('ul.dropdown li.help-help a:not(.coldbrew-help)').each(function() {
      if (!$.cookie('atrium_help')) {
        $.cookie('atrium_help', -1, {expires: 7});
      }
      switch($.cookie('atrium_help')) {
        case '1':
          $('ul.dropdown li.help-help').addClass('selected');
          $('div#block-help-help').addClass('selected').show();
          break;
      }
      $(this).addClass('coldbrew-help').click(function() {
        if ($(this).parent().is('.selected')) {
          $.cookie('atrium_help', 0);
        }
        else {
          $.cookie('atrium_help', 1);
        }
        return false;
      });
    });
  }

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
