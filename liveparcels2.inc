<?php

/**
 * @file
 * Store front page menu items.
 */
 
/**
 * Menu callback which provides the store administration overview page.
 */
function liveparcels_packageshow() {

$parcels=liveparcels_getparcelsdata();

if(module_exists('lp_feature_service') && get_service_type_count()>1){
 $service_type = get_service_type();
//update 2015-08-13
$options = '';
 foreach($service_type as $service){
   $options .= '<option value="'.$service['id'].'">'.$service['type'].' (+'.($service['value']*100).'%)</option>'; 
 }

}

$parcel_info='';
 $postfrom='';
 $post='postto';
$p=0;
 $jsondata=liveparcels_getZonelistData();
if($parcels>0){

        if(strpos($parcels['parcels'][0]['parcelnum'],'Parcel')>0){
          $parcels['parcels'][0]['parcelnum'] = 'Parcel#1';
        } 


        $postfrom=$parcels['ptype']==2 ? $parcels['parcels'][0]['postfrom']:$parcels['parcels'][0]['postto'];
     $post=$parcels['ptype']==2 ? 'postto':'postfrom';

  foreach($parcels['parcels'] as $pid=>$parcel){
$p++;
       $parcel_info.=' <div class="post-all">
          <div class="parcel"><strong>'.$parcel['parcelnum'].'</strong>
            <div class="error-mess">Please fill in the correct information!</div>           
            <input type="button" value="X" '.($pid>0 ? 'style="display:block"':'').'>
          </div>
          <div class="post-mess"> 
		    <table>
            <tr>
             <td class="dimensions">Dimensions (cm):</td>
              <td>
              <input class="dim-first" type="text" value="'.$parcel['dimfirst'].'">X
              <input class="dim-second" type="text" value="'.$parcel['dimsecond'].'">X
              <input class="dim-three" type="text" value="'.$parcel['dimthree'].'">
             </td>
            </tr>
            <tr>
              <td class="dimensional">Dimensional weight (kg):</td>
              <td class="dimens-input">
                <input class="dimens-text" type="text" readonly  value="'.$parcel['dimenstext'].'">(this value is calculated automatically)
              </td>
            </tr>
            <tr>
               <td class="weight">Dead weight (kg):</td>
               <td class="wei-text">
                 <input class="weight-text" type="text"  value="'.$parcel['weighttext'].'">
               </td>
            </tr>
            <tr>
               <td class="destination">
                  <span class="package-to">'.($post=='postfrom' ? 'Pickup:':'Destination:').'</span>
               </td>
               <td class="des-text">
		<input id="destination" class="addressto" placeholder="Enter your address" onFocus="geolocate()" type="text"></input>
<input type="hidden"  id="route1">
<input type="hidden"  id="locality1">
<input  type="hidden" id="administrative_area_level_11">
<input type="hidden"  id="postal_code1">
<input type="hidden"  id="country1">

                </td>


              </tr>'.(module_exists('lp_feature_service')&&get_service_type_count()>1?'
	      <tr>
		<td class="service-type">Service (+fee):</td>
		<td><select class="optional-fees">'.$options.'</select></td>
	      </tr>':'').'
            </table>
          </div>
        <div class="post-btn">
             <div class="duplicate">
                <input class="form-submit" type="button" name="duplicate" value="Duplicate">
             </div>
        </div>
      </div>';
    }  
}

	$rows['package'] = array(array('data' => '<div class="page-main">
	<div class="header-warning">
	  '.variable_get('liveparcels_error_message').'
	</div>
	<div class="header-mess">

<!--	  <div><h1>Postage calculator</h1></div> -->

	  <div class="header-content">
	    '.variable_get('liveparcels_info_message').'
	  </div>
	</div>
	<div class="page-content">
	  <div class="page-content-title"><h2>Parcel Details</h2></div>
	  <div class="page-float">
      <div class="page-content-select"><h4>Please select the service 
      you requires:</h4></div>
      <div class="page-content-choose">
		 <input class="deliver" type="radio" disabled="disabled" name="items" '.( $parcels['ptype']==1 ? '':'checked').' value="2" >
		 Deliver one or more items
         <input class="pick-up" type="radio" disabled="disabled" name="items" '.($parcels['ptype']==1 ? 'checked':'').' value="1" >
         Pickup one or more items
      </div>
      <div class="page-content-address" >
           <strong class="package-from">'.($post=='postfrom' ? 'Destination:':'Pickup:').'</strong>
            <input id="autocomplete" placeholder="Enter your address"
             onFocus="geolocate()" type="text"></input>

<input type="hidden"  id="route">
<input type="hidden"  id="locality">
<input  type="hidden" id="administrative_area_level_1">
<input type="hidden"  id="postal_code">
<input type="hidden"  id="country">



      </div>
    '.($parcel_info<>'' ? $parcel_info:' <div class="post-all">
          <div class="parcel"><strong>Parcel#1</strong>
            <div class="error-mess">Please fill in the correct information!</div>           
            <input type="button" value="X">
          </div>
          <div class="post-mess"> 
		    <table>
            <tr>
             <td class="dimensions">Dimensions (cm):</td>
              <td>
              <input class="dim-first" type="text">X
              <input class="dim-second" type="text">X
              <input class="dim-three" type="text">
             </td>
            </tr>
            <tr>
              <td class="dimensional">Dimensional weight (kg):</td>
              <td class="dimens-input">
                <input class="dimens-text" type="text" readonly>(this value is calculated automatically)
              </td>
            </tr>
            <tr>
               <td class="weight">Dead weight (kg):</td>
               <td class="wei-text">
                 <input class="weight-text" type="text" >
               </td>
            </tr>
            <tr>
               <td class="destination">
                  <span class="package-to">'.($post=='postfrom' ? 'Pickup:':'Destination:').'</span>
               </td>
               <td class="des-text">
		<input id ="destination" class="addressto" placeholder="Enter your address" onFocus="geolocate()" type="text"></input>
<input type="hidden"  id="route1">
<input type="hidden"  id="locality1">
<input  type="hidden" id="administrative_area_level_11">
<input type="hidden"  id="postal_code1">
<input type="hidden"  id="country1">



                </td>
             </tr> 
		'.(module_exists('lp_feature_service')&&get_service_type_count()>1?'
	      	<tr>
		<td class="service-type">Service (+fee):</td>
		<td><select class="optional-fees">'.$options.'</select></td>
	      	</tr>':'').'
       
            </table>
          </div>
        <div class="post-btn">
             <div class="duplicate">
                <input class="form-submit" type="button" name="duplicate" value="Duplicate">
             </div>
        </div>
      </div>').'
          <div class="add_new">
               <input class="form-submit" type="button" name="add_new" value="Add new">
          </div>   
      </div>
      </div>
      <div class="order sidebar">
	 <div class="block">	
          <h2>Order summary</h2>
          <ul class="parcel-line">
          <li class="order-first">Pending...</li>
          </ul>
           '.(module_exists('lp_discount') ? '<div class="order-discount">Discount : Pending...</div>':'').'
          <div class="order-total">Total : Pending...</div>
           </div>
          </div>
          <div class="order-btn">
          <form action="/liveparcels/parcels_addtocart" method="POST" id="liveparcelsform">
           <input  type="hidden" name="action" value="addtocart">
          <input class="parcelsPost" type="hidden" name="parcelsPost" value="">
          </form>
		    <input class="form-submit check_parcels" type="button" name="modify" value="Update">
	        <input class="form-submit add_to_cart" type="button" name="checkout" value="Checkout">
          </div>  
	  <div class="footer-note">
	  '.variable_get('liveparcels_note_message').'
	  </div>
  </div>
 <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAemm83CciPsUdSgw6W5jtV-j5RHiNDnU4&signed_in=true&libraries=places&callback=initAutocomplete"
        async defer></script>

 <script type="text/javascript">

// This example displays an address form, using the autocomplete feature
// of the Google Places API to help users fill in the information.

var placeSearch, autocomplete,destination;
var componentForm = {

  route: "long_name",
  locality: "long_name",
  administrative_area_level_1: "short_name",
  country: "long_name",
  postal_code: "short_name"
};

var componentForm1 = {

  route1: "long_name",
  locality1: "long_name",
  administrative_area_level_11: "short_name",
  country1: "long_name",
  postal_code1: "short_name"
};



function initAutocomplete() {
  // Create the autocomplete object, restricting the search to geographical
  // location types.
  autocomplete = new google.maps.places.Autocomplete(
     (document.getElementById("autocomplete")),
      {types: ["geocode"]});

  destination  = new google.maps.places.Autocomplete(
     (document.getElementById("destination")),
      {types: ["geocode"]});

  // When the user selects an address from the dropdown, populate the address
  // fields in the form.
  autocomplete.addListener("place_changed", fillInAddress);
  destination.addListener("place_changed", fillInAddress1);
}

// [START region_fillform]
function fillInAddress() {

  // Get the place details from the autocomplete object.
  var place = autocomplete.getPlace();

  for (var component in componentForm) {
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (componentForm[addressType]) {
      var val = place.address_components[i][componentForm[addressType]];
      document.getElementById(addressType).value = val;
    }
  }

}

function fillInAddress1() {

  var place = destination.getPlace();

  for (var component in componentForm1) {
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];

    if (componentForm1[addressType+"1"]) {
      var val = place.address_components[i][componentForm1[addressType+"1"]];
      document.getElementById(addressType+"1").value = val;
    }

  }

}


// [END region_fillform]

// [START region_geolocation]

function geolocate() {
  if (navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(function(position) {
      var geolocation = {
        lat: position.coords.latitude,
        lng: position.coords.longitude
      };
      var circle = new google.maps.Circle({
        center: geolocation,
        radius: position.coords.accuracy
      });
      autocomplete.setBounds(circle.getBounds());
      destination.setBounds(circle.getBounds());
    });
  }

}
// [END region_geolocation]


  (function($){
  var zonedata='.( $jsondata<>'' ? $jsondata:'').';

document.onreadystatechange = subSomething;

function subSomething() { 
if(document.readyState == "complete") {
  $(".post-suburb").removeAttr("disabled");
  $(".deliver").removeAttr("disabled");
  $(".pick-up").removeAttr("disabled");

}else{
  $(".post-suburb").attr("disabled","disabled");
  $(".deliver").addr("disabled","disabled");
  $(".pick-up").addr("disabled","disabled");
}

}
   function isFloat(oNum){

	  if(!oNum) return false;

	  var strP=/^\d+(\.\d+)?$/;

	  if(!strP.test(oNum)) return false;

	  try{

	  	if(parseFloat(oNum)!=oNum) return false;

	  }catch(ex){

	    return false;

	  }

	  return true;

	}
      function checknull(f){
          var error=0;
		 var first  = $(".post-all:eq("+(f-1)+")").find(".dim-first").val();
		 var second = $(".post-all:eq("+(f-1)+")").find(".dim-second").val();
		 var three  = $(".post-all:eq("+(f-1)+")").find(".dim-three").val();
		 var weight = $(".post-all:eq("+(f-1)+")").find(".weight-text").val();
		 var dimens = $(".post-all:eq("+(f-1)+")").find(".dimens-text").val();
		 var postto = $(".post-all:eq("+(f-1)+")").find(".pnum-to").val();
		 var posttos = $(".post-all:eq("+(f-1)+")").find(".postcode-suburb").val();
		 if(postto == ""){
             error=1;
	           $(".post-all:eq("+(f-1)+")").find(".postcode-suburb").css("border","1px dashed red");
	           $(".post-all:eq("+(f-1)+")").find(".error-mess").show();
		 }else{
		       $(".post-all:eq("+(f-1)+")").find(".postcode-suburb").css("border","1px solid #ccc");
		 }
		if(first !== "" && second !== "" && three !== "" 
		   && weight !== "" && dimens !== "" && postto !== ""){
		        $(".post-all:eq("+(f-1)+")").find(".error-mess").hide();       
		}  
		 
			if(isFloat(first) && isFloat(second) && isFloat(three)){
		         var volume = parseFloat(first) * parseFloat(second) * parseFloat(three)*
		         '.variable_get('liveparcels_factor',1).';
		         var Pvolume = volume.toFixed(4);
		         $(".post-all:eq("+(f-1)+")").find(".dimens-text").val(Pvolume);  
		     }   
				 if(!isFloat(first)){
                     error=1;		 
					$(".post-all:eq("+(f-1)+")").find(".dim-first").css("border","1px dashed red");
					$(".post-all:eq("+(f-1)+")").find(".error-mess").show();
				 }else{
					$(".post-all:eq("+(f-1)+")").find(".dim-first").css("border","1px solid #ccc");
				 }
	         
				 if(!isFloat(second)){
                     error=1;
					$(".post-all:eq("+(f-1)+")").find(".dim-second").css("border","1px dashed red");
					 $(".post-all:eq("+(f-1)+")").find(".error-mess").show();
				 }else{
					$(".post-all:eq("+(f-1)+")").find(".dim-second").css("border","1px solid #ccc"); 
				}
	         
				 if(!isFloat(three)){
                     error=1;
					$(".post-all:eq("+(f-1)+")").find(".dim-three").css("border","1px dashed red");
					$(".post-all:eq("+(f-1)+")").find(".error-mess").show();
				 }else{
					$(".post-all:eq("+(f-1)+")").find(".dim-three").css("border","1px solid #ccc"); 
				 }
	      
				 if(!isFloat(weight)){
                      error=1;
					 $(".post-all:eq("+(f-1)+")").find(".error-mess").show();
					 $(".post-all:eq("+(f-1)+")").find(".weight-text").css("border","1px dashed red");
				   }else{
                      $(".post-all:eq("+(f-1)+")").find(".weight-text").css("border","1px solid #ccc"); 
				   }
			  
				 if(!isFloat(dimens)){
                      error=1;
					 $(".post-all:eq("+(f-1)+")").find(".error-mess").show();
					 $(".post-all:eq("+(f-1)+")").find(".dimens-text").css("border","1px dashed red");
				   }else{
                      $(".post-all:eq("+(f-1)+")").find(".dimens-text").css("border","1px solid #ccc"); 
				   }
			     if(posttos ==""){
			       $(".post-all:eq("+(f-1)+")").find(".pnum-to").val("");
			     }
		    if(isFloat(first) && isFloat(second) && isFloat(three) && isFloat(weight) && isFloat(dimens)){
		         $(".post-all:eq("+(f-1)+")").find(".error-mess").hide();
		}
        return error;     
	  }
	  $(".post-all input").blur(function(){
		 var first = $(this).parent("td").find(".dim-first").val();
		 var second = $(this).parent("td").find(".dim-second").val();
		 var three = $(this).parent("td").find(".dim-three").val();
		 var weight = $(this).parent("td").find(".weight-text").val();
		 var dimens  = $(this).parent("td").find(".dimens-text").val();
		 var postto = $(this).parent("td").find(".pnum-to").val();
		 var posttos = $(this).parent("td").find(".postcode-suburb").val();
		 var cla = $(this).attr("class");
	     if(cla == "dim-first" || cla == "dim-second" || cla == "dim-three"){ 
			if(isFloat(first) && isFloat(second) && isFloat(three)){
		         var volume = parseFloat(first) * parseFloat(second) * parseFloat(three)*
		         '.variable_get('liveparcels_factor',1).';
		         var Pvolume = volume.toFixed(4);
	             $(this).parent("td").parent("tr").next("tr")
	             .children("td").find(".dimens-text").val(Pvolume);  
		     }
		     if( cla == "dim-first"){ 	    
				 if(!isFloat(first)){		 
					$(this).parent("td").find(".dim-first").css("border","1px dashed red");
					 $(this).parent("td").parent("tr").parent("table").parent("div")
					 .next("div").find(".error-mess").show();
					 return false;
					 
				 }else{
					$(this).parent("td").find(".dim-first").css("border","1px solid #ccc");
				 }
	         }
	         if(cla == "dim-second" ){
				 if(!isFloat(second)){
					$(this).parent("td").find(".dim-second").css("border","1px dashed red");
					 $(this).parent("td").parent("tr").parent("table").parent("div")
					 .next("div").find(".error-mess").show();
					 return false;
					 
				 }else{
					$(this).parent("td").find(".dim-second").css("border","1px solid #ccc"); 
				}
	         }
	         if(cla == "dim-three"){
				 if(!isFloat(three)){
					$(this).parent("td").find(".dim-three").css("border","1px dashed red");
					 $(this).parent("td").parent("tr").parent("table").parent("div")
					 .next("div").find(".error-mess").show();
					 return false;
					 
				 }else{
					$(this).parent("td").find(".dim-three").css("border","1px solid #ccc"); 
				 }
	         }
	     } 
			 if(cla =="weight-text"){
				 if(isFloat(weight)){
					 $(this).parent("td").find(".weight-text").css("border","1px solid #ccc"); 
				   }else{
					 $(this).parent("td").parent("tr").parent("table").parent("div")
					 .next("div").find(".error-mess").show();
					 $(this).parent("td").find(".weight-text").css("border","1px dashed red");
					 return false;
				   }
			  } 
			   if(cla =="dimens-text"){
				 if(isFloat(dimens)){
					 $(this).parent("td").find(".dimens-text").css("border","1px solid #ccc"); 
				   }else{
					 $(this).parent("td").parent("tr").parent("table").parent("div")
					 .next("div").find(".error-mess").show();
					 $(this).parent("td").find(".dimens-text").css("border","1px dashed red");
					 return false;
				   }
			  } 
			  if(cla == "postcode-suburb"){
			     if(posttos ==""){
			       $(this).parent("td").find(".pnum-to").val("");
			     }
			  }
		if(isFloat(first) && isFloat(second) && isFloat(three) && isFloat(weight) && isFloat(dimens)){
		         $(this).parent("td").parent("tr").parent("table").parent("div")
		         .next("div").find(".error-mess").hide();
		} 
	  
  });    
	 
     var num = '.($p>1 ? $p:1).';
     $(".add_new input").click(function(){
		num++;
          $(".post-all .parcel strong").each(function(){
		ptitle = $(this).html();
                pnum = ptitle.substring(7);
                 if(pnum==num){
			num++;
                 }

	  });

		var divText = $(".post-all:last");
        var newDiv = divText.clone(true);
		divText.after(newDiv);
		$(".post-all:last .parcel strong").html("Parcel#" + num);
         $(".post-all:last .pcode").attr("id","pcode"+num);
          $(".post-all:last .addressto").attr("id","destination"+ num);
		$(".post-all:last .parcel input").show();
		$(".post-all:last .post-mess table input").val("");
		



     });
	 $(".duplicate input").click(function(){
		num++;

          $(".post-all .parcel strong").each(function(){
		ptitle = $(this).html();
                pnum = ptitle.substring(7);
                 if(pnum==num){
			num++;
                 }

	  });
		var divText = $(this).parent().parent().parent();
        var newDiv = divText.clone(true);
		$(".post-all:last").after(newDiv);
		$(".post-all:last .parcel strong").html("Parcel#" + num);
        $(".post-all:last .pcode").attr("id","pcode"+num);
         $(".post-all:last .addressto").attr("id","duplicate"+num);
		$(".post-all:last .parcel input").show();
   		
     });
     $(".deliver").click(function(){
         $(".package-from").text("Pickup:");
         $(".package-to").text("Destination:");
        });
    $(".pick-up").click(function(){
         $(".package-to").text("Pickup:");
         $(".package-from").text("Destination:");
        });
        
	 $(".parcel input").click(function() {
		$(this).parent().parent().remove();
		num--;
	 });
	 $(".post-all").mouseenter(function(){
	    if($(".order-btn .check_parcels").val()=="Update"){
	       $(this).find(".duplicate").show();
	    }
	 }).mouseleave(function(){
	    $(this).find(".duplicate").hide();
	 });
	 function getprice(f,tlen,postfrom,ajaxrequest){
			  var max = 0;
			  var parcelnum = $(".post-all:eq("+(f-1)+")").find(".parcel strong").text();
			  var dimfirst = $(".post-all:eq("+(f-1)+")").find(".dim-first").val();
			  var dimsecond = $(".post-all:eq("+(f-1)+")").find(".dim-second").val();
			  var dimthree = $(".post-all:eq("+(f-1)+")").find(".dim-three").val();
			  var dimenstext  = $(".post-all:eq("+(f-1)+")").find(".dimens-text").val();
			  var weighttext = $(".post-all:eq("+(f-1)+")").find(".weight-text").val();
	             	
			  var service_type = $(".post-all:eq("+(f-1)+")").find(".optional-fees").val();



              var ptype=2;
              if($(".deliver").attr("checked")){
                   var addressfrom =$("#autocomplete").val();
                   var addressto = $(".post-all:eq("+(f-1)+")").find("#destination").val();
		  //   locality  = $("#locality").val();
		   //  state = $("#administrative_area_level_1").val();
		   //  postcode = $("#postal_code").val();

		     var postfrom = "0_"+$("#administrative_area_level_1").val()+"_"+$("#postal_code").val();
		     var postto = "0_"+$("#administrative_area_level_11").val()+"_"+$("#postal_code1").val();
                     ptype=2;
                }else{
                    var addressto =$("#autocomplete").val() ;
                    var addressfrom =$(".post-all:eq("+(f-1)+")").find("#destination").val();
		     var postto = "0_"+$("#administrative_area_level_1").val()+"_"+$("#postal_code").val();
		     var postfrom = "0_"+$("#administrative_area_level_11").val()+"_"+$("#postal_code1").val();
                   ptype=1;
                }
			  if(dimfirst > max){
				  max = dimfirst; 
			  }
			  if(dimsecond > max){
			      max = dimsecond;
			  }
			  if(dimthree > max){
				  max = dimthree;  
			  }
              weighttext=parseFloat(weighttext);
              
              ajaxrequest+=(ajaxrequest !="" ? ",":"")+ \'{"parcelnum":"\'+parcelnum+\'","service_type":"\'+service_type+\'","dimfirst":"\'+dimfirst+\'","dimsecond":"\'+dimsecond+\'","dimthree":"\'+dimthree+\'","max":"\'+max+\'","dimenstext":"\'+dimenstext+\'","weighttext":"\'+weighttext.toFixed(1)+\'","postfrom":"\'+postfrom+\'","postto":"\'+postto+\'","addressfrom":"\'+addressfrom+\'","addressto":"\'+addressto+\'"}\'; 
              
             if(f<tlen){ 
                getprice(f+1,tlen,postfrom,ajaxrequest);
                
            }else{
                $.post("/admin/liveparcels/getzoneprice/ajax", 
                     {ajaxrequest:"["+ajaxrequest+"]",action:"updateprice"},function(zone){
                         

                       if(zone != ""){
                          $(".order ul").append(zone.parcels);
                          if( zone.error=="1"){
                              $(".header-warning").show();
                            }
                                var parcelsjson=eval("(" +"{\\"parcels\\":["+ ajaxrequest +"]}"+ ")");
                                  for (k in zone.pprice){
                                      parcelsjson.parcels[k].price=zone.pprice[k][\'pprice\'];
                                      parcelsjson.parcels[k].package_name=zone.pprice[k][\'package_name\'];
                                    }
                                    parcelsjson.ptype= ptype;
                                    parcelsjson.totals= zone.totals;
                                    parcelsjson.discount= zone.discount; 
                                     
                                    $(".parcelsPost").val(json2str(parcelsjson)); 
                            
                            '.(module_exists('lp_discount') ? ' 
                            if(zone.discount>0 ){ $(".order-discount").html("Discount: '.variable_get('uc_currency_sign','$').'" + zone.discount);}else{$(".order-discount").html(""); }':'').'
                            var totals=zone.totals-zone.discount; 

                            $(".order-total").html("Total: '.variable_get('uc_currency_sign','$').'" + '.(module_exists('lp_discount') ?  'totals.toFixed(2)':'zone.totals').');
					    }else{
                            $(".header-warning").show();
                             '.(module_exists('lp_discount') ? ' $(".order-discount").html("Discount:  Pending...");':'').'
							  $(".order-total").html("Total : Pending..."); 
					    }
                     },"json");
            }
            
        }
         function json2str(o) { 
            var arr = []; 
            var fmt = function(s) { 
            if (typeof s == "object" && s != null) return json2str(s); 
                return /^(string|number)$/.test(typeof s) ? "\\"" + s + "\\"" : s; 
            } 
            for (var i in o) arr.push("\\"" + i + "\\":" + fmt(o[i])); 
            return "{" + arr.join(",") + "}"; 
        } 
	 $(".check_parcels").click(function(){
		if($(this).attr("value")=="Update"){
		   
	       var postfrom =$(".pnum-from").val();
	       var postfroms =$(".post-suburb").val();
	      
	       if(postfroms == ""){
	         $(".pnum-from").val("");
	       }
		   if(postfrom ==""){
		      $(".post-suburb").css("border","1px dashed red");
		      return false;
		   }else{
		      $(".post-suburb").css("border","1px solid #ccc");
		   }
		   var f=1;   
		   var subtotal = 0;   
		   var tlen=$(".post-all:last").index()-2;
		   $(".order ul li").remove();
           $(".header-warning").hide();
           var er=0;
           for(var i=1;i<=tlen;i++){
                er=checknull(i);
                if(er){
                break;    
                }
            }
            if(!er){
                var ajaxrequest="";
                getprice(f,tlen,postfrom,ajaxrequest);	
           }       
	       $(".page-float input").attr("disabled",true);     
	       $(".post-mess table input").css("background","#d2d2d2");
	       $(".page-float select").attr("disabled",true);     


	       $(".add_new").hide();
	       $(this).attr("value","Modify");
	    }else{
           $(".parcelsPost").val("");
	       if(postfroms == ""){
	          $(".pnum-from").val("");
	       }
		   if(postfrom ==""){
		      $(".post-suburb").css("border","1px dashed red");
		      return false;
		   }else{
		      $(".post-suburb").css("border","1px solid #ccc");
		   }
		   $(".page-float input").attr("disabled",false);
		   $(".page-float select").attr("disabled",false);

		   $(".dimens-text").attr("disabled",true);
		   $(".post-mess table input").css("background","white");

		   $(".dimens-input input").css("background","#d2d2d2");
		   $(".order ul li").remove();
		   $(".order ul").append("<li>Pending...</li>");
		   $(".order-total").html("Total: Pending..."); 
		   $(".add_new").show();
	       $(this).attr("value","Update");
		}    
	 });
    $(".add_to_cart").click(function(){
        if($(".parcelsPost").val()==""){
                alert("Please update parcels information.");
                return false;
        }else{
            $("#liveparcelsform").submit();
        }
    });
	 $(".post-suburb").keyup(function(){
          var words=gettrim($(this).val());
          var id=$(this).attr("id");
          if( words.length >= 3){
              setTimeout(ajaxsearch(words,id),500);
          }else{
              $("#pcode"+id).hide();
            }
	  });
       $(".postcode-suburb").keyup(function(){
          var words=gettrim($(this).val());
          var id=$(this).attr("id");
          if( words.length >= 2){
              setTimeout(ajaxsearch(words,id),500);
            
          }else{
              $("#pcode"+id).hide();
            }
	  });
      function gettrim(str){ //trim left and right varchar
 
		  var i;
		  for(i=0;i<str.length;i++){
		    if(str.charAt(i)!=" "&&str.charAt(i)!=" ") {
			break;
		    } 
		  } 
		  str = str.substring(i,str.length);
		  i=0;
		  
		  for(i=str.length-1;i>=0;i--){
		  
		  if(str.charAt(i)!=" "&&str.charAt(i)!=" ") break;
		  
		  }
		  
		  str = str.substring(0,i+1);
		  
		  return str;
	
    }
    function ajaxsearch(words,id){     
        if(words == "" || words == " " ){
	     	 $("#pcode"+id).hide();
             return false;
        } 
        var str="";
	 	var res="";
		var post="";
		for (k in zonedata){
			str=zonedata[k].locality.toUpperCase();
            post=zonedata[k].pcode;
			if(str.indexOf(words.toUpperCase()) >= 0 || post.indexOf(words) >= 0){
			  res+="<li id=\'"+zonedata[k].pnum+"_"+zonedata[k].state+"_"+post+"\'>"+str+" "+post+"</li>";
		    }	
		}
        if(res != ""){
         $("#pcode"+id).html(res);
           $(".pcode li").click(function(){
                 $(this).parent("ul").hide();
                 $(this).parent("ul").prev().prev(".postcode-suburb").val( $(this).text());
                $(this).parent("ul").prev(".pnum-to").val($(this).attr("id"));
             });
            $(".fpcode li").click(function(){
                 $(this).parent("ul").hide();
                 $(".post-suburb").val( $(this).text());
                 $(".pnum-from").val($(this).attr("id"));
             });
         $("#pcode"+id).show();
        }
	 }
  })(jQuery) </script>'));
  
	$build['liveparcels'] = array(
	"#theme" => "table",
	  "#rows" => $rows,
	  "#attributes" => array("class" => array("live-parcels-status")),
	);

	 drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/package_show.css', 
	 array('group' => CSS_DEFAULT, 'every_page' => TRUE));

	 
     return $build;
}

function liveparcels_getPackageprice($max,$dimenstext,$weighttext) {

	$weight = $dimenstext>$weighttext?$dimenstext:$weighttext;
	$items=array('pprice'=>0,'package_name'=>'');
	if($max>0 && $dimenstext>0 && $weighttext>0){ 
		$arr = db_query("SELECT `weight`,`plength` FROM 
		`{liveparcels_package}` ORDER BY `pprice` DESC LIMIT 1")->fetchAssoc();
		if($arr['weight'] < $weight || $arr['plength'] < $max){
		     $items=array('pprice'=>0,'package_name'=>'');
        }else{
                $pprice = db_query("SELECT `pprice`,`package_name` FROM `{liveparcels_package}` 
                   WHERE `plength`>=". $max ." ORDER BY `pprice` ASC  LIMIT 1")
                   ->fetchAssoc();
        $lprice = db_query("SELECT `pprice`,`package_name` FROM `{liveparcels_package}` 
                   WHERE `weight`>=". $weight ." 
                   ORDER BY `pprice` ASC  LIMIT 1")
                   ->fetchAssoc();
                    $nowprice=$lprice['pprice'] >$pprice['pprice'] ? $lprice:$pprice;
                    if($nowprice['pprice']>0){
                      $items= $nowprice;
                    }else{
                    $items = db_query("SELECT `pprice`,`package_name` FROM `{liveparcels_package}` 
                    ORDER BY `pprice` ASC LIMIT 1 ")->fetchAssoc();
                    }
              }
      }
  
		return  array("pprice"=>$items['pprice'],"package_name"=>$items['package_name']);
}  

function liveparcels_getZoneprice() {

if(isset($_SESSION['lp_node'])){ 
  unset($_SESSION['lp_node']);
}

if(isset($_SESSION['lp_order'])){
  unset($_SESSION['lp_order']);
}

    $ajaxrequest = $_REQUEST['ajaxrequest'];
    $pricedata =json_decode($ajaxrequest,true);
	$action = $_REQUEST['action'];
    $parcels='';
    $totals=0;
    $error=0;
    $parcels_price=array();
    $service_price = array();

   // location_distance_between($latlon_a = array(), $latlon_b = array(), $distance_unit = 'km');





	if($action =="updateprice" && count($pricedata)>0){
        foreach($pricedata as $key=>$pdata){
            $pprice=liveparcels_getPackageprice($pdata['max'],$pdata['dimenstext'],$pdata['weighttext']);

         // $data = get_google_distance($pdata['addressfrom'],$pdata['addressto']);

	//    $distance = $data->rows['0']['elements']['0']['distance']['value'];

	$distance = 218000;

            if($pprice['pprice']>0){
		$result = db_query('select * from {liveparcels_distance} order by distance asc');
		$pzon = 0;
		 foreach($result as $rst){

			$set_distance = $rst->distance;

			if($distance>$set_distance*1000){
				$pzon = $rst->multiplier;
			}


		 }

                if($pzon>0){
                    $pzone=$pzon*$pprice['pprice']; 
                }else{
                    $pzone=0;
                }
               
            }else{
                  $pzone=0;  
            }
            $parcels_price[]=array("pprice"=>variable_get('uc_currency_sign','$').sprintf('%.2f',round($pzone,2)),"package_name"=>$pprice['package_name']);
	    // service price
	    $totals+=$pzone;
	    if(module_exists('lp_feature_service')&&get_service_type_count()>1){
	    $type_value =  get_service_value($pdata['service_type']);
    	    $service_price[] = array("pprice"=>variable_get('uc_currency_sign','$').sprintf('%.2f',round($pzone*$type_value,2)),"package_name"=>$pprice['package_name']);
    	    $totals += $pzone*$type_value;
	    }

            if($pzone=='0'){
            $error=1;    
            }

	    if(module_exists('lp_feature_service')&&get_service_type_count()>1){
            $parcels.=$pzone=='0' ? "<li>". $pdata['parcelnum'].": <span style='color:red'>??</span></li>":"<li>". $pdata['parcelnum'].": <span>".variable_get('uc_currency_sign','$').sprintf('%.2f',$pzone)."</span> <div>Service fee: ".variable_get('uc_currency_sign','$').sprintf('%.2f',round($pzone*$type_value,2))."</div></li>";
            }else{
 $parcels.=$pzone=='0' ? "<li>". $pdata['parcelnum'].": <span style='color:red'>??</span></li>":"<li>". $pdata['parcelnum'].": <span>".variable_get('uc_currency_sign','$').$pzone."</span></li>";
	    }
        }
	}
    if(module_exists('lp_discount')){
        $discount=lp_discount_get_pricing($totals);
    }else{
        $discount=0;
    }

    $returndata=array('error'=>$error,'discount'=>sprintf('%.2f',$discount),'totals'=>sprintf('%.2f',$totals),'service_price'=>$service_price,'parcels'=>$parcels,'pprice'=>$parcels_price);
    
		echo json_encode($returndata);		
}

function  get_google_distance($from,$to){

  $url = 'https://maps.googleapis.com/maps/api/distancematrix/json?origins='.$from.'&destinations='.$to.'&mode=bicycling&language=en';

  $output = file_get_contents($url);

  return json_decode($output);

}




