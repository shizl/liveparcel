<?php
/**
 * @file
 * Store front page live parcels checkout.
 */
function liveparcels_addToCart(){

 //global $user;

        drupal_session_start(); 
    $parcels=trim($_REQUEST['parcelsPost']) !="" ?  trim($_REQUEST['parcelsPost']) :"";
    $action=trim($_REQUEST['action']) !="" ?  trim($_REQUEST['action']) :"";
    if($action != "addtocart" || $parcels==""){
            header("location:/liveparcels/parcel_quote");exit;
    }
     
    $cart_id=uc_cart_get_id();
     
    $data=array( 'shippable' =>'1','type'=>'live_parcel_product','module' => 'uc_product');
    db_delete('uc_cart_products')->condition('cart_id',$cart_id , '=')->execute();
    db_delete('liveparcels_cart')->condition('cart_id',$cart_id , '=')->execute();
    uc_cart_add_item(variable_get('liveparcels_product_id'), 1, $data,  $cart_id, variable_get('uc_cart_add_item_msg', TRUE));
   
    $parcelsdata =json_decode($parcels,true);
    db_insert('liveparcels_cart')->fields(array(
  'cart_id' => $cart_id,
  'parcel_info' =>serialize($parcelsdata)))->execute();

  if($parcelsdata['totals']==0) {
	variable_set('uc_payment_method_free_order_checkout',1);
   }else{
	variable_set('uc_payment_method_free_order_checkout',0);
   }
 //if($user->uid!=0){
  header("location:/cart/checkout");exit;
// }else{
 //  header('location:/user?destination=liveparcels/parcel_quote');
// }
}


