jQuery(document).ready(function(){

 jQuery('#checkout_reload').click(function(){

       user_mail = jQuery('#admin_order_settings-pane .form-item-panes-admin-order-settings-edit-parcel-user input').val();
       discount = jQuery('#admin_order_settings-pane .form-item-panes-admin-order-settings-edit-parcel-discount input').val();
       order_id = jQuery('#admin_order_settings-pane .admin_order_id').val();

  parr = Array();
       jQuery('#admin_order_settings-pane .cart-review .price input').each(function(){
           price = jQuery(this).val();
           parr.push(price);
       });

   jQuery.post("/liveparcels/reload_checkout_render/ajax",{parr:parr,user_mail:user_mail,discount:discount,order_id:order_id},function(data){
           window.location.reload();     
      },"json");

 });

});
