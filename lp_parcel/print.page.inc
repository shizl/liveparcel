<?php

function lp_parcel_print_pdf($node){

  drupal_add_js(drupal_get_path('module','lp_address').'/lp_address.js');
//javascript:window.print()
  drupal_add_css(drupal_get_path('module','lp_parcel').'/lp_parcel.css');
  drupal_add_css(drupal_get_path('module','lp_parcel').'/lp_parcel_print.css',array('media'=>'print'));
$output = array();


$output['start'] = array(
  '#markup'=>'<!--startprint1-->',
);
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

        $service_type = empty($node->field_service_type['und'][0]['value'])?'':$node->field_service_type['und'][0]['value'];

$output['print_left']['delivery_info'] = array(
  '#markup' => '<div class="delivery_info"><div class="field-items"><div class="field-item even"><div class="location vcard">
  <div class="adr">
              <div class="fn"><span>Attention: </span>'.$d_address['name'].'</div>
            '.(empty($d_address['company'])?'':'<div class="company-name">'.$d_address['company'].'</div>').'
              <div class="street-address">'.$d_address['street'].'</div>
              <div class="locality">'.$d_address['city'].'</div>
	      <span class="region">'.$d_address['province'].'</span>, <span class="postal-code">'.$d_address['postal_code'].'</span>
            '.(empty($d_address['phone'])?'':'<div class="phone"><span>Phone: </span>'.$d_address['phone'].'</div>').'
 </div> 
  </div>
</div></div></div>',
);
$output['print_right']['pickup_info'] = array(
  '#markup' =>'<div class="pickup_info"><div class="field-items"><div class="field-item even"><div class="location vcard">
  <div class="adr">
              <div class="fn"><span>Attention: </span>'.$p_address['name'].'</div>
            '.(empty($p_address['company'])?'':'<div class="company-name">'.$p_address['company'].'</div>').'
              <div class="street-address">'.$p_address['street'].'</div>
              <div class="locality">'.$p_address['city'].'</div>
	      <span class="region">'.$p_address['province'].'</span>, <span class="postal-code">'.$p_address['postal_code'].'</span>
            '.(empty($p_address['phone'])?'':'<div class="phone"><span>Phone: </span>'.$p_address['phone'].'</div>').'
  </div>
      
  </div>
</div></div></div>',
);

if ($node->type=="live_parcel"){

        global $base_url;

        $account = user_load($node->uid);
	$role_array = '';
	foreach($account->roles as $key=>$role){
		$role_array .=  '"'.$key.'"'.':'. '"'. $role.'",';
	}

       $price = variable_get('uc_currency_sign','$').$price;
	$role_array = substr($role_array,0,strlen($role_array)-1);
        $data = '{"username":"'.$account->name.'","uid":'.$node->uid.',"nid":'.$node->nid.',"date":"'.date('Y-m-d',$node->created).'","title":"'.$node->title.'","url":"'.$base_url.'/node/'.$node->nid.'","Order ID":"'.$orderid.'","Shipping fee":"'.$price.'","Parcel dimension":"'.$dimension.'","Package type":"'.$package.'","Parcel weight":"'.$weight.'","Service type":"'.$service_type.'","Authority to leave":"'.$leave.'","Cash to collect":"'.$collect.'","Customer reference":"'.$ref.'","Delivery note":"'.$d_note.'","Pickup note":"'.$p_note.'","Pickup date":"'.$p_date.'","Pickup shift":"'.$shift.'","Pickup address":[{"name":"'.$p_address['name'].'","street":"'.$p_address['street'].'","city":"'.$p_address['city'].'","province":"'.$p_address['province'].'","postal_code":"'.$p_address['postal_code'].'","country":"'.$p_address['country_name'].'"}],"Delivery address":[{"name":"'.$d_address['name'].'","street":"'.$d_address['street'].'","city":"'.$d_address['city'].'","province":"'.$d_address['province'].'","postal_code":"'.$d_address['postal_code'].'","country":"'.$d_address['country_name'].'"}],"role":[{'.$role_array.'}]}';


        QRcode::png($data, 'sites/default/files/'.$node->nid.$orderid.'.png', "M", 3, 3);
        $code = '<img src="/sites/default/files/'.$node->nid.$orderid.'.png"/>';
}


$output['print_right']['qrcode'] = array(
  '#markup'=>'<div class="qrcode">'.$code.'</div>',
);
$output['print_left']['note'] = array(
  '#markup'=>'<div class="note"><strong>Notes: </strong>'.(empty($node->field_delivery_note['und'][0]['value'])?'':$node->field_delivery_note['und'][0]['value']).'</div>',
);


$output['print_left']['service_type'] = array(
  '#markup'=>'<div style="text-align:center;font-size:24px;font-style: italic;">'.(empty($node->field_service_type['und'][0]['value'])?'':$node->field_service_type['und'][0]['value']).'</div>',
);


if($leave==1){
$output['print_left']['leave'] = array(
  '#markup'=>'<div class="leave_wapper"><div class="leave"  style="'.(empty($node->field_service_type['und'][0]['value'])?'margin-top:20px':'').'">Authority to leave</div></div>',
);
}

$output['print_right']['detail_info'] = array(
  '#markup'=>'<div class="detail_info"><div>'.$node->title.'</div><div>Customer reference: '.$ref.'</div><div>Package type: '.$package.'</div><div>Parcel weight: '.$weight.'</div><div>Dimension: '.$dimension.'</div><div>Customer: '.user_load($node->uid)->name.'</div></div>',
);

$output['end'] = array(
  '#markup'=>'<!--endprint1-->',
);

$output['print_button'] = array(
  '#markup'=>'<div class="print-action"><input class="form-submit" type="button" value="Print" onclick="preview();" /></div>',
);

return $node->field_fee_status['und'][0]['value']=='Confirmed'?$output:'Permission denied because fee status not equal to confirmed.';
}
