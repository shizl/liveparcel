<?php 


function lp_parcel_print_pdf($node){

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

  $content = '<div> Orderid: '.$orderid.'</div><div>Shipping fee: '.$price.'</div><div>Parcel dimension: '.$dimension.'</div><div>Package type: '.$package.'</div><div>Parcel weight: '.$weight.'</div><div>Authority to leave: '.$leave.'</div><div>Cash to collect: '.$collect.'</div><div>Customer reference: '.$ref.'</div><div>Pickup note: '.$p_note.'</div><div>Pickup date: '.$p_date.'</div><div>Pickup shift: '.$shift.'</div><div><div>Pickup address: </div><div><div><div>
  <div>
              <div>'.$p_address['name'].'</div>
              <div>'.$p_address['street'].'</div>
              <span>'.$p_address['postal_code'].'</span>
              <span>'.$p_address['city'].'</span>,<span>'.$p_address['province'].'</span>
              <div>'.$p_address['country_name'].'</div>
  </div>
  </div>
</div></div></div><div>Delivery note: '.$d_note.'</div><div><div>Delivery address: </div><div><div><div>
  <div>
              <div>'.$d_address['name'].'</div>
              <div>'.$d_address['street'].'</div>
              <span>'.$d_address['postal_code'].'</span>
              <span>'.$d_address['city'].'</span>,<span>'.$d_address['province'].'</span>
              <div>'.$d_address['country_name'].'</div>
 </div>
  </div>
</div></div></div>';

  require_once(drupal_get_path('module', 'lp_parcel') . '/html2fpdf/html2fpdf.php');
  $pdf=new HTML2FPDF(); 
  $pdf->SetAuthor(variable_get('site_name'));
  $pdf->SetCreator(variable_get('site_name', 'Drupal'));
  $pdf->SetTitle($node->title);
  $pdf->SetSubject($node->type);
  $pdf->SetFont('Arial', 'b', 20); 
  $pdf->AddPage();
  $pdf->AcceptPageBreak();  
  $pdf->Text('10','15',$node->title);  
  $pdf->SetFont('Arial', '', 16);
  $pdf->SetY(20);
  $pdf->WriteHTML($content);  
  echo $pdf->Output($node->title.'.pdf','D');

}
