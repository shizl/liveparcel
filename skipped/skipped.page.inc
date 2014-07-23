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

        $neworder = uc_order_new($user->uid);
        
	$neworder->order_total = $total;
	uc_order_save($neworder);
	uc_cart_complete_sale($neworder, TRUE);
        $node = node_load($value);
        $node->title = 'Order#'.$neworder->order_id.'Parcel#1';
        $node->field_parcel_order_id['und'][0]['value'] = $neworder->order_id;
        $node->field_status_skipped['und'][0]['value'] = 'Passing';
  
        node_save($node);
    }
  }else{

    drupal_set_message('Please select a row.','error');
  }

}

}

