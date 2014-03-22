<?php
function lp_address_country_setting_form($form,$form_state){
    $countryinfo=db_query("SELECT `country_name`,`country_iso_code_2`,`country_iso_code_3` FROM `uc_countries` WHERE `country_id`='8888'")->fetchAssoc();
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
     $form['country_name'] = array(
      '#type' => 'textfield',
        '#title' => t('Liveparcels address country name'),
        '#default_value' => $countryinfo['country_name'],
      );
      $form['country_iso_code_2'] = array(
        '#type' => 'textfield',
        '#title' => t('Liveparcels address country code'),
        '#default_value' => $countryinfo['country_iso_code_2'],
      );
      $form['country_iso_code_3'] = array(
        '#type' => 'textfield',
        '#title' => t('Liveparcels address country code2'),
        '#default_value' =>$countryinfo['country_iso_code_3'],
      );
       $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
       '#submit'=>array('lp_address_admin_country_form_submit')
      );
      return $form;  
}
function lp_address_country_setting_form_submit($form,$form_state){
    db_update("uc_countries")->fields(array(
    'country_name' =>$form_state['values']['country_name'] ,
'country_iso_code_2' =>$form_state['values']['country_iso_code_2'],
      'country_iso_code_3' => $form_state['values']['country_iso_code_3'],
  ))->condition('country_id', 8888, '=')->execute();

}
function lp_address_update_zone_form($form,$form_state){
 
    $active = array('insert' => t('Insert state to uc address state'), 'delete' => t('Delete state to uc address state'));
      $form['settings']['active'] = array(
    '#type' => 'radios',
    '#title' => t('State update'),
    '#default_value' => 'insert',
    '#options' => $active,
    '#description' => t('Insert or delete state to uc address state.'));
    
       $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
       '#submit'=>array('lp_address_update_zone_form_submit')
      );
      return $form;  
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
    //print_r($insertstate);exit;
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