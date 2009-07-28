<?php 
/* Id */
/**
 * Extends the update parser to work with releases
 * 
 * The update parser uses version tag to index releases
 * We will use 'language' and 'tag'
 * 
 * @todo Update the server side and get rid of this
 */
// We do the include this way to be installer safe.
require_once './modules/update/update.fetch.inc';

class l10n_update_xml_parser extends update_xml_parser {
  function end($parser, $name) {
    switch ($name) {
      case 'RELEASE':
        unset($this->current_object);
        $this->current_project['releases'][$this->current_release['language']][$this->current_release['tag']] = $this->current_release;
        break;
      default:
        parent::end($parser, $name);
    }
  }
}