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

  jQuery("#uc-cart-checkout-form").submit(function(){


	jQuery('.address_error_message').remove();

	if(jQuery('#parcel_pickup-pane h2:last').text()!=''){
	 str1 = jQuery('#parcel_pickup-pane h2:last').text();
	 num1 = parseInt(str1.replace('Parcel#',''));
	}else{
	num1 = 1;
	}
	 for(i=0;i<num1;i++){
	pickup_city = jQuery('#parcel_pickup-pane').find('input[name="panes[parcel_pickup]['+i+'][field_parcel_pickup_address_data][address][city]"]').val();
	pickup_country = jQuery('#parcel_pickup-pane').find('input[name="panes[parcel_pickup]['+i+'][field_parcel_pickup_address_data][address][country]"]').val();
	
	pickup_zone_name = jQuery('#parcel_pickup-pane').find('input[name="panes[parcel_pickup]['+i+'][field_parcel_pickup_address_data][address][zone_name]"]').val();
	pickup_postal_code = jQuery('#parcel_pickup-pane').find('input[name="panes[parcel_pickup]['+i+'][field_parcel_pickup_address_data][address][postal_code]"]').val();

	if(pickup_city==''||pickup_country==''||pickup_zone_name ==''|| pickup_postal_code==''){
	jQuery('#parcel_pickup-pane').find('.form-item-panes-parcel-pickup-'+i+'-field-pickup-note').append('<div class="address_error_message" style="color:red;">Your address is not correct, please check it.</div>');
	
	if(pickup_city==''){
		jQuery('#parcel_pickup-pane').find('.parcel_data .city_'+i).css({'color':'red'});
	}
	if(pickup_country==''){
		jQuery('#parcel_pickup-pane').find('.parcel_data .country_'+i).css({'color':'red'});
	}
	if(pickup_zone_name==''){
		jQuery('#parcel_pickup-pane').find('.parcel_data .state_'+i).css({'color':'red'});
	}
	if(pickup_postal_code==''){
		jQuery('#parcel_pickup-pane').find('.parcel_data .postcode_'+i).css({'color':'red'});
	}

	}

      }


	if(jQuery('#parcel_delivery-pane h2:last').text()!=''){
	 str = jQuery('#parcel_delivery-pane h2:last').text();
	 num = parseInt(str.replace('Parcel#',''));
	}else{
	num = 1;
	}
	 for(i=0;i<num;i++){
	delivery_city = jQuery('#parcel_delivery-pane').find('input[name="panes[parcel_delivery]['+i+'][field_parcel_delivery_address_data][address][city]"]').val();
	delivery_country = jQuery('#parcel_delivery-pane').find('input[name="panes[parcel_delivery]['+i+'][field_parcel_delivery_address_data][address][country]"]').val();
	
	delivery_zone_name = jQuery('#parcel_delivery-pane').find('input[name="panes[parcel_delivery]['+i+'][field_parcel_delivery_address_data][address][zone_name]"]').val();
	delivery_postal_code = jQuery('#parcel_delivery-pane').find('input[name="panes[parcel_delivery]['+i+'][field_parcel_delivery_address_data][address][postal_code]"]').val();

	if(delivery_city==''||delivery_country==''||delivery_zone_name ==''|| delivery_postal_code==''){
	jQuery('#parcel_delivery-pane').find('.form-item-panes-parcel-delivery-'+i+'-field-delivery-note').append('<div class="address_error_message" style="color:red;">Your address is not correct, please check it.</div>');
	if(delivery_city==''){
		jQuery('#parcel_delivery-pane').find('.parcel_data .city_'+i).css({'color':'red'});
	}
	if(delivery_country==''){
		jQuery('#parcel_delivery-pane').find('.parcel_data .country_'+i).css({'color':'red'});
	}
	if(delivery_zone_name==''){
		jQuery('#parcel_delivery-pane').find('.parcel_data .state_'+i).css({'color':'red'});
	}
	if(delivery_postal_code==''){
		jQuery('#parcel_delivery-pane').find('.parcel_data .postcode_'+i).css({'color':'red'});
	}

	}

      }	

	if(jQuery('#uc-cart-checkout-form .address_error_message').html()== null){
		return true;

	}else{
		return false;
	}

  });


});



function preview(){

bdhtml=window.document.body.innerHTML;
sprnstr="<!--startprint1-->";
eprnstr="<!--endprint1-->";
prnhtml=bdhtml.substring(bdhtml.indexOf(sprnstr)+18); 

prnhtml=prnhtml.substring(0,prnhtml.indexOf(eprnstr));
window.document.body.innerHTML=prnhtml;
window.print();
var explorer = window.navigator.userAgent ;
if(explorer.indexOf("Chrome") >=0){
  window.location.href=window.location.href;
}else{
  window.document.body.innerHTML=bdhtml;
}

}


