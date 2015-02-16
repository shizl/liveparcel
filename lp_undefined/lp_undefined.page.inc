<?php


function get_user_skipped($user){

         $arr = array(); 
	$roles = db_query('select rid from {users_roles} where uid = '.$user->uid);
		foreach($roles as $role){
		  $arr[] = $role->rid;		
		}
	   return drupal_get_form('get_user_status_skipped_node');
}



function get_admin_status_skipped_node(){

$options = array();
$result = db_query('select entity_id from {field_data_field_fee_status} where field_fee_status_value = :value or field_fee_status_value= :value1' ,array(':value'=>'Undefined',':value1'=>'Pending'));
  foreach($result as $entity){
     $node = node_load($entity->entity_id);
       $option['title'] = '<a href="/node/'.$entity->entity_id.'">'.$node->title.'</a>';
       $option['price'] = $node->field_parcel_price['und'][0]['value'];
       $option['orderid'] = $node->field_parcel_order_id['und'][0]['value'];
       $option['size'] = $node->field_parcel_size['und'][0]['value'];
       $options[] = $option; 
  }
  $header =   array('title'=>t('Title'),'price'=>t('Price'),t('Order ID'),t('Parcel Size'));
   $build['live_parcel_node_list'] = array(
    '#header'=>$header,
    '#theme' =>'table',
    '#rows'=>$options,
    '#empty' => t('No Results Found.'),
 );

  return $build;
}


function get_user_status_skipped_node($form,$form_state){
global  $user;
  $options = array();

$result = db_query('select entity_id from {field_data_field_fee_status} where field_fee_status_value = :value or field_fee_status_value= :value1' ,array(':value'=>'Undefined',':value1'=>'Pending'));

  foreach($result as $entity){
     $node = node_load($entity->entity_id);
     $option = array();

 if($node!=null){
   if($node->uid == $user->uid){	

	if($node->field_fee_status['und'][0]['value']=="Pending"){
         $option['selectall'] = '<input type="radio" name ="radio" value ="'.$entity->entity_id.'"  />';
	}else{
	 $option['undefined'] = 'Undefined';
	}
         $option['title'] = '<a href="/node/'.$entity->entity_id.'">'.$node->title.'</a>';
         $option['price'] = $node->field_parcel_price['und'][0]['value'];
         $option['orderid'] = $node->field_parcel_order_id['und'][0]['value'];
         $option['size'] = $node->field_parcel_size['und'][0]['value'];
         $options[] = $option; 
     }
   }
 }
  $header = array('select'=>t('Select'),'title'=>t('Title'),'price'=>t('Price'),t('Order ID'),t('Parcel Size'));
  $form['live_parcel_node_list'] = array(
    '#header'=>$header,
    '#theme' =>'table',
    '#rows'=>$options,
    '#empty' => t('No Results Found.'),
 );

   $form['submit'] = array(
      '#type'=>'submit',
      '#value'=>t('Create new order'),
   ); 

  return $form;
}

function get_user_status_skipped_node_submit($form,&$form_state){

global $user;


if($user->uid == arg(1)){

  if (isset($_POST['radio'])){

 $value = $_POST['radio'];
	//$total = $form['live_parcel_node_list']['#rows'][$key]['price'];

//{"parcels":{"0":{"parcelnum":"Parcel#1","dimfirst":"22","dimsecond":"33","dimthree":"33","max":"33","dimenstext":"4.7916",
//"weighttext":"332.0","postfrom":"16_NSW_1001","postto":"1_NT_822","price":"$0","package_name":"Size4"}},
//"ptype":"2","totals":"0","discount":"0"}
  $nodedata = array();
   
        $node = node_load($value);
        $size = $node->field_parcel_size['und'][0]['value'];
        $size = str_replace(' ','x',$size);
        $sizearr =  explode('x',$size);
 	$max = 0;
          if($sizearr[0]>$max){
		$max = $sizearr[0];
	  }

	 if($sizearr[1]>$max){
		$max = $sizearr[1];
          }

	if($sizearr[2]>$max){
		$max = $sizearr[2];
          }      

$lid = $node->field_pickup_location['und'][0]['lid'];

$lid1 = $node->field_delivery_location['und'][0]['lid'];

$address = db_query('select city,province,postal_code from location where lid ='.$lid)->fetchAssoc();
$address1 = db_query('select city,province,postal_code from location where lid ='.$lid1)->fetchAssoc();
    $zone_number =  db_query('SELECT zone_number FROM  {liveparcels_zone_post} WHERE locality =:locality LIMIT 0 , 1',array(':locality'=>$address['city']))->fetchfield();

    $zone_number1 =  db_query('SELECT zone_number FROM  {liveparcels_zone_post} WHERE locality =:locality LIMIT 0 , 1',array(':locality'=>$address1['city']))->fetchfield();

        $nodedata = array(
	'parcels'=>array(
	   '0'=>array(
	        'parcelnum'=>$node->title,
		'dimfirst'=>$sizearr[0],
		'dimsecond'=>$sizearr[1],
		'dimthree'=>$sizearr[2],
		'max'=>$max,
		'dimenstext'=>0,
		'weighttext'=>$node->field_parcel_weight['und'][0]['value'],
		'postto'=>$zone_number.'_'.$address['province'].'_'.$address['postal_code'],
		'postfrom'=>$zone_number1.'_'.$address1['province'].'_'.$address1['postal_code'],
		'price'=> '$'.intval($node->field_parcel_price['und'][0]['value']),
		'package_name'=>empty($node->field_parcel_package_name['und'][0]['value'])?'':$node->field_parcel_package_name['und'][0]['value'],
              )),	
		'ptype'=>2,
		'totals'=>intval($node->field_parcel_price['und'][0]['value']),
		'discount'=>0,	
		);


  $action = 'addtocart';


  user_add_to_cart($nodedata,$action,$node->nid);

  }else{

    drupal_set_message('Please select a row.','error');
  }

}

}


function user_add_to_cart($parcelsdata,$action,$nid){
 
    drupal_session_start(); 
    $parcels= $parcelsdata !=null ? $parcelsdata :"";
    $action=trim($action) !="" ?  trim($action) :"";
    if($action != "addtocart" || $parcels==""){
            header("location:/liveparcels/parcel_quote");exit;
    }    
    $cart_id=uc_cart_get_id();
     
    $data=array( 'shippable' =>'1','type'=>'live_parcel_product','module' => 'uc_product');
    db_delete('uc_cart_products')->condition('cart_id',$cart_id , '=')->execute();
    db_delete('liveparcels_cart')->condition('cart_id',$cart_id , '=')->execute();
    uc_cart_add_item(variable_get('liveparcels_product_id'), 1, $data,  $cart_id, variable_get('uc_cart_add_item_msg', TRUE));
   
    db_insert('liveparcels_cart')->fields(array(
  'cart_id' => $cart_id,
  'parcel_info' =>serialize($parcelsdata)))->execute();

  $_SESSION['lp_node'] = $nid;
  $node = node_load($nid);
  $_SESSION['lp_order'] = $node->field_parcel_order_id['und'][0]['value'];
  if($parcelsdata['totals']==0) {
	variable_set('uc_payment_method_free_order_checkout',1);
   }else{
	variable_set('uc_payment_method_free_order_checkout',0);
   }
  header("location:/cart/checkout");exit;  

}