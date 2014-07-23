<?php


function get_user_skipped($user){

         $arr = array(); 
	$roles = db_query('select rid from {users_roles} where uid = '.$user->uid);
		foreach($roles as $role){
		  $arr[] = $role->rid;		
		}
    if(in_array(3,$arr)){
	return  get_admin_status_skipped_node();
    }else{
	   return drupal_get_form('get_user_status_skipped_node');
   }
}



function get_admin_status_skipped_node(){

$options = array();
$status = 'Skipped';
$result = db_query('select entity_id from {field_data_field_status_skipped} where field_status_skipped_value = :value' ,array(':value'=>$status));
  foreach($result as $entity){
     $node = node_load($entity->entity_id);
       $option['title'] = '<a href="/node/'.$entity->entity_id.'/edit">'.$node->title.'</a>';
       $option['price'] = $node->field_parcel_price['und'][0]['value'];
       $option['orderid'] = $node->field_parcel_order_id['und'][0]['value'];
       $option['size'] = $node->field_parcel_size['und'][0]['value'];
       $options[] = $option; 
  }
  $header =   array('title'=>t('Title'),'price'=>t('Price'),t('#Order Id'),t('Parcel Size'));
   $build['live_parcel_node_list'] = array(
    '#header'=>$header,
    '#theme' =>'table',
    '#rows'=>$options,
    '#empty' => t('No Results Found.'),
 );

  return $build;
}


function get_user_status_skipped_node($form,$form_state){

  $options = array();
  $status = 'Pending';
  $result = db_query('select entity_id from {field_data_field_status_skipped} where field_status_skipped_value = :value' ,array(':value'=>$status));

  foreach($result as $entity){
     $node = node_load($entity->entity_id);
     $option = array();


         $option['selectall'] = '<input type="checkbox" name ="checkbox[]" value ="'.$entity->entity_id.'"  />';
         $option['title'] = $node->title;
         $option['price'] = $node->field_parcel_price['und'][0]['value'];
         $option['orderid'] = $node->field_parcel_order_id['und'][0]['value'];
         $option['size'] = $node->field_parcel_size['und'][0]['value'];
         $options[] = $option; 
   }

  $header = array('select'=>t('Select'),'title'=>t('Title'),'price'=>t('Price'),t('#Order Id'),t('Parcel Size'));
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

  if (isset($_POST['checkbox'])){

    foreach($_POST['checkbox'] as $key=>$value){

	$total = $form['live_parcel_node_list']['#rows'][$key]['price'];

	$nid = db_query("select nid from {node} where type = 'live_parcel_product' and status=1 LIMIT 0 , 1")->fetchfield();
	$error_msg = FALSE;

	$node = node_load($nid);
	$product = uc_product_load($node);
	if (!$product)
	  // $error_msg = 'There was an error finding the free trial product. Please contact an administrator.';
	$product->nid = $node->nid; //we need to do this in order for the file downloads to work
	$product->qty = 1;
	$product->title = $node->title;
	 
	// Create the order and gather user information
	$order = uc_order_new($user->uid, 'completed');
	$order_id = $order->order_id;

	if (!$user->uid){
	  $names = split(' ', $user->name);
	  $last_name = array_pop($names);
	  $first_names = join(' ', $names);
	  $email = $user->mail;
	} else {
	 // $aid = _uc_addresses_get_default_address_id($user->uid);
	 // $address = _uc_addresses_db_get_address($user->uid, $aid);
	 // $first_names = $address->first_name;
	//  $last_name = $address->last_name;
	//  $email = $user->mail;
	}

	// Populate the order
	$order->products[] = $product;
	$order->payment_method = 'free_order';
	if (!isset($order->primary_email))
	  $order->primary_email = $email;

	//$order->billing_first_name = $first_names;
	//$order->billing_last_name = $last_name;

	$order->order_total = $total;

	//if (!$user->uid)
	 // $order->data['new_user']['pass'] = $form_state['values']['password'];
	 
	// Complete the sale
	uc_order_save($order);
	uc_cart_complete_sale($order, TRUE);
    }
  }

}

}

