jQuery(document).ready(function(){
jQuery(".parcel_select_address").change(function(){
        var address_id=jQuery(this).val();
            address_id=address_id.split('_');
        if(address_id[2]>0){
                jQuery.post("/liveparcels/lp_address_update_render/ajax",{address_id:address_id[2]},function(data){
                    if(data){
                        jQuery("."+address_id[0]+"_first_name:eq("+address_id[1]+")").val(data.first_name);
                        jQuery("."+address_id[0]+"_last_name:eq("+address_id[1]+")").val(data.last_name);
                        jQuery("."+address_id[0]+"_company:eq("+address_id[1]+")").val(data.company);
                        jQuery("."+address_id[0]+"_street1:eq("+address_id[1]+")").val(data.street1);
                        jQuery("."+address_id[0]+"_street2:eq("+address_id[1]+")").val(data.street2);
                        jQuery("."+address_id[0]+"_phone:eq("+address_id[1]+")").val(data.phone);
                        jQuery("."+address_id[0]+"_address_name:eq("+address_id[1]+")").val(data.address_name);
                    }    
                },"json");
        }
    });  
    
    jQuery(".parcel_use_parcel").change(function(){
            var parcel_id=jQuery(this).val();
            parcel_id=parcel_id.split('_');
        jQuery("."+parcel_id[0]+"_first_name:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_first_name:eq("+parcel_id[2]+")").val());
        jQuery("."+parcel_id[0]+"_last_name:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_last_name:eq("+parcel_id[2]+")").val());
        jQuery("."+parcel_id[0]+"_company:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_company:eq("+parcel_id[2]+")").val());
        jQuery("."+parcel_id[0]+"_street1:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_street1:eq("+parcel_id[2]+")").val());
        jQuery("."+parcel_id[0]+"_street2:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_street2:eq("+parcel_id[2]+")").val());
        jQuery("."+parcel_id[0]+"_phone:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_phone:eq("+parcel_id[2]+")").val());
        jQuery("."+parcel_id[0]+"_address_name:eq("+parcel_id[1]+")").val(jQuery("."+parcel_id[0]+"_address_name:eq("+parcel_id[2]+")").val());
    });  


jQuery('#admin-add-parcels-form .save').click(function(){

 maxnum = jQuery('#parcel_warapper').find('>fieldset:last').attr('id');
 maxnum = maxnum.substr(maxnum.length-1,1);
 maxnum = parseInt(maxnum)+1;

 for(i=1;i<=maxnum;i++){

    if(jQuery('#edit-basic-info-'+i+' .size .form-item-length-'+i+' input').val().length==0){
      alert('#parcel'+i+' length not empty');
      return false;
    }else if(jQuery('#edit-basic-info-'+i+' .size .form-item-width-'+i+' input').val().length==0){
      alert('#parcel'+i+' width not empty');
      return false;
    }else if(jQuery('#edit-basic-info-'+i+' .size .form-item-height-'+i+' input').val().length==0){
      alert('#parcel'+i+' height not empty');
      return false;
    }else if(jQuery('#edit-basic-info-'+i+' .form-item-pweight-'+i+' input').val().length==0){
      alert('#parcel'+i+' weight not empty');
      return false;
    }else if(jQuery('.form-item-pickup-first-name-'+i+' input').val()==""){
      alert('#parcel'+i+' pickup first name not empty');
      return false;
    }else if(jQuery('.form-item-pickup-last-name-'+i+' input').val()==""){
      alert('#parcel'+i+' pickup last name not empty');
      return false;
    }else if(jQuery('.form-item-delivery-first-name-'+i+' input').val()==""){
      alert('#parcel'+i+' delivery first name not empty');
      return false;
    }else if(jQuery('.form-item-delivery-last-name-'+i+' input').val()==""){
      alert('#parcel'+i+' delivery last name not empty');
      return false;
    }else if(jQuery('.form-item-pickup-street1-'+i+' input').val()==""){
      alert('#parcel'+i+' pickup street1 not empty');
      return false;
    }else if(jQuery('.form-item-delivery-street1-'+i+' input').val()==""){
      alert('#parcel'+i+' delivery street1 not empty');
      return false;
    }else if(jQuery('#edit-parcel-price-'+i+' .form-item-price-'+i+' input').val().length==0){
      alert('#parcel'+i+' price not empty');
      return false;
    }else if(i==maxnum){
      return true;
    }

  }

});

});



