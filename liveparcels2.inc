<?php
/**
 * @file
 * Store front page menu items.
 */
 
/**
 * Menu callback which provides the store administration overview page.
 */

include_once(DRUPAL_ROOT . '/' . drupal_get_path('module', 'location') . '/geocoding/google.inc');

function liveparcels_packageshow() {

$parcels=liveparcels_getparcelsdata();

$countryinfo = lp_address_get_country_info();

$options = '';
$parcel_info='';
 $postfrom='';
 $post='postto';
$p=0;
 $jsondata=liveparcels_getZonelistData();

if(module_exists('lp_feature_service') && get_service_type_count()>1){
 $service_type = get_service_type();
//update 2015-08-13

 foreach($service_type as $service){

   $options .= '<option  value="'.$service['id'].'">'.$service['type'].' (+'.($service['value']*100).'%)</option>'; 

 }

}


if($parcels>0){

        if(strpos($parcels['parcels'][0]['parcelnum'],'Parcel')>0){
          $parcels['parcels'][0]['parcelnum'] = 'Parcel#1';
        }


     $postfrom=$parcels['ptype']==2 ? $parcels['parcels'][0]['postfrom']:$parcels['parcels'][0]['postto'];
     $post=$parcels['ptype']==2 ? 'postto':'postfrom';

 foreach($parcels['parcels'] as $pid=>$parcel){

$p++;

 $_postfrom = explode('_',$parcel['postfrom']);
 $_postto = explode('_',$parcel['postto']);

  
   $options =  str_replace('value="'.$parcel['service_type'].'"', 'value="'.$parcel['service_type'].'" selected ' ,$options);

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
		<input id="destination" class="addressto"  value="'.(empty($parcel['addressto'])?'':$parcel['addressto']).'"  placeholder="Enter your address" onFocus="geolocate()" type="text"></input>
<input type="hidden"  id="street_number1" class="street" value="'.(empty($_postto[0])?'':$_postto[0]).'">
<input type="hidden"  id="route1" class="route" value="'.(empty($_postto[1])?'':$_postto[1]).'">
<input type="hidden"  id="locality1" class="locality">
<input type="hidden"  id="administrative_area_level_11" class="administrative_area_level" value="'.(empty($_postto[2])?'':$_postto[2]).'">
<input type="hidden"  id="postal_code1" class="postal_code" value="'.(empty($_postto[3])?'':$_postto[3]).'">
<input type="hidden"  id="country1" class="country">

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
            <input id="autocomplete" placeholder="Enter your address" value="'.(empty($parcel['addressfrom'])?'':$parcel['addressfrom']).'"
             onFocus="geolocate()" type="text"></input>
<input type="hidden"  id="street_number" value="'.(empty($_postfrom[0])?'':$_postfrom[0]).'">
<input type="hidden"  id="route" value="'.(empty($_postfrom[1])?'':$_postfrom[1]).'">
<input type="hidden"  id="locality">
<input type="hidden"  id="administrative_area_level_1" value="'.(empty($_postfrom[2])?'':$_postfrom[2]).'">
<input type="hidden"  id="postal_code" value="'.(empty($_postfrom[3])?'':$_postfrom[3]).'">
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
		<input id ="destination" class="addressto"  value="'.(empty($parcel['addressto'])?'':$parcel['addressto']).'" placeholder="Enter your address" onFocus="geolocate()" type="text"></input>
<input type="hidden"  id="street_number1" class="street" value="'.(empty($_postto[0])?'':$_postto[0]).'">
<input type="hidden"  id="route1" class="route" value="'.(empty($_postto[1])?'':$_postto[1]).'">
<input type="hidden"  id="locality1" class="locality">
<input type="hidden"  id="administrative_area_level_11" class="administrative_area_level" value="'.(empty($_postto[2])?'':$_postto[2]).'">
<input type="hidden"  id="postal_code1" class="postal_code" value="'.(empty($_postto[3])?'':$_postto[3]).'">
<input type="hidden"  id="country1" class="country">



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
 <script src="https://maps.googleapis.com/maps/api/js?key='.variable_get('google_autocomplete_address_key','').'&signed_in=true&libraries=places&callback=initAutocomplete"
        async defer></script>

 <script type="text/javascript">

// This example displays an address form, using the autocomplete feature
// of the Google Places API to help users fill in the information.

var placeSearch,autocomplete,destination1,destination2,destination3,destination4,destination5,destination6,destination7,destination8,destination9;



var componentForm = {
  street_number: "short_name",
  route: "long_name",
  locality: "long_name",
  administrative_area_level_1: "short_name",
  country: "long_name",
  postal_code: "short_name"
};


var destination_componentForm = {
componentForm1:{
  street_number1: "short_name",
  route1: "long_name",
  locality1: "long_name",
  administrative_area_level_11: "short_name",
  country1: "long_name",
  postal_code1: "short_name"
},
componentForm2 :{
  street_number2: "short_name",
  route2: "long_name",
  locality2: "long_name",
  administrative_area_level_12: "short_name",
  country2: "long_name",
  postal_code2: "short_name"
},
componentForm3 :{
  street_number3: "short_name",
  route3: "long_name",
  locality3: "long_name",
  administrative_area_level_13: "short_name",
  country3: "long_name",
  postal_code3: "short_name"
},
componentForm4 :{
  street_number4: "short_name",
  route4: "long_name",
  locality4: "long_name",
  administrative_area_level_14: "short_name",
  country4: "long_name",
  postal_code4: "short_name"
},
componentForm5 :{
  street_number5: "short_name",
  route5: "long_name",
  locality5: "long_name",
  administrative_area_level_15: "short_name",
  country5: "long_name",
  postal_code5: "short_name"
},
componentForm6 :{
  street_number6: "short_name",
  route6: "long_name",
  locality6: "long_name",
  administrative_area_level_16: "short_name",
  country6: "long_name",
  postal_code6: "short_name"
},
componentForm7 :{
  street_number7: "short_name",
  route7: "long_name",
  locality7: "long_name",
  administrative_area_level_17: "short_name",
  country7: "long_name",
  postal_code7: "short_name"
},
componentForm8 :{
  street_number8: "short_name",
  route8: "long_name",
  locality8: "long_name",
  administrative_area_level_18: "short_name",
  country8: "long_name",
  postal_code8: "short_name"
},
componentForm9 :{
  street_number9: "short_name",
  route9: "long_name",
  locality9: "long_name",
  administrative_area_level_19: "short_name",
  country9: "long_name",
  postal_code9: "short_name"
}

};




function initAutocomplete() {
  // Create the autocomplete object, restricting the search to geographical
  // location types.
  autocomplete = new google.maps.places.Autocomplete(
     (document.getElementById("autocomplete")),
      {types: ["geocode"]});

  // When the user selects an address from the dropdown, populate the address
  // fields in the form.
  autocomplete.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  autocomplete.addListener("place_changed", fillInAddress);

  destination1  = new google.maps.places.Autocomplete(
     (document.getElementById("destination")),
      {types: ["geocode"]});
  destination1.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination1.addListener("place_changed", fillInAddress1);

  destination2  = new google.maps.places.Autocomplete(
     (document.getElementById("destination2")),
      {types: ["geocode"]});
  destination2.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination2.addListener("place_changed", fillInAddress2);

  destination3  = new google.maps.places.Autocomplete(
     (document.getElementById("destination3")),
      {types: ["geocode"]});
  destination3.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination3.addListener("place_changed", fillInAddress3);

  destination4  = new google.maps.places.Autocomplete(
     (document.getElementById("destination4")),
      {types: ["geocode"]});
  destination4.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination4.addListener("place_changed", fillInAddress4);

  destination5  = new google.maps.places.Autocomplete(
     (document.getElementById("destination5")),
      {types: ["geocode"]});
  destination5.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination5.addListener("place_changed", fillInAddress5);

  destination6  = new google.maps.places.Autocomplete(
     (document.getElementById("destination6")),
      {types: ["geocode"]});
  destination6.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination6.addListener("place_changed", fillInAddress6);

  destination7  = new google.maps.places.Autocomplete(
     (document.getElementById("destination7")),
      {types: ["geocode"]});
  destination7.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination7.addListener("place_changed", fillInAddress7);

  destination8  = new google.maps.places.Autocomplete(
     (document.getElementById("destination8")),
      {types: ["geocode"]});
  destination8.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination8.addListener("place_changed", fillInAddress8);

  destination9  = new google.maps.places.Autocomplete(
     (document.getElementById("destination9")),
      {types: ["geocode"]});
  destination9.setComponentRestrictions({"country": "'.$countryinfo['country_iso_code_2'].'"});
  destination9.addListener("place_changed", fillInAddress9);
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

  var place = destination1.getPlace();

  for (var component in destination_componentForm["componentForm1"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm1"][addressType+"1"]) {
      var val = place.address_components[i][destination_componentForm["componentForm1"][addressType+"1"]];
      document.getElementById(addressType+"1").value = val;
    }
 }
}
function fillInAddress2() {

  var place = destination2.getPlace();

  for (var component in destination_componentForm["componentForm2"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm2"][addressType+"2"]) {
      var val = place.address_components[i][destination_componentForm["componentForm2"][addressType+"2"]];
      document.getElementById(addressType+"2").value = val;
    }
 }
}

function fillInAddress3() {

  var place = destination3.getPlace();

  for (var component in destination_componentForm["componentForm3"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm3"][addressType+"3"]) {
      var val = place.address_components[i][destination_componentForm["componentForm3"][addressType+"3"]];
      document.getElementById(addressType+"3").value = val;
    }
 }
}
function fillInAddress4() {

  var place = destination4.getPlace();

  for (var component in destination_componentForm["componentForm4"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm4"][addressType+"4"]) {
      var val = place.address_components[i][destination_componentForm["componentForm4"][addressType+"4"]];
      document.getElementById(addressType+"4").value = val;
    }
 }
}

function fillInAddress5() {

  var place = destination5.getPlace();

  for (var component in destination_componentForm["componentForm5"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm5"][addressType+"5"]) {
      var val = place.address_components[i][destination_componentForm["componentForm5"][addressType+"5"]];
      document.getElementById(addressType+"5").value = val;
    }
 }
}

function fillInAddress6() {

  var place = destination6.getPlace();

  for (var component in destination_componentForm["componentForm6"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm6"][addressType+"6"]) {
      var val = place.address_components[i][destination_componentForm["componentForm6"][addressType+"6"]];
      document.getElementById(addressType+"6").value = val;
    }
 }
}

function fillInAddress7() {

  var place = destination4.getPlace();

  for (var component in destination_componentForm["componentForm7"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm7"][addressType+"7"]) {
      var val = place.address_components[i][destination_componentForm["componentForm7"][addressType+"7"]];
      document.getElementById(addressType+"7").value = val;
    }
 }
}
function fillInAddress8() {

  var place = destination8.getPlace();

  for (var component in destination_componentForm["componentForm8"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm8"][addressType+"8"]) {
      var val = place.address_components[i][destination_componentForm["componentForm8"][addressType+"8"]];
      document.getElementById(addressType+"8").value = val;
    }
 }
}

function fillInAddress9() {

  var place = destination9.getPlace();

  for (var component in destination_componentForm["componentForm9"]){
    document.getElementById(component).value = "";
    document.getElementById(component).disabled = false;
  }

  for (var i = 0; i < place.address_components.length; i++) {
    var addressType = place.address_components[i].types[0];
    if (destination_componentForm["componentForm9"][addressType+"9"]) {
      var val = place.address_components[i][destination_componentForm["componentForm9"][addressType+"9"]];
      document.getElementById(addressType+"9").value = val;
    }
 }
}

function count(o){
    var t = typeof o;
    if(t == "string"){
            return o.length;
    }else if(t == "object"){
            var n = 0;
            for(var i in o){
                    n++;
            }
            return n;
    }
    return false;
}; 

// [END region_fillform]

// [START region_geolocation]

function geolocate() {

initAutocomplete();

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
    });
  }

}
// [END region_geolocation]


  (function($){
  var zonedata='.( $jsondata<>'' ? $jsondata:'').';

document.onreadystatechange = subSomething;

function subSomething() { 
if(document.readyState == "complete") {
  $("#autocomplete").removeAttr("disabled");
  $(".deliver").removeAttr("disabled");
  $(".pick-up").removeAttr("disabled");

}else{
  $("#autocomplete").attr("disabled","disabled");
  $(".deliver").attr("disabled","disabled");
  $(".pick-up").attr("disabled","disabled");
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
		 var postto = $("#autocomplete").val();
		 var posttos = $(".post-all:eq("+(f-1)+")").find(".addressto").val();

		 if(postto == ""){

	           $("#autocomplete").css("border","1px dashed red");
	           $(".post-all:eq("+(f-1)+")").find(".error-mess").show();
		 }else{
		       $("#autocomplete").css("border","1px solid #ccc");
		 }

		if(posttos==""){

	           $(".post-all:eq("+(f-1)+")").find(".addressto").css("border","1px dashed red");
	           $(".post-all:eq("+(f-1)+")").find(".error-mess").show();		

 		}else{
	           $(".post-all:eq("+(f-1)+")").find(".addressto").css("border","1px solid #ccc");
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

          $(".post-all:last .street").attr("id","street_number"+ num);
          $(".post-all:last .route").attr("id","route"+ num);
          $(".post-all:last .locality").attr("id","locality"+ num);
          $(".post-all:last .administrative_area_level").attr("id","administrative_area_level_1"+ num);
          $(".post-all:last .postal_code").attr("id","postal_code"+ num);
          $(".post-all:last .country").attr("id","country"+ num);

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
         $(".post-all:last .addressto").attr("id","destination"+num);

          $(".post-all:last .street").attr("id","street_number"+ num);
          $(".post-all:last .route").attr("id","route"+ num);
          $(".post-all:last .locality").attr("id","locality"+ num);
          $(".post-all:last .administrative_area_level").attr("id","administrative_area_level_1"+ num);
          $(".post-all:last .postal_code").attr("id","postal_code"+ num);
          $(".post-all:last .country").attr("id","country"+ num);

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
		   var from_locality  = $("#locality").val();
                   var addressto = $(".post-all:eq("+(f-1)+")").find(".addressto").val();

		   var to_locality  = $(".post-all:eq("+(f-1)+")").find(".locality").val();

		   var postfrom = $("#street_number").val()+"_"+$("#route").val()+"_"+$("#administrative_area_level_1").val()+"_"+$("#postal_code").val();
		   var postto = $(".post-all:eq("+(f-1)+")").find(".street").val()+"_"+$(".post-all:eq("+(f-1)+")").find(".route").val()+"_"+$(".post-all:eq("+(f-1)+")").find(".administrative_area_level").val()+"_"+$(".post-all:eq("+(f-1)+")").find(".postal_code").val();
                     ptype=2;
                }else{
                   var addressto = $("#autocomplete").val();
                   var addressfrom =$(".post-all:eq("+(f-1)+")").find(".addressto").val();
		   var from_locality  = $(".post-all:eq("+(f-1)+")").find(".locality").val();
	           var to_locality = $("#locality").val();
		   var postto = $("#street_number").val()+"_"+$("#route").val()+"_"+$("#administrative_area_level_1").val()+"_"+$("#postal_code").val();
		   var postfrom = $(".post-all:eq("+(f-1)+")").find(".street").val()+"_"+$(".post-all:eq("+(f-1)+")").find(".route").val()+"_"+$(".post-all:eq("+(f-1)+")").find(".administrative_area_level").val()+"_"+$(".post-all:eq("+(f-1)+")").find(".postal_code").val();
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
              
              ajaxrequest+=(ajaxrequest !="" ? ",":"")+ \'{"parcelnum":"\'+parcelnum+\'","service_type":"\'+service_type+\'","dimfirst":"\'+dimfirst+\'","dimsecond":"\'+dimsecond+\'","dimthree":"\'+dimthree+\'","max":"\'+max+\'","dimenstext":"\'+dimenstext+\'","weighttext":"\'+weighttext.toFixed(1)+\'","from_locality":"\'+from_locality+\'","to_locality":"\'+to_locality+\'","postfrom":"\'+postfrom+\'","postto":"\'+postto+\'","addressfrom":"\'+addressfrom+\'","addressto":"\'+addressto+\'"}\'; 

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
           $distance_type =  variable_get('distance_type');

	   if($distance_type == '0'){

		$location_from = explode(',',$pdata['addressfrom']);
		$locationfrom = array();
		$locationfrom['street'] = $location_from[0];
		$locationfrom['city'] = $location_from[1];
		$locationfrom['province'] = $location_from[2];
		$locationfrom['country'] = $location_from[3];
		$latlon_a = google_geocode_location($locationfrom);

		$location_to = explode(',',$pdata['addressto']);
		$locationto = array();
		$locationto['street'] = $location_to[0];
		$locationto['city'] = $location_to[1];
		$locationto['province'] = $location_to[2];
		$locationto['country'] = $location_to[3];
		$latlon_b = google_geocode_location($locationto);

		$getunit = variable_get('distance_unit',0);
		if($getunit=='1'){
		  $unit = 'mile';
		}else{
		  $unit = 'km';
		}
		$between = location_distance_between($latlon_a,$latlon_b,$unit);
		$distance = $between['scalar']*1000;
	  	$distancetest = $between['scalar'].$between['distance_unit'];
            }else{
          	$data = get_google_distance($pdata['addressfrom'],$pdata['addressto']);
	        $distance = intval($data->rows[0]->elements[0]->distance->value);	
	  	$distancetest = $data->rows[0]->elements[0]->distance->text;
            }
 //$distance = 218000;
            if($pprice['pprice']>0){
		$result = db_query('select * from {liveparcels_distance} order by distance asc');
		$pzon = 0;
		 foreach($result as $rst){

			$set_distance = $rst->distance;

			if($distance!='0'&&$set_distance*1000>$distance){
				$pzon = $rst->multiplier;
  				break;
			}else{
				$pzon = 0;
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
            $parcels.=$pzone=='0' ? "<li>". $pdata['parcelnum'].": <span style='color:red'>??</span>".$distancetest."</li>":"<li>". $pdata['parcelnum'].": <span>".variable_get('uc_currency_sign','$').sprintf('%.2f',$pzone)."</span> <div>Service fee: ".variable_get('uc_currency_sign','$').sprintf('%.2f',round($pzone*$type_value,2))."</div>".$distancetest."</li>";
            }else{
 $parcels.=$pzone=='0' ? "<li>". $pdata['parcelnum'].": <span style='color:red'>??</span></li>":"<li>". $pdata['parcelnum'].": <span>".variable_get('uc_currency_sign','$').$pzone."</span>".$distancetest."</li>";
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

$unit = variable_get('distance_unit',0);
$restriction = variable_get('distance_restriction',0);

if($restriction=='1'){
  $distance_restriction = 'tolls';
}elseif($restriction=='2'){
  $distance_restriction = 'highways';
}elseif($restriction=='3'){
  $distance_restriction = 'ferries';
}elseif($restriction=='4'){
  $distance_restriction = 'indoor';
}else{
  $distance_restriction = '';
}

if($unit=='0'){
 $distance_unit = 'metric';
}else{
 $distance_unit = 'imperial';
}

$url = 'https://maps.googleapis.com/maps/api/distancematrix/json?origins='.urlencode($from).'&destinations='.urlencode($to).'&mode=driving&language=en&avoid='.$distance_restriction.'&units='.$distance_unit.'&key='.variable_get('google_autocomplete_address_key','');

$output = file_get_contents($url);

  return json_decode($output);

}




