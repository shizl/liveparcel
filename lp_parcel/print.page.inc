<?php

function lp_parcel_print_pdf($node){
  drupal_add_css(drupal_get_path('module','lp_parcel').'/lp_parcel_print.css',array('media'=>'print'));
  drupal_add_css(drupal_get_path('module','lp_parcel').'/lp_parcel.css');
//javascript:window.print()

$output = array();

$output['print_left'] = array(
  '#prefix' => '<div class="print-left">',
  '#suffix' => '</div>',
);
$output['print_right'] = array(
  '#prefix' => '<div class="print-right">',
  '#suffix' => '</div>',
);

$output['print_left']['site_info'] = array(
  '#prefix' => '<div class="site_info">',
  '#suffix' => '</div>',
);

if (theme_get_setting('toggle_logo')) {
  $image = array(
    'path' => theme_get_setting('logo'),
    'alt' => 'my logo',
  );
  $output['print_left']['site_info']['logo'] =array(
    '#markup'=>theme('image', $image),
  );

}
$output['print_left']['site_info']['site_name'] = array(
  '#markup'=>'<div class="site_name"><strong>'.variable_get('site_name').'</strong></div>',
);

	$orderid = empty($node->field_parcel_order_id['und'][0]['value'])?'':$node->field_parcel_order_id['und'][0]['value'];
	$price = empty($node->field_parcel_price['und'][0]['value'])?'':$node->field_parcel_price['und'][0]['value'];
	$dimension = empty($node->field_parcel_size['und'][0]['value'])?'':$node->field_parcel_size['und'][0]['value'];
	$package = empty($node->field_parcel_package_name['und'][0]['value'])?'':$node->field_parcel_package_name['und'][0]['value'];
	$weight = empty($node->field_parcel_weight['und'][0]['value'])?'':$node->field_parcel_weight['und'][0]['value'];
	$leave = empty($node->field_authority_to_leave['und'][0]['value'])?'':$node->field_authority_to_leave['und'][0]['value'];
	$collect = empty($node->field_cash_to_collect['und'][0]['value'])?'':$node->field_cash_to_collect['und'][0]['value'];
	$ref = empty($node->field_customer_reference['und'][0]['value'])?'':$node->field_customer_reference['und'][0]['value'];
	$d_note = empty($node->field_delivery_note['und'][0]['value'])?'':$node->field_delivery_note['und'][0]['value'];
	$p_note = empty($node->field_pickup_note['und'][0]['value'])?'':$node->field_pickup_note['und'][0]['value'];
	$p_date = empty($node->field_pick_up_time['und'][0]['value'])?'':$node->field_pick_up_time['und'][0]['value'];
	$shift = empty($node->field_pick_up_time_ampm['und'][0]['value'])?'':$node->field_pick_up_time_ampm['und'][0]['value'];

	$p_address = empty($node->field_pickup_location['und'][0])?array():$node->field_pickup_location['und'][0];
	$d_address = empty($node->field_delivery_location['und'][0])?array():$node->field_delivery_location['und'][0];


$output['print_left']['delivery_info'] = array(
  '#markup' => '<div class="delivery_info"><div class="field-items"><div class="field-item even"><div class="location vcard">
  <div class="adr">
              <div class="company_name"><span>Company Name </span>'.$d_address['company'].'</div>
              <div class="fn"><span>Attention: </span>'.$d_address['name'].'</div>
              <div class="phone"><span>Phone: </span>'.$d_address['phone'].'</div>
              <div class="street-address">'.$d_address['street'].'</div>
              <div class="locality">'.$d_address['city'].'</div>
	      <span class="region">'.$d_address['province'].'</span>,<span class="postal-code">'.$d_address['postal_code'].'</span>
 </div> 
  </div>
</div></div></div>',
);
$output['print_right']['pickup_info'] = array(
  '#markup' =>'<div class="pickup_info"><div class="field-items"><div class="field-item even"><div class="location vcard">
  <div class="adr">
              <div class="company_name"><span>Company Name </span>'.$p_address['company'].'</div>
              <div class="fn"><span>Attention: </span>'.$p_address['name'].'</div>
              <div class="phone"><span>Phone: </span>'.$p_address['phone'].'</div>
              <div class="street-address">'.$p_address['street'].'</div>
              <div class="locality">'.$p_address['city'].'</div>
	      <span class="region">'.$p_address['province'].'</span>,<span class="postal-code">'.$p_address['postal_code'].'</span>
  </div>
      
  </div>
</div></div></div>',
);

$output['print_right']['detail_info'] = array(
  '#markup'=>'<div class="detail_info"><div>'.$node->title.'</div><div>Customer reference: '.$ref.'</div><div>Package type: '.$package.'</div><div>Parcel weight :'.$weight.'</div><div>Dimension: '.$dimension.'</div><div>Customer: '.$node->uid.'</div></div>',
);
$output['print_left']['note'] = array(
  '#markup'=>'<div class="note"><strong>Notes:</strong>e.g.leave at front door if no one home.</div>',
);
if($leave==1){
$output['print_left']['leave'] = array(
  '#markup'=>'<div class="leave">Authority to leave</div>',
);
}

$output['print_right']['qrcode'] = array(
  '#markup'=>'<div class="qrcode"><img src="/sites/default/files/'.$node->nid.$orderid.'.png" /></div>',
);

$output['print_button'] = array(
'#markup'=>'<div class="print-action"><input class="form-submit" type="button" value="Print" onclick="javascript:window.print();" /></div>',
);

 return $output;

}
