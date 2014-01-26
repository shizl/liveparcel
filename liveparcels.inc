<?php

/**
 * @file
 * Store front page menu items.
 */
 
/**
 * Menu callback which provides the store administration overview page.
 */
function liveparcels_packageshow() {
    
	$rows['package'] = array(array('data' => '<div class="page-main">
	<div class="header-warning">
	  Warning: The calculator is unable to deterine the cost to deliver your parcel #3 to the location
	  you have entered. You may proceed and complete the checkout but the parcel will not be picked up untill you have accepted the price that the administrator will provide and notify you within one working day.
	</div>
	<div class="header-mess">
	  <div><h1>Postage calculator</h1></div>
	  <div class="header-content">
		  To obtain a free,instant quote on your shipment,please select the service you requires, enter the pickup/destination postcode/suburb as well as the parcel\'s details. You may enter the detail\'s of multiple parcels to send to or pick up from different places on this form. If you would like to proceed with the booking,press the Checkout button.
	  </div>
	</div>
	<div class="page-content">
	  <div class="page-content-title"><h2>Parcel Details</h2></div>
	  <div class="page-float">
      <div class="page-content-select"><h4>Please select the service you requires:</h4></div>
      <div class="page-content-choose">
		 <input class="deliver" type="radio" name="items" checked value="" >Deliver one or more items
         <input class="pick-up" type="radio" name="items" value="" >Pick-up one or more items
      </div>
      <div class="page-content-address" ><strong>Pickup post/suburb:</strong><input class="post-suburb" type="text" > </div>
      <div class="post-all">
          <div class="parcel"><strong>Parcel #1</strong></div>
        <div class="post-mess"> 
		 <table>
          <tr><td class="dimensions">Dimensions(cm):</td><td><input class="dim-first" type="text">X<input class="dim-second" type="text">X<input class="dim-three" type="text"></td></tr>
          <tr><td class="dimensional">Dimensional weight(kg):</td><td class="dimens-input"><input type="text" readonly>(this value is calculated automatically)</td></tr>
          <tr><td class="weight">weight(kg):</td><td class="wei-text"><input type="text" ></td></tr>
          <tr><td class="destination">Destination postcode/suburb:</td><td class="des-text"><input type="text" ></td></tr>
        </table>
        </div>
        <div class="post-btn">
             <div class="duplicate"><input type="button" name="duplicate" value="Duplicate"></div>
             <div class="add_new"><input type="button" name="add_new" value="Add New"></div>
        </div>
      </div>
      </div>
      </div>
      <div class="order">
          <div class="order-title">Order summary</div>
          <ul>
          <li class="order-first">Parcel #1: $25(2 ticket)</li>
          <li>Parcel #2: $25(2 ticket)</li>
          <li>Parcel #3: $25(2 ticket)</li>
          <div class="order-total">Total:$75(6 ticket)</div>
          </ul>
      </div>
      <div class="order-btn">
		  <input class="order-btn-first" type="button" name="modify" value="Modify">
	      <input type="button" name="checkout" value="Checkout">
      </div>
	  <div class="footer-note">
		Note:to calculate your parcel price, we use either the Dimensional
        Weight or the Actual Weight, whichever is the greater of the two values.	
	  </div>
  </div>
  <script language="javascript">
  (function($){
  function isFloat(key,str){
   var reg = parseFloat(str);
   if(reg>0){
	  $("."+key).val(reg);
	 return reg;   
   }else{
	 return 0;   
   }
  }
	function reckon(){
		var first = isFloat("dim-first",$(".dim-first").val());
		var second = isFloat("dim-second",$(".dim-second").val());
		var three = isFloat("dim-three",$(".dim-three").val());
		if( $(".dim-first").val() !== "" && $(".dim-second").val() !=="" && $(".dim-three").val() !==""){
		     if(first>0 && second>0 && three>0){				 
			    var volume = first*second*three*'.variable_get('liveparcels_factor',1).';
                volume=Math.round(volume*1000)/1000;
                if(volume>0){
                          $(".dimens-input input").val(volume);
                }else{
                    $(".dim-first").val("");
			    $(".dim-second").val("");
			    $(".dim-three").val("");
			    $(".dimens-input").html("Please input int or float value.");
                    }
			  
			 }else{
				$(".dim-first").val("");
			    $(".dim-second").val("");
			    $(".dim-three").val("");
			    $(".dimens-input").html("Please input int or float value.");
		     }
		}	 
	 }
     $(".dim-first").bind("blur",reckon);
     $(".dim-second").bind("blur",reckon);
     $(".dim-three").bind("blur",reckon);
     $(".wei-text input").blur(function(){
		var weight = isFloat("wei-text",$(".wei-text input").val());
		if($(".wei-text input").val()!==""){
		   if(weight>0){
		   	$(".wei-text input").val(weight);
	     }else{
		   	$(".wei-text input").val("");
		 }
       }
     });

  })(jQuery) </script>'));
  
	$build['liveparcels'] = array(
	'#theme' => 'table',
	  '#rows' => $rows,
	  '#attributes' => array('class' => array('live-parcels-status')),
	);

	 drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/package_show.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
	 
  return $build;
}
 function liveparcels_managepackage(){
	 $atype=!empty($_REQUEST['atype']) ? trim($_REQUEST['atype']):'';

	 	$result = db_query("SELECT `pprice` FROM `{liveparcels_package}` WHERE   ORDER BY `pprice` DESC", array(':id' => $order->order_id))->fetchField();
		foreach ($result as $row) {
			$items[$row->position] = array(
		
			  'pprice' => $row->pprice
			);
		}
				
        echo $
}