function check_price(parcelnum){

dimfirst = jQuery('fieldset .size .form-item-length-'+parcelnum+' input').val();
dimfirst = parseFloat(dimfirst);
dimsecond = jQuery('fieldset .size .form-item-width-'+parcelnum+' input').val();
dimsecond = parseFloat(dimsecond);
dimthree = jQuery('fieldset .size .form-item-height-'+parcelnum+' input').val();
dimthree =parseFloat(dimthree);
        maxsize= 0; 
 	if(dimfirst > maxsize){
		maxsize = dimfirst; 
	}
	if(dimsecond > maxsize){
		maxsize = dimsecond;
	}
	if(dimthree > maxsize){
		maxsize = dimthree;  
	}

 dimenstext =  parseFloat(dimfirst)*parseFloat(dimsecond)*parseFloat(dimthree)*parseFloat(jQuery('.liveparcels_factor').val());
 weighttext =  jQuery('#edit-basic-info-'+parcelnum+' .form-item-pweight-'+parcelnum+' input').val();
 weighttext = parseFloat(weighttext);
postfrom =  jQuery('#edit-pickup-location-'+parcelnum+' .pickup_post').val();
 postto =  jQuery('#edit-delivery-location-'+parcelnum+' .delivery_post').val();

ajaxrequest = '{"parcelnum":"'+'Parcel#'+parcelnum+'","dimfirst":"'+dimfirst+'","dimsecond":"'+dimsecond+'","dimthree":"'+dimthree+'","max":"'+maxsize+'","dimenstext":"'+dimenstext+'","weighttext":"'+weighttext.toFixed(1)+'","postfrom":"'+postfrom+'","postto":"'+postto+'"}'; 
                jQuery.get("/admin/liveparcels/getzoneprice/ajax",{ajaxrequest:"["+ajaxrequest+"]",action:"updateprice"},function(zone){
  
                   if(zone != ""){ 
                         // $(".order ul").append(zone.parcels);
                          if( zone.error=="1"){
                              jQuery("#edit-parcel-price-"+parcelnum+" .display_pricre").html('<span style="color:red;">Warning: The calculator is unable to determine the cost to deliver one of your parcels to the location you have entered. You may proceed and complete the checkout but the parcel will not be picked up until you have accepted the price that the administrator will provide and notify you within one working day. </span>');
                            }else{	
                                  var pprice = 0;	
				  var packagename = '';		                               
                                  for (k in zone.pprice){
                                        pprice = zone.pprice[k]['pprice'];
                                        packagename = zone.pprice[k]['package_name'];
                                    }
		
                                 jQuery("#edit-parcel-price-"+parcelnum+" .display_pricre").html('<div> price: '+pprice+'</div>'+'<div>package name: '+packagename+'</div>'); 
			    }
				 jQuery("#edit-parcel-price-"+parcelnum+" .package_name").val(zone.pprice[0]['package_name']);
                                // alert(zone.pprice[0]['package_name']);
		  }

                },"json");
  
}

