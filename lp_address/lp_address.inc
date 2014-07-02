<?php
function lp_address_admin_setting_form($form,$form_state){

  $form['lp_country'] = array(
    '#type' => 'fieldset',
    '#title' => t('Country Settings'),
    '#collapsible' => TRUE,
  );
  $form['lp_pickup_time'] = array(
    '#type' => 'fieldset',
    '#title' => t('Checkout settings'),
    '#collapsible' => TRUE,
  );
  $form['lp_state'] = array(
    '#type' => 'fieldset',
    '#title' => t('State field in Address book'),
    '#collapsible' => TRUE,
  );
  $countryinfo=lp_address_get_country_info();
  if(!is_array($countryinfo)){
    db_insert('uc_countries')
      ->fields(array(
        'country_id' => 8888,
        'country_name' => 'Australia',
        'country_iso_code_2' => 'AU',
        'country_iso_code_3' => 'AUS',
        'version' => 1,
      ))
      ->execute();
    $countryinfo= array( 'country_name' =>'live parcel',
      'country_iso_code_2' =>'LP',
      'country_iso_code_3' => 'LPL'); 
  }
  $form['lp_country']['country_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Country name'),
    '#default_value' => $countryinfo['country_name'],
    '#size'=>20,
    '#description'=>'The country this LiveParcels system is configured for.',
  );
  $form['lp_country']['country_iso_code_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Two letter country code'),
    '#default_value' => $countryinfo['country_iso_code_2'],
    '#maxlength'=>2,
    '#size'=>4,
    '#description'=>'<a href="http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2" target="_blank">ISO 3166-1 alpha-2</a>',
  );
  $form['lp_country']['country_iso_code_3'] = array(
    '#type' => 'textfield',
    '#title' => t('Three letter country code'),
    '#default_value' =>$countryinfo['country_iso_code_3'],
    '#maxlength'=>3,
    '#size'=>4,
    '#description'=>'<a href="http://en.wikipedia.org/wiki/ISO_3166-1_alpha-3" target="_blank">ISO 3166-1 alpha-3</a>',
  );
   $form['lp_pickup_time']['limit_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum pickup date'),
    '#default_value' => variable_get('liveparcels_pickup_time',0),
    '#size'=>20,
    '#description'=>'The minimum pickup date user can set during checkout. 0 means any date from today. 1 means any date from tomorrow. 2 means any date from the day after and so on.',
  );
  $active = array('insert' => t('Keep old and add new States'), 'delete' => t('Delete old and add new States'));
  $form['lp_state']['active'] = array(
    '#type' => 'radios',
    '#title' => t('State field),
    '#default_value' => 'insert',
    '#options' => $active,
    '#description'=>t('After updating postcode, you can choose to keep or delete old States in the LiveParcels address book by selecting the option above and then click Update.'));
  $form['lp_state']['update_state'] = array(
    '#type' => 'submit',
    '#value' => 'Update',
    '#submit'=>array('lp_address_update_zone_form_submit'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit'=>array('lp_address_country_setting_form_submit')
  );
  return $form;  
}
function lp_address_country_setting_form_submit($form,$form_state){
  variable_set('liveparcels_pickup_time',$form_state['values']['limit_time']);
  db_update("uc_countries")->fields(array(
    'country_name' =>$form_state['values']['country_name'] ,
    'country_iso_code_2' =>$form_state['values']['country_iso_code_2'],
    'country_iso_code_3' => $form_state['values']['country_iso_code_3'],
  ))->condition('country_id', 8888, '=')->execute();

}
function lp_address_update_zone_form_submit($form,$form_state){
  $oldstate=db_query("SELECT `zone_code` FROM `uc_zones` WHERE `zone_country_id`='8888'");
  $uc_state=array();
  foreach($oldstate as $zone){
    $uc_state[]=$zone->zone_code;
  }
  $newstate=db_query("SELECT `state` FROM `liveparcels_zone_post` GROUP BY `state`");
  $parcel_state=array();
  foreach($newstate as $zone){
    $parcel_state[]=$zone->state;
  }
  $updstate=array_intersect($uc_state,$parcel_state);
  if(count($updstate)>0){
    $insertstate=array_diff($parcel_state,$updstate);
  }else{
    $insertstate=$parcel_state;
  }
  $zones=array();
  foreach($insertstate as $state){
    $zones[]=array(8888, $state, $state);
  }
  $query = db_insert('uc_zones')->fields(array('zone_country_id', 'zone_code', 'zone_name'));
  foreach ($zones as $zone) {
    $query->values($zone);
  }
  $query->execute();
  if($form_state['values']['active']=='delete'){
    $deletestate=array_diff($uc_state,$updstate);
    if(count($deletestate)>0){
      db_delete('uc_zones')->condition('zone_code',$deletestate , 'in')->execute();
    }
  }
}