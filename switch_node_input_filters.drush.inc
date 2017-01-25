<?php

/**
 * Implements hook_drush_command().
 */
function switch_node_input_filters_drush_command() {
  $items = array();

  $items['switch-node-input-filters'] = array(
    'description' => 'Switch input filters on nodes of a given type.',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'node-type' => 'The type of node on which filters should be switched.',
      'to-filter' => 'Switch nodes to this filter...',
      'from-filter' => '...from this filter (optional - without this, all nodes will be switched).',
    ),
    'options' => array(
       'limit' => 'todo',
       'dry-run' => 'todo',
    ),
    'required-arguments' => 2,
    'examples' => array(
      'drush snif Article basic_html full_html' => 'Switch all Article nodes which currently use full_html to basic_html.',
      'drush snif Blog wysiwyg' => 'Switch all Blog nodes to the wysiwyg filter.',
    ),
    'aliases' => array('snif'),
  );

  return $items;
}

function drush_switch_node_input_filters($node_type, $to_filter, $from_filter = NULL) {

  // @todo: check / sanitise inputs.

  // Get a list of nodes we want to switch
  $query = \Drupal::entityQuery('node')
    ->condition('type', $node_type);
    // @todo: --limit option
    // ->range(0, 2);
    // Run the query as user 1.
    // ->addMetaData('account', user_load(1));

    if (!is_null($from_filter)) {
      // Add a condition based on existing input filter
      $query->condition('body.format', $from_filter);
    }

  $nids = $query->execute();
  $matched_nodes = count($nids);
  $node_storage = \Drupal::entityManager()->getStorage('node');

  // Process one node at a time.
  $switched_nodes = 0;
  foreach ($nids as $nid) {
    $node = $node_storage->load($nid);
    $old_filter = $node->body->format;
    $log_args = array(
      '@nid' => $nid,
      '@old' => $old_filter,
      '@to'  => $to_filter,
    );
    if ($to_filter != $old_filter) {
      $node->body->format = $to_filter;
      $node->save();
      $switched_nodes++;
      drush_log(dt('Switched node nid=@nid from filter @old to @to.', $log_args));
    }
    else {
      drush_log(dt('Node nid=@nid was already using the @to filter.', $log_args));
    }
  }
  $log_args = array(
    '@type'     => $node_type,
    '@switched' => $switched_nodes,
    '@matched'  => $matched_nodes,
    '@filter'   => $to_filter,
  );
  drush_log(dt('Switched @switched @type nodes (out of @matched matches) to @filter.', $log_args), 'ok');

}
