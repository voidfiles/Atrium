// $Id: admin_message_form.js,v 1.2 2009/03/06 03:02:41 ultimateboy Exp $

// Global Killswitch
if (Drupal.jsEnabled) {
  $(document).ready(function() {  
    // Hide the other options if "Show message (sticky)" is not checked.    
    $("#admin-message-toggle")[['hide', 'show'][Number($("#edit-sticky")[0].checked)]]();
    
    $("#edit-sticky").click(function() {
      $("#admin-message-toggle")[['hide', 'show'][Number(this.checked)]]();
    });
  });
}
