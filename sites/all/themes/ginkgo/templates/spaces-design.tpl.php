<?php if ($color): ?>
<style type='text/css'>
body.spaces-design #global,
body.spaces-design #branding,
body.spaces-design #navigation,
body.spaces-design #content h2.block-title,
body.spaces-design #navigation ul.space-links li a:hover { background-color:<?php print $color ?>; }

body.spaces-design #header,
body.spaces-design #console,
body.spaces-design #branding form input.form-text { background-color:<?php print $downshift ?>; }

body.spaces-design #navigation ul.space-links li a,
body.spaces-design #branding form input.form-text { border-color:<?php print $upshift ?>; }
</style>
<?php endif; ?>
