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


