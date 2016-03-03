<?php 


/**
* distance setting page
*/

function distance_setting(){

$getunit = variable_get('distance_unit',0);
if($getunit=='1'){
  $unit = 'mi';
}else{
  $unit = 'km';
}

  drupal_add_js(drupal_get_path('module', 'lp_distance_price') . '/js/distance.js');
  drupal_add_css(drupal_get_path('module', 'lp_distance_price') . '/css/distance.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
 
 $rows['distance'] = array(array('data'=>'<div class="package-table"><div class="parcels-title">Define distance maximum value and associated price multiplier</div>
 <div><p>To use distance pricing, you must configure the pricing table below, the zone multipler here multiples with the base price of the package to arrive at the price the customer is charged.</p>
 <p>The first row (position 1) defines the price multiplier from 0 to the max distance, e.g. 10 km you have entered.</p></div>
 <ul class="packagedata">
        <li id="phead"><div class="field-small">Position</div><div class="field">Max distance ('.$unit.')</div><div class="field">Multiplier</div><div class="field">Edit/Delete</div></li>
        <li class="package-line" id="n0"><div class="field-small"><input type="hidden" class="oldposition small-text" value="0"><input type="text" class="position small-text" size="4"></div><div class="field"><input type="text" class="distance small-text"></div><div class="field"><input type="text" class="multiplier small-text"></div><div class="field"><a href="####" onclick="savenote(0,\'updateposition\')">Save</a></div></li></ul></div>'));
 
$rows['option'] = array(array('data'=>drupal_get_form('distances_option_form')));

$rows['table']  = array(array('data'=>distance_price_table()));


  $build['liveparcels'] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#attributes' => array('class' => array('live-parcels-status')),
      );

 return $build;

}

/**
* distance option form
*/

function  distances_option_form($form,&$form_state){


$form['google_autocomplete_address_key'] = array(
 '#title'=>t('Google API key'),
 '#description' => 'Entering your own Google API key allows you to track and pay for excess usage.',
 '#type'=>'textfield',
 '#default_value'=>variable_get('google_autocomplete_address_key',''),
);

$form['title'] = array(
 '#markup'=>'<div class="parcels-title">Distance calculation method</div>',
);

$form['description'] = array(
  '#markup'=>"<p>Straight line distance is the recommended default to avoid exceeding Google's free usage limit.</p>",
);
$form['distance_type'] = array(
  '#type'=>'radios',
  '#options' => array('Straight line distance','Google maps driving distance'),
  '#default_value'=>variable_get('distance_type',0),
);

$custom_var = variable_get('distance_type');
$form['google_regison'] = array(

  '#prefix' => '<div id="google-wrapper" style="'.(empty($custom_var) ?"display:none":"display:block").'">',
  '#suffix' => '</div>', 

);

$form['google_regison']['restriction_title'] = array(
  '#markup'=>'<p>Avoid</p>',
);
$form['google_regison']['distance_restriction'] = array(
  '#type'=>'radios',
  '#options' => array('None','Tolls','Highways','Ferries','Indoor'),
  '#default_value'=> variable_get('distance_restriction',0),
);

$form['unit_title'] = array(
  '#markup'=>'<p>Units</p>',
);

$form['distance_unit'] = array(
  '#type'=>'radios',
  '#options' => array('Metric (default) returns distance in kilometers and meters.','Imperial returns distance in miles and feet.'),
  '#default_value'=>variable_get('distance_unit',0), 
);
 return system_settings_form($form);

}




/**
* distance price table
*/
function distance_price_table(){

$result = db_query('select * from {liveparcels_distance} ');

$tr = '';

$package = distances_packagename('price');

$getunit = variable_get('distance_unit',0);
if($getunit=='1'){
  $unit = 'mi';
}else{
  $unit = 'km';
}

foreach($result as $key=>$rst){
$td = '';
 foreach($package as $size){

if(module_exists('lp_discount')){
 $td .= '<td>'.variable_get('uc_currency_sign','$').(sprintf('%0.2f',$size*$rst->multiplier)-lp_discount_get_pricing($size*$rst->multiplier)).'</td>';
}else{
  $td .= '<td>'.variable_get('uc_currency_sign','$').sprintf('%0.2f',$size*$rst->multiplier).'</td>';
 }

}

$tr .= '<tr><td>'.$rst->position.'</td><td>'.$rst->distance.' '.$unit.'</td>'.$td.'</tr>';

}

  $output ='<div class="parcels-title">Price table including your discount</div><p>The price table below is calculated based on your settings above. It shows you the price charged to deliver a parcel at the distance defined.</p><table><thead><tr class="table-head"><th><a href="####" class="znumber">Position<input type="hidden" class="oid" value=""><img typeof="foaf:Image" src="/sites/all/modules/live_parcel/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th><th><a href="####" class="zname">max distance<input type="hidden" class="oname" value="asc"><img typeof="foaf:Image" src="/sites/all/modules/live_parcel/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th>'.distances_packagename('name').'</tr></thead><tr>'.$tr.'</table>';

 return $output;
}




function distances_packagename($type ='name'){//price or name
  $resultpackage = db_query("SELECT `package_name`,`pprice` FROM `{liveparcels_package}` ORDER BY `position` ASC");

  if($type=='price'){
    $tprice=array();
    foreach($resultpackage as $pack){
      $tprice[]=$pack->pprice;
    }  
    return $tprice; 
  }elseif($type=='name'){
    $thead='';
    foreach($resultpackage as $pack){
      $thead.='<th>'.$pack->package_name.'</th>';
    } 
    return $thead;
  }



}

/**
* setting distance price ajax function 
*/

function distance_price_managepackage(){

  $atype=!empty($_REQUEST['atype']) ? trim($_REQUEST['atype']):'';
  if($atype=="packagelist"){
    $items=array();
    $result = db_query("SELECT * FROM `{liveparcels_distance}` ORDER BY `position` ASC");
    foreach ($result as $row) {
      $items[$row->position] = array(
          'position' => $row->position,
          'distance' => $row->distance,
          'multiplier' => $row->multiplier,
          );
    }

    echo json_encode($items);

  }elseif($atype=="updateposition"){
    db_query("UPDATE `{liveparcels_distance}` SET `position`=`position`+1 WHERE `position` >= '".$_REQUEST['position']."' ORDER BY `position` DESC");
    db_query("INSERT INTO `{liveparcels_distance}` VALUES('".$_REQUEST['position']."','".$_REQUEST['distance']."','".$_REQUEST['multiplier']."')");
    echo 1;

  }elseif($atype=="update"){
    db_query("UPDATE `{liveparcels_distance}` SET `distance`='".$_REQUEST['distance']."',`multiplier`='".$_REQUEST['multiplier']."' WHERE `position`='".$_REQUEST['oldposition']."'");	
    echo 1;

  }elseif($atype=="delete"){

    $result=db_query("DELETE FROM `{liveparcels_distance}` WHERE `position`='".$_REQUEST['position']."'");
    $result = db_query("SELECT `position` FROM `{liveparcels_distance}` WHERE `position` > '".$_REQUEST['position']."' ");

    if(count($result)>0){
      foreach ($result as $row) {
        db_query("UPDATE `{liveparcels_distance}` SET `position`=`position`-1 WHERE `position` >= '".$row->position."'  ORDER BY `position` ASC");
      } 		
    }	
    echo 1;
  }

}
