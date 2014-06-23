<?php
function lp_address_admin_setting_form($form,$form_state){

  $form['lp_country'] = array(
    '#type' => 'fieldset',
    '#title' => t('Country Settings'),
    '#collapsible' => TRUE,
  );
  $form['lp_pickup_time'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pickup time Settings'),
    '#collapsible' => TRUE,
  );
  $form['lp_state'] = array(
    '#type' => 'fieldset',
    '#title' => t('Backend  State Update features'),
    '#collapsible' => TRUE,
  );
  $countryinfo=lp_address_get_country_info();
  if(!is_array($countryinfo)){
    db_insert('uc_countries')
      ->fields(array(
        'country_id' => 8888,
        'country_name' => 'Live parcel',
        'country_iso_code_2' => 'LP',
        'country_iso_code_3' => 'LPL',
        'version' => 1,
      ))
      ->execute();
    $countryinfo= array( 'country_name' =>'live parcel',
      'country_iso_code_2' =>'LP',
      'country_iso_code_3' => 'LPL'); 
  }
  $form['lp_country']['country_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Liveparcels address country name'),
    '#default_value' => $countryinfo['country_name'],
    '#size'=>20,
    '#description'=>'country name',
  );
  $form['lp_country']['country_iso_code_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Liveparcels address country code'),
    '#default_value' => $countryinfo['country_iso_code_2'],
    '#maxlength'=>2,
    '#size'=>4,
    '#description'=>'Max 2 char',
  );
  $form['lp_country']['country_iso_code_3'] = array(
    '#type' => 'textfield',
    '#title' => t('Liveparcels address country code2'),
    '#default_value' =>$countryinfo['country_iso_code_3'],
    '#maxlength'=>3,
    '#size'=>4,
    '#description'=>'Max 3 char',
  );
   $form['lp_pickup_time']['limit_time'] = array(
    '#type' => 'textfield',
    '#title' => t('Liveparcels address pickup time begin time'),
    '#default_value' => variable_get('liveparcels_pickup_time',0),
    '#size'=>20,
    '#description'=>'default 0',
  );
  $active = array('insert' => t('keep Old and Add New States'), 'delete' => t('Delete Old and  Add New States'));
  $form['lp_state']['active'] = array(
    '#type' => 'radios',
    '#title' => t('State update'),
    '#default_value' => 'insert',
    '#options' => $active,
    '#description'=>t('keep Old and Add New States '));
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