function copy_package(parcelnum){

 maxnum = jQuery('#parcel_warapper').find('>fieldset:last').attr('id');
 maxnum = maxnum.substr(maxnum.length-1,1);
 maxnum = parseInt(maxnum)+1;

 l = parcelnum!=null?jQuery('fieldset .form-item-length-'+parcelnum +' input').val():'';
 w = parcelnum!=null?jQuery('fieldset .form-item-width-'+parcelnum +' input').val():'';
 h = parcelnum!=null?jQuery('fieldset .form-item-height-'+parcelnum +' input').val():'';
 pw = parcelnum!=null?jQuery('fieldset .form-item-pweight-'+parcelnum +' input').val():'';
 cash = parcelnum!=null?jQuery('fieldset .form-item-cash-'+parcelnum +' input').val():'';
 customer_reference = parcelnum!=null?jQuery('fieldset .form-item-customer-reference-'+parcelnum +' input').val():'';
 delivery_note = parcelnum!=null?jQuery('fieldset .form-item-delivery-note-'+parcelnum +' textarea').val():'';
 pickup_note = parcelnum!=null?jQuery('fieldset .form-item-pickup-note-'+parcelnum+' textarea').val():'';
 pickup_date = parcelnum!=null?jQuery('fieldset .form-item-pickup-time-date-'+parcelnum+'-date input').val():jQuery('fieldset .form-item-pickup-time-date-1-date input').val();
 pickup_ampm = parcelnum!=null?jQuery('fieldset .form-item-pick-up-time-ampm-'+parcelnum+' select').val():'';

 if(parcelnum!=null){

 pickup_address = '';
     jQuery('fieldset #edit-pickup-'+parcelnum+'-select-address option').each(function(){
        address_id = jQuery(this).val().split('_');
	pickup_address += '<option value="'+address_id[0]+'_'+parseInt(parseInt(address_id[1])+1)+'_'+address_id[2]+'" >'+jQuery(this).text()+'</option>';
     });
 }else{
 pickup_address = '';
     jQuery('fieldset #edit-pickup-'+(maxnum-1)+'-select-address option').each(function(){
        address_id = jQuery(this).val().split('_');
	pickup_address += '<option value="'+address_id[0]+'_'+parseInt(maxnum-1)+'_'+address_id[2]+'" >'+jQuery(this).text()+'</option>';
     });
  
 }
 pickup_first_name = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-first-name-'+parcelnum+' input').val():'';
 pickup_last_name = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-last-name-'+parcelnum+' input').val():'';
 pickup_company = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-company-'+parcelnum+' input').val():'';
 pickup_street1 = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-street1-'+parcelnum+' input').val():'';
 pickup_street2 = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-street2-'+parcelnum+' input').val():'';
 pickup_city = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-city-'+parcelnum+' input').val():'';
 pickup_zone = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-zone-'+parcelnum+' input').val():'';
 pickup_country = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-country-'+parcelnum+' input').val():'';
 pickup_postal_code = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-postal-code-'+parcelnum+' input').val():'';
 pickup_phone = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .form-item-pickup-phone-'+parcelnum+' input').val():'';
 pickup_post = parcelnum!=null?jQuery('#edit-pickup-location-'+parcelnum+' .pickup_post').val():'';

if(parcelnum!=null){
 delivery_address = '';
     jQuery('fieldset #edit-delivery-'+parcelnum+'-select-address option').each(function(){
        address_id = jQuery(this).val().split('_');
	delivery_address += '<option value="'+address_id[0]+'_'+parseInt(parseInt(address_id[1])+1)+'_'+address_id[2]+'" >'+jQuery(this).text()+'</option>';
     });
 }else{
 delivery_address = '';
     jQuery('fieldset #edit-delivery-'+(maxnum-1)+'-select-address option').each(function(){
        address_id = jQuery(this).val().split('_');
	delivery_address += '<option value="'+address_id[0]+'_'+parseInt(maxnum-1)+'_'+address_id[2]+'" >'+jQuery(this).text()+'</option>';
     });

} 
 delivery_first_name = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-first-name-'+parcelnum+' input').val():'';
 delivery_last_name = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-last-name-'+parcelnum+' input').val():'';
 delivery_company = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-company-'+parcelnum+' input').val():'';
 delivery_street1 = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-street1-'+parcelnum+' input').val():'';
 delivery_street2 = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-street2-'+parcelnum+' input').val():'';
 delivery_city = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-city-'+parcelnum+' input').val():'';
 delivery_zone = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-zone-'+parcelnum+' input').val():'';
 delivery_country = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-country-'+parcelnum+' input').val():'';
 delivery_postal_code = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-postal-code-'+parcelnum+' input').val():'';
 delivery_phone = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .form-item-delivery-phone-'+parcelnum+' input').val():'';
 delivery_post = parcelnum!=null?jQuery('#edit-delivery-location-'+parcelnum+' .delivery_post').val():'';
 
 parcel_price = parcelnum!=null?jQuery('#edit-parcel-price-'+parcelnum+' .form-item-price-'+parcelnum+' input').val():'';
 package_name = parcelnum!=null?jQuery('#edit-parcel-price-'+parcelnum+' .package_name').val():'';


 var ht = '<fieldset class="collapsible form-wrapper collapse-processed" id="edit-parcels-'+maxnum+'"><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Hide</span> parcel#'+maxnum+'</a><span class="summary"></span></span></legend><div class="fieldset-wrapper"><fieldset class="collapsible form-wrapper collapse-processed" id="edit-basic-info-'+maxnum+'"><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Hide</span> Basic Info</a><span class="summary"></span></span></legend><div class="fieldset-wrapper"><div class="size"><div class="form-item form-type-textfield form-item-length-'+maxnum+'"><label for="edit-length-1">Parcel Size (cm) </label><input type="text" id="edit-length-'+maxnum+'" name="length_'+maxnum+'" value="'+l+'" size="5" maxlength="5" class="form-text"></div><div class="form-item form-type-textfield form-item-width-'+maxnum+'"><label for="edit-width-'+maxnum+'">X </label><input type="text" id="edit-width-'+maxnum+'" name="width_'+maxnum+'" value="'+w+'" size="5" maxlength="5" class="form-text"></div><div class="form-item form-type-textfield form-item-height-'+maxnum+'"><label for="edit-height-'+maxnum+'">X </label><input type="text" id="edit-height-'+maxnum+'" name="height_'+maxnum+'" value="'+h+'" size="5" maxlength="5" class="form-text"></div></div><input type="hidden" name="dweight_'+maxnum+'" value="" ><div class="form-item form-type-textfield form-item-pweight-'+maxnum+'"><label for="edit-pweight-'+maxnum+'">Parcel weight (kg) </label><input type="text" id="edit-pweight-'+maxnum+'" name="pweight_'+maxnum+'" value="'+pw+'" size="5" maxlength="5" class="form-text"></div><div class="form-item form-type-checkbox form-item-authority-'+maxnum+'"><input type="checkbox" id="edit-authority-'+maxnum+'" name="authority_'+maxnum+'" value="1" class="form-checkbox">  <label class="option" for="edit-authority-'+maxnum+'">Authority to leave </label></div><div class="form-item form-type-textfield form-item-cash-'+maxnum+'"><label for="edit-cash-'+maxnum+'">Cash to collect($) </label><input type="text" id="edit-cash-'+maxnum+'" name="cash_'+maxnum+'" value="'+cash+'" size="32" maxlength="128" class="form-text"></div><div class="form-item form-type-textfield form-item-customer-reference-'+maxnum+'"><label for="edit-customer-reference-'+maxnum+'">Customer reference </label><input type="text" id="edit-customer-reference-'+maxnum+'" name="customer_reference_'+maxnum+'" value="'+customer_reference+'" size="32" maxlength="128" class="form-text"></div><div class="form-item form-type-textarea form-item-delivery-note-'+maxnum+'"><label for="edit-delivery-note-'+maxnum+'">Delivery Note </label><div class="form-textarea-wrapper resizable textarea-processed resizable-textarea"><textarea id="edit-delivery-note-'+maxnum+'" name="delivery_note_'+maxnum+'" cols="60" rows="5" class="form-textarea">'+delivery_note+'</textarea><div class="grippie"></div></div></div><div class="form-item form-type-textarea form-item-pickup-note-'+maxnum+'"><label for="edit-pickup-note-'+maxnum+'">Pickup Note </label><div class="form-textarea-wrapper resizable textarea-processed resizable-textarea"><textarea id="edit-pickup-note-'+maxnum+'" name="pickup_note_'+maxnum+'" cols="60" rows="5" class="form-textarea">'+pickup_note+'</textarea><div class="grippie"></div></div></div><div class="container-inline-date"><div class="form-item form-type-date-popup form-item-pickup-time-date-'+maxnum+'"><label for="edit-pickup-time-date-'+maxnum+'">Pick up time date <span class="form-required" title="This field is required.">*</span></label><div id="edit-pickup-time-date-'+maxnum+'" class="date-padding"><div class="form-item form-type-textfield form-item-pickup-time-date-'+maxnum+'-date"><label for="edit-pickup-time-date-'+maxnum+'-datepicker-popup-0">Date </label><input type="text" id="edit-pickup-time-date-'+maxnum+'-datepicker-popup-0" name="pickup_time_date_'+maxnum+'[date]" value="'+pickup_date+'" size="20" maxlength="30" class="form-text" onclick="click_date_pop('+maxnum+')" ><div class="description"> E.g., 07/08/2014</div></div></div></div></div><div class="form-item form-type-select form-item-pick-up-time-ampm-'+maxnum+'"><label for="edit-pick-up-time-ampm-'+maxnum+'">Pick up time ampm </label><select class="pick_up_time_ampm form-select" id="edit-pick-up-time-ampm-'+maxnum+'" name="pick_up_time_ampm_'+maxnum+'"><option value="AM" selected="selected">AM</option><option value="PM">PM</option></select></div></div></fieldset><fieldset class="collapsible form-wrapper collapse-processed" id="edit-pickup-location-'+maxnum+'"><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Hide</span> Pickup Location</a><span class="summary"></span></span></legend><div class="fieldset-wrapper"><div class="form-item form-type-select form-item--pickup-'+maxnum+'-select-address"><label for="edit-pickup-'+maxnum+'-select-address">Select addresses </label><select class="admin_parcel_select_address form-select" id="edit-pickup-'+maxnum+'-select-address" name="pickup['+maxnum+'][select_address]" onchange="admin_parcel_select_address('+maxnum+',\'pickup\')">'+pickup_address+'</select></div><div class="form-item form-type-textfield form-item-pickup-first-name-'+maxnum+'"><label for="edit-first-name">First name <span class="form-required" title="This field is required.">*</span> </label><input class="pickup_first_name form-text" type="text" id="edit-first-name" name="pickup_first_name_'+maxnum+'" value="'+pickup_first_name+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-last-name-'+maxnum+'"><label for="edit-last-name">Last name <span class="form-required" title="This field is required.">*</span> </label><input class="pickup_last_name form-text" type="text" id="edit-last-name" name="pickup_last_name_'+maxnum+'" value="'+pickup_last_name+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-company-'+maxnum+'"><label for="edit-company">Company </label><input class="pickup_company form-text" type="text" id="edit-company" name="pickup_company_'+maxnum+'" value="'+pickup_company+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-street1-'+maxnum+'"><label for="edit-street1">Street address <span class="form-required" title="This field is required.">*</span> </label><input class="pickup_street1 form-text" type="text" id="edit-street1" name="pickup_street1_'+maxnum+'" value="'+pickup_street1+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-street2-'+maxnum+'"><label for="edit-street2">Street address2 </label><input class="pickup_street2 form-text" type="text" id="edit-street2" name="pickup_street2_'+maxnum+'" value="'+pickup_street2+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-city-'+maxnum+'"><label for="edit-city">City </label><input class="pickup_city form-text" type="text" id="edit-city" name="pickup_city_'+maxnum+'" value="'+pickup_city+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-zone-'+maxnum+'"><label for="edit-zone">State/Province </label><input class="pickup_zone form-text" type="text" id="edit-zone" name="pickup_zone_'+maxnum+'" value="'+pickup_zone+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-country-'+maxnum+'"><label for="edit-country">Country </label><input class="pickup_country form-text" type="text" id="edit-country" name="pickup_country_'+maxnum+'" value="'+pickup_country+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-postal-code-'+maxnum+'"><label for="edit-postal-code">Postal code </label><input class="pickup_postal_code form-text" type="text" id="edit-postal-code" name="pickup_postal_code_'+maxnum+'" value="'+pickup_postal_code+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-pickup-phone-'+maxnum+'"><label for="edit-phone">Phone number </label><input class="pickup_phone form-text" type="text" id="edit-phone" name="pickup_phone_'+maxnum+'" value="'+pickup_phone+'" size="32" maxlength="128"></div><input class="pickup_post" type="hidden" name="post" value="'+pickup_post+'"><input type="hidden" name="address_name" value=""><input type="hidden" name="default_shipping" value="0"><input type="hidden" name="default_billing" value="0"></div></fieldset><fieldset class="collapsible form-wrapper collapse-processed" id="edit-delivery-location-'+maxnum+'"><legend><span class="fieldset-legend"><a class="fieldset-title" href="#"><span class="fieldset-legend-prefix element-invisible">Hide</span> Delivery Location</a><span class="summary"></span></span></legend><div class="fieldset-wrapper"><div class="form-item form-type-select form-item--delivery-'+maxnum+'-select-address"><label for="edit-delivery-'+maxnum+'-select-address">Select addresses </label><select class="admin_parcel_select_address form-select" id="edit-delivery-'+maxnum+'-select-address" name="delivery['+maxnum+'][select_address]" onchange ="admin_parcel_select_address('+maxnum+',\'delivery\')">'+delivery_address+'</select></div><div class="form-item form-type-textfield form-item-delivery-first-name-'+maxnum+'"><label for="edit-first-name--2">First name <span class="form-required" title="This field is required.">*</span> </label><input class="delivery_first_name form-text" type="text" id="edit-first-name--2" name="delivery_first_name_'+maxnum+'" value="'+delivery_first_name+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-last-name-'+maxnum+'"> <label for="edit-last-name--2">Last name <span class="form-required" title="This field is required.">*</span> </label> <input class="delivery_last_name form-text" type="text" id="edit-last-name--2" name="delivery_last_name_'+maxnum+'" value="'+delivery_last_name+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-company-'+maxnum+'">  <label for="edit-company--2">Company </label> <input class="delivery_company form-text" type="text" id="edit-company--2" name="delivery_company_'+maxnum+'" value="'+delivery_company+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-street1-'+maxnum+'">  <label for="edit-street1--2">Street address <span class="form-required" title="This field is required.">*</span> </label> <input class="delivery_street1 form-text" type="text" id="edit-street1--2" name="delivery_street1_'+maxnum+'" value="'+delivery_street1+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-street2-'+maxnum+'">  <label for="edit-street2--2">Street address2 </label> <input class="delivery_street2 form-text" type="text" id="edit-street2--2" name="delivery_street2_'+maxnum+'" value="'+delivery_street2+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-city-'+maxnum+'">  <label for="edit-city--2">City </label> <input class="delivery_city form-text" type="text" id="edit-city--2" name="delivery_city_'+maxnum+'" value="'+delivery_city+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-zone-'+maxnum+'"> <label for="edit-zone--2">State/Province </label> <input class="delivery_zone form-text" type="text" id="edit-zone--2" name="delivery_zone_'+maxnum+'" value="'+delivery_zone+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-country-'+maxnum+'">  <label for="edit-country--2">Country </label><input class="delivery_country form-text" type="text" id="edit-country--2" name="delivery_country_'+maxnum+'" value="'+delivery_country+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-postal-code-'+maxnum+'">  <label for="edit-postal-code--2">Postal code </label><input class="delivery_postal_code form-text" type="text" id="edit-postal-code--2" name="delivery_postal_code_'+maxnum+'" value="'+delivery_postal_code+'" size="32" maxlength="100"></div><div class="form-item form-type-textfield form-item-delivery-phone-'+maxnum+'">  <label for="edit-phone--2">Phone number </label> <input class="delivery_phone form-text" type="text" id="edit-phone--2" name="delivery_phone_'+maxnum+'" value="'+delivery_phone+'" size="32" maxlength="128"></div><input class="delivery_post" type="hidden" name="post" value="'+delivery_post+'"><input type="hidden" name="address_name" value=""><input type="hidden" name="default_shipping" value="0"><input type="hidden" name="default_billing" value="0"></div></fieldset><fieldset class="form-wrapper" id="edit-parcel-price-'+maxnum+'"><legend><span class="fieldset-legend">Parcel Price</span></legend><div class="fieldset-wrapper"><div class="form-item form-type-textfield form-item-price-'+maxnum+'">  <label for="edit-price-1">Parcel Price($) </label><input type="text" id="edit-price-'+maxnum+'" name="price_'+maxnum+'" value="'+parcel_price+'" size="32" maxlength="128" class="form-text"></div><input type="hidden" value="'+package_name+'" name="package_name_'+maxnum+'" class="package_name"><div class="actions"><input type="button" class="form-submit check_price" onclick="check_price('+maxnum+')" value="check reference price"></div><input class="liveparcels_factor" type="hidden" name="parcels_factor" value="0.0002"><div class="display_pricre"></div></div></fieldset><input type="button" class="form-submit duplicate"  value="Duplicate" onclick="copy_package('+maxnum+')"><input type="button" class="form-submit delete"  value="Delete" onclick="delete_package('+maxnum+')"></div></fieldset>';


jQuery('#parcel_warapper').append(ht);

jQuery('.maxnum').val(maxnum);

}

