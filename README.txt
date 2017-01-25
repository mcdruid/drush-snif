# USAGE

$ drush help switch-node-input-filters

Switch input filters on nodes of a given type.

Examples:
 drush snif Article basic_html full_html   Switch all Article nodes which currently use full_html to basic_html. 
 drush snif Blog wysiwyg                   Switch all Blog nodes to the wysiwyg filter.

Arguments:
 node-type                                 The type of node on which filters should be switched.                      
 to-filter                                 Switch nodes to this filter...                                             
 from-filter                               ...from this filter (optional - without this, all nodes will be switched).

Options:
 --dry-run                                 todo 
 --limit                                   todo

Aliases: snif


# INSTALLATION

To include a single drush commandfile you can use --include e.g.:

$ drush --include=/full/path/to/dir help snif

N.B. the include path is to the directory containing the file.

Alternatively, drush searches for commandfiles in a number of locations:

http://docs.drush.org/en/master/commands/#create-commandfiledrushinc

