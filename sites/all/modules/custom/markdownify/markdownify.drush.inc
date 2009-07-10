<?php
// $Id$

/**
 * @file
 *    Drush command to convert textile to markdown.
 *
 * 1) Goto admin/build/modules and enable markdown.
 * 2) Run the "drush markdownify" command.
 *
 * Note: On the Markdown format the code filter should come after markdown because 
 *    markdown has a built in ` ` tag for <code> </code> which we can then convert
 *    to a div and display properly.
 */

/**
 * Implementation of hook_drush_command().
 */
function markdownify_drush_command() {
  $items = array();
  $items['markdownify'] = array(
    'callback' => 'markdownify_callback',
    'description' => "Convert all textile content into markdown.",
  );
  return $items;
}

/**
 * Main conversion call back.
 */
function markdownify_callback() {
  $textile = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = 'Textile'"));
  $markdown = db_result(db_query("SELECT format FROM {filter_formats} WHERE name = 'Markdown'"));

  if (!$textile || !$markdown) {
    drush_die("Could not locate both a 'Textile' and 'Markdown' input format.");
  }

  // Slim down the textile filter.
  $result = db_query("SELECT * from {filters} WHERE format = %d", $textile);
  while ($row = db_fetch_object($result)) {
    if ($row->module == 'textile') {
      continue;
    }
    elseif ($row->module == 'filter' && $row->delta == 3) {
      continue;
    }
    else {
      db_query("DELETE FROM {filters} WHERE fid = %d", $row->fid);
    }
  }

  drush_print(markdownify_convert($textile, $markdown));
}

/**
 * Main conversion function
 * 
 * @param $oldformat
 *   The drupal format id of the content that needs to be converted. The format
 *   should have the textile filter enabled. This is used to select the content
 *   that will be converted.
 *
 * @param $newformat
 *   The drupal format to convet to. Should have markdown enabled.
 */
function markdownify_convert($oldformat, $newformat) {

  require_once dirname(__FILE__) .'/markdownify/markdownify_extra.php';

  $res = db_query("SELECT vid, format, body FROM {node_revisions} nr WHERE format = %d", $oldformat);
  $count = 0;
  while($node = db_fetch_object($res)) {
    $md = new Markdownify_Extra;
    $node->body = $md->parseString(_markdownify_fixtables(check_markup($node->body, $node->format, FALSE)));
    $node->teaser = node_teaser($node->body, $newformat);
    db_query("UPDATE {node_revisions} SET format = %d, body = '%s', teaser = '%s' WHERE vid = %d", $newformat, $node->body, $node->teaser, $node->vid);    
    $count ++;
  }

  $res = db_query("SELECT cid, format, comment FROM {comments} c WHERE format = %d", $oldformat);
  $countc = 0;
  while($comment = db_fetch_object($res)) {
    $md = new Markdownify_Extra;
    $comment->comment = $md->parseString(_markdownify_fixtables(check_markup($comment->comment, $comment->format, FALSE)));
    db_query("UPDATE {comments} SET format = %d, comment = '%s' WHERE cid = %d", $newformat, $comment->comment, $comment->cid);
    $countc ++;
  }

  return "$count nodes updated, $countc comments updated.";
}

/**
 * Makes the first <tr> have headers instead so markdown works with it.
 * 
 * Not robust (ie case dependent) but should play nice with the limited range
 * of output textile will produce
 */
function _markdownify_fixtables($string) {
  $stringarr = explode("<table", $string);
  for ($a=1; $a< count($stringarr); $a++) {
    $temp = explode("</tr>",$stringarr[$a]);
    $temp[0] = str_replace("<td","<th",$temp[0]);
    $temp[0] = str_replace("</td>","</th>",$temp[0]);
    $stringarr[$a] = implode("</tr>",$temp);
  }
  return implode("<table", $stringarr);
}