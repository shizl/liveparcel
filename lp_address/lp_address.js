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

 
jQuery('#comments h2.comment-form').text('Add New Update');

 jQuery('.comment .submitted').each(function(){

author = jQuery(this).children('.commenter-name').html();
jQuery(this).children('.commenter-name').html('<span>Author: </span>'+author);

datehtml = jQuery(this).children('.comment-time').html();

jQuery(this).children('.comment-time').html('<span>Date: </span>'+datehtml);

 });


});







