// $Id: admin_message.js,v 1.2 2009/03/06 03:02:41 ultimateboy Exp $

// Global Killswitch
if (Drupal.jsEnabled) {
  $(document).ready(function() {  
    // Close
    $("#block-admin_message-admin_message a.admin-message-close").click(function() {
      var href = $(this).attr("href");
      $.get(href);
      $(this).parent().slideUp('fast');
      return false;
    });
  });
}