function delete_package(parcelnum){

jQuery('#parcel_warapper').find('#edit-parcels-'+parcelnum).remove();
jQuery('.maxnum').val(parcelnum-1);

}

function admin_parcel_select_address(parcelnum,type){
        var address_id=jQuery('#edit-'+type+'-'+parcelnum+'-select-address').val();
            address_id=address_id.split('_');
        if(address_id[2]>0){
                jQuery.post("/liveparcels/lp_address_update_render/ajax",{address_id:address_id[2],type:'admin_create_order'},function(data){
                    if(data){
                        jQuery("."+address_id[0]+"_first_name:eq("+address_id[1]+")").val(data.first_name);
                        jQuery("."+address_id[0]+"_last_name:eq("+address_id[1]+")").val(data.last_name);
                        jQuery("."+address_id[0]+"_company:eq("+address_id[1]+")").val(data.company);
                        jQuery("."+address_id[0]+"_street1:eq("+address_id[1]+")").val(data.street1);
                        jQuery("."+address_id[0]+"_street2:eq("+address_id[1]+")").val(data.street2);
                        jQuery("."+address_id[0]+"_city:eq("+address_id[1]+")").val(data.city);
                        jQuery("."+address_id[0]+"_zone:eq("+address_id[1]+")").val(data.zonename);
                        jQuery("."+address_id[0]+"_country:eq("+address_id[1]+")").val(data.countryname);
                        jQuery("."+address_id[0]+"_postal_code:eq("+address_id[1]+")").val(data.postal_code);
                        jQuery("."+address_id[0]+"_phone:eq("+address_id[1]+")").val(data.phone);
                        jQuery("."+address_id[0]+"_address_name:eq("+address_id[1]+")").val(data.address_name);
                        jQuery("."+address_id[0]+"_post:eq("+address_id[1]+")").val(data.zone_number+'_'+data.zonename+'_'+data.postal_code);
                    }    
                },"json");
        }
}
function click_date_pop(parcelnum){
jQuery('#edit-pickup-time-date-'+parcelnum+'-datepicker-popup-0').datepicker();
}

