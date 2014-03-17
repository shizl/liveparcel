<?php
/**
 * @file
 * Store front page live parcels checkout.
 */
function liveparcels_addToCart(){
  
    $parcels=trim($_REQUEST['parcelsPost']) !="" ?  trim($_REQUEST['parcelsPost']) :"";
    $action=trim($_REQUEST['action']) !="" ?  trim($_REQUEST['action']) :"";
    if($action != "addtocart" || $parcels==""){
            header("location:/liveparcels/parcel_quote");exit;
    }
    $cart_id=uc_cart_get_id();
    $data='a:3:{s:9:"shippable";s:1:"1";s:4:"type";s:19:"live_parcel_product";s:6:"module";s:10:"uc_product";}';
    db_delete('uc_cart_products')->condition('cart_id',$cart_id , '=')->execute();
    db_delete('liveparcels_cart')->condition('cart_id',$cart_id , '=')->execute();
    uc_cart_add_item(variable_get('liveparcels_product_id'), 1, $data,  $cart_id, variable_get('uc_cart_add_item_msg', TRUE),false);
    $parcelsdata =json_decode($parcels,true);
    db_insert('liveparcels_cart')->fields(array(
  'cart_id' => $cart_id,
  'parcel_info' =>serialize($parcelsdata)))->execute();
  header("location:/cart/checkout");exit;  
}


