if (Drupal.jsEnabled) {
  $(document).ready(function() {
    if ($('div.shoutform').size() > 0) {
      $("div.shoutform").parents('form').each(function() {
        $(this).submit(function() {
          var form = $(this);
          $("input.form-submit", form).mousedown();
          $("input.form-text", form).val('');
          return false;
        });
        $("input.form-submit", this).mousedown(function() {
          var form = $(this).parents('form');
          $("input.form-text, textarea", form).val('');
          return false;
        });
      });
    }
  });
};