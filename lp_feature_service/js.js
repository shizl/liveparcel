jQuery(document).ready(function(){

 jQuery('.del').click(function(){
    id = jQuery(this).attr('data-id');
    jQuery.post("/admin/liveparcels/adminsetting/feature_service/ajax",{id,id},function(data){
	if(data=='1'){
		location.reload();
	}
    },"json");

});

});
