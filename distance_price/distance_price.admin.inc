<?php 


/**
* distance  menu items .
**/

function  distance_pages(){

  $menu = menu_get_item('admin/liveparcels/distance_config_page');
  $content = system_admin_menu_block($menu);
  $build['menu'] = array(
    '#theme' => 'admin_block_content',
    '#content' => $content,
  );

  return $build;

}

/**
* distance setting page
*/

function distance_setting(){

  drupal_add_js(drupal_get_path('module', 'distance_price') . '/js/distance.js');
  drupal_add_css(drupal_get_path('module', 'distance_price') . '/css/distance.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
 
 $rows['distance'] = array(array('data'=>'<div class="package-table"><div class="parcels-title">Define package maximum values and price</div><ul class="packagedata">
        <li id="phead"><div class="field-small">Position</div><div class="field">max distance (km)</div><div class="field">multiplier</div><div class="field">Edit/Delete</div></li>
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

$form['title'] = array(
 '#markup'=>'<div class="parcels-title">Distance option</div>',
);

$form['description'] = array(
  '#markup'=>'<p>Distance option descriotion</p>',
);
$form['distance_type'] = array(
  '#type'=>'radios',
  '#options' => array('Straight Distance','Google Route'),
  '#default_value'=>variable_get('distance_type'),
);

$form['google_regison'] = array(

  '#prefix' => '<div id="google-wrapper" style="'.(variable_get('distance_type')=="0"?"display:none":"display:block").'">',
  '#suffix' => '</div>', 

);

$form['google_regison']['restriction_title'] = array(
  '#markup'=>'<p>Restriction otpion</p>',
);
$form['google_regison']['distance_restriction'] = array(
  '#type'=>'checkboxes',
  '#options' => array('1'=>'tolls','2'=>'highways','3'=>'ferries','4'=>'indoor'),
  '#default_value'=>variable_get('distance_restriction'),
);

$form['google_regison']['unit_title'] = array(
  '#markup'=>'<p>Unit option</p>',
);

$form['google_regison']['distance_unit'] = array(
  '#type'=>'radios',
  '#options' => array('Metric (default) returns distances in kilometers and meters.','Imperial returns distances in miles and feet.'),
  '#default_value'=>variable_get('distance_unit'), 
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


foreach($result as $key=>$rst){
$td = '';
 foreach($package as $size){

  $td .= '<td>'.variable_get('uc_currency_sign','$').sprintf('%0.2f',$size*$rst->multiplier).'</td>';
 }

$tr .= '<tr><td>'.$rst->position.'</td><td>'.$rst->distance.' km</td>'.$td.'</tr>';

}

  $output ='<div class="parcels-title">Price table (calculated)</div><p>some description</p><table><thead><tr class="table-head"><th><a href="####" class="znumber">distance number <input type="hidden" class="oid" value=""><img typeof="foaf:Image" src="/sites/all/modules/live_parcel/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th><th><a href="####" class="zname">max distance<input type="hidden" class="oname" value="asc"><img typeof="foaf:Image" src="/sites/all/modules/live_parcel/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th>'.distances_packagename('name').'</tr></thead><tr>'.$tr.'</table>';

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

