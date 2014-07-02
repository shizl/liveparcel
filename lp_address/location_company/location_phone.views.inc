<?php

/**
 * @file
 * Views 3 support for Location company.
 */

/**
 * Implements hook_views_data().
 */
function location_company_views_data() {
  // ----------------------------------------------------------------
  // location_company table -- basic table information.

  // Define the base group of this table. Fields that don't
  // have a group defined will go into this field by default.

  $data['location_company']['table']['group'] = t('Location', array(), array('context' => 'geolocation'));

  // Join location_company to all the tables that would be useful
  $data['location_company']['table']['join'] = array(
    // location_company links to location via lid.
    'location' => array(
      'left_field' => 'lid',
      'field' => 'lid',
    ),
    // location_company links to node through location_instance via lid.
    'node' => array(
      'left_table' => 'location_instance',
      'left_field' => 'lid',
      'field' => 'lid',
    ),
    // location_company links to node_revision through location_instance via lid.
    'node_revision' => array(
      'left_table' => 'location_instance',
      'left_field' => 'lid',
      'field' => 'lid',
    ),
    // location_company links to users through location_instance via lid.
    'users' => array(
      'left_table' => 'location_instance',
      'left_field' => 'lid',
      'field' => 'lid',
    ),
  );

  // ----------------------------------------------------------------
  // location_company table -- fields

  $data['location_company']['company'] = array(
    'title' => t('Company'),
    'help' => t('The company name of the selected location.'),
    'field' => array(
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
      'empty field name' => t('None'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
      'allow empty' => TRUE,
    ),
  );

  return $data;
}