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
      <div class="page-content-address" ><strong>Pickup post/suburb:</strong><input id="0" class="post-suburb" type="text" ><input class="pnum-from" type="hidden" ><ul class="fpcode" id="pcode0"></ul></div>
      <div class="post-all" id=vp1>
          <div class="parcel"><strong>Parcel #1</strong><input type="button" value="X"></div>
        <div class="post-mess"> 
		 <table>
          <tr><td class="dimensions">Dimensions(cm):</td><td><input class="dim-first" type="text">X<input class="dim-second" type="text">X<input class="dim-three" type="text"></td></tr>
          <tr><td class="dimensional">Dimensional weight(kg):</td><td class="dimens-input"><input class="dimens-text" type="text" readonly>(this value is calculated automatically)</td></tr>
          <tr><td class="weight">weight(kg):</td><td class="wei-text"><input class="weight-text" type="text" ></td></tr>
          <tr><td class="destination">Destination postcode/suburb:</td><td class="des-text"><input class="postcode-suburb"  id="1" type="text" ><input class="pnum-to" type="hidden" ><ul class="pcode" id="pcode1"></ul></td></tr>
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
          <li class="order-first">Parcel #1: No value</li>
          <li>Parcel #2: No value</li>
          <li>Parcel #3: No value</li>
          </ul>
          <div class="order-total">Total:No value</div>
          
      </div>
      <div class="order-btn">
		  <input class="order-btn-first" type="button" name="modify" value="Save">
	      <input type="button" name="checkout" value="Checkout">
      </div>
	  <div class="footer-note">
		Note:to calculate your parcel price, we use either the Dimensional
        Weight or the Actual Weight, whichever is the greater of the two values.	
	 </div>
  </div>
 <script type="text/javascript">
  (function($){
  var zonedata='.(liveparcels_getZonelistData()<>'' ? liveparcels_getZonelistData():'').';
     $(".post-all input").blur(function(){
		 var first = $(this).parent("td").find(".dim-first").val();
		 var second = $(this).parent("td").find(".dim-second").val();
		 var three = $(this).parent("td").find(".dim-three").val();
		 var weight = $(this).parent("td").find(".weight-text").val();
		 var dimens  = $(this).parent("td").find(".dimens-text").val();
		 var cla = $(this).attr("class");
	  if(cla == "dim-first" || cla == "dim-second" || cla == "dim-three"){ 
		 if(first !== "" && second!== "" && three !== ""){
			if(parseFloat(first)>0 && parseFloat(second)>0 && parseFloat(three)>0){
		         var volume = parseFloat(first) * parseFloat(second) * parseFloat(three)*'.variable_get('liveparcels_factor',1).';
		         var Pvolume = volume.toFixed(4);
	             $(this).parent("td").parent("tr").next("tr")
	             .children("td").find(".dimens-text").val(Pvolume); 
	             $(this).parent("td").find(".dim-first").val(parseFloat(first));
		         $(this).parent("td").find(".dim-second").val(parseFloat(second));
		         $(this).parent("td").find(".dim-three").val(parseFloat(three));    
			}else{
			      alert("Please fill in the correct information");
			      $(this).parent("td").find(".dim-first").val("");
		          $(this).parent("td").find(".dim-second").val("");
		          $(this).parent("td").find(".dim-three").val("");   
			      return false;
			}
	     }
	   }
	   if(cla ="weight-text"){
		   if(weight !== "" ){
			 if(parseFloat(weight)>0){
				 $(this).parent("td").find(".weight-text").val(parseFloat(weight));
			   }else{
				 $(this).parent("td").find(".weight-text").val(""); 
			   }
			} 
	    }
	 
	  });
	  
     var num = 1;
     $(".add_new input").click(function(){
		num++;
		var divText = $(".post-all:last");
        var newDiv = divText.clone(true);
		divText.after(newDiv);
		$(".post-all:last .parcel strong").html("Parcel #" + num);
         $(".post-all:last .pcode").attr("id","pcode"+num);
          $(".post-all:last .postcode-suburb").attr("id",num);
		$(".post-all:last .parcel input").show();
		$(".post-all:last .post-mess table input").val("");
		
     });
	 $(".duplicate input").click(function(){
		num++;
		var divText = $(this).parent().parent().parent();
        var newDiv = divText.clone(true);
		$(".post-all:last").after(newDiv);
		$(".post-all:last .parcel strong").html("Parcel #" + num);
        $(".post-all:last .pcode").attr("id","pcode"+num);
         $(".post-all:last .postcode-suburb").attr("id",+num);
		$(".post-all:last .parcel input").show();
   		
     });
	 $(".parcel input").click(function() {
		$(this).parent().parent().remove();
		num--;
	 });
	 function getprice(f,tlen,postfrom,subtotal){
			  var max = 0;
			  var parcelnum = $(".post-all:eq("+(f-1)+")").find(".parcel strong").text();
			  var dimfirst = $(".post-all:eq("+(f-1)+")").find(".dim-first").val();
			  var dimsecond = $(".post-all:eq("+(f-1)+")").find(".dim-second").val();
			  var dimthree = $(".post-all:eq("+(f-1)+")").find(".dim-three").val();
			  var dimenstext  = $(".post-all:eq("+(f-1)+")").find(".dimens-text").val();
			  var weighttext = $(".post-all:eq("+(f-1)+")").find(".weight-text").val();
			  var postto = $(".post-all:eq("+(f-1)+")").find(".pnum-to").val();
			  var postfrom =$(".pnum-from").val();
			  if(dimfirst > max){
				  max = dimfirst; 
			  }
			  if(dimsecond > max){
			      max = dimsecond;
			  }
			  if(dimthree > max){
				  max = dimthree;  
			  }
			  $.get("/liveparcels/getpackageprice",{max:max,dimenstext:dimenstext,weighttext:weighttext},function(data){
			       if(data>0){
                     $.get("/liveparcels/getzoneprice",{postfrom:postfrom,postto:postto,price:data},function(zone){
                          
                          $(".order ul").append("<li>" + parcelnum +":&nbsp" + zone +"</li>");
                           
                          subtotal = subtotal + parseFloat(zone);
                       
                         if(f<tlen){
							getprice(f+1,tlen,postfrom,subtotal);
                         }else{
                         
							$(".order-total").html("Total: " + subtotal);
                         }
                     });
			       }
	        }) ;
	       }
	 $(".order-btn-first").click(function(){
		if($(this).attr("value")=="Save"){
		      var postfrom =$(".post-suburb").val();
		      var f=1;   
		      var subtotal = 0;   
		   var tlen=$(".post-all:last").index()-2;
		   $(".order ul li").remove();
		   getprice(f,tlen,postfrom,subtotal);
	       
	       $(".post-all input").attr("disabled",true);
	       $(this).attr("value","Modify"); 
	    }else{
		   $(".post-all input").attr("disabled",false);
		   $(".dimens-text").attr("disabled",true);
	       $(this).attr("value","Save");
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
			  res+="<li id="+zonedata[k].pnum+">"+str+" "+post+"</li>";
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

	 drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/package_show.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
	 
  return $build;
}

function liveparcels_getPackageprice() {
	$max = $_REQUEST['max'];
	$dimenstext = $_REQUEST['dimenstext'];
	$weighttext = $_REQUEST['weighttext'];	
	if($max>0 && $dimenstext>0 && $weighttext>0){
		$items='';
		$items = db_query("SELECT `pprice` FROM `{liveparcels_package}` WHERE `plength`<". $max ." AND `dead_weight`<". $dimenstext ." AND  `dimen_weight`<" . $weighttext . " ORDER BY `pprice` DESC  LIMIT 1")->fetchField();		
		if($items==""){
		  	$items = db_query("SELECT `pprice` FROM `{liveparcels_package}` ORDER BY `pprice` ASC LIMIT 1 ")->fetchField();
	   }
	}
		echo $items;
}  

function liveparcels_getZoneprice() {
    $postfrom = $_REQUEST['postfrom'];
	$postto = $_REQUEST['postto'];
	$price = $_REQUEST['price'];
	if($postfrom!=="" && $postto!==""){
		$pzone='';
		$pzon='';
		$pzon = db_query("SELECT `multiplier` FROM `{liveparcels_zone_price}` WHERE `zone_from_number`='". $postfrom ."' AND   `zone_to_number`='". $postto."'")->fetchField();	
		if($pzon<>''){
			$pzone=$pzon*$price;
		}else{
			$pzone=0;
		}
	}
		echo $pzone;		
}
function liveparcels_getZonelistData() {
	$postlist =array();
	$result= db_query("SELECT `pcode`,`locality`,`zone_number` FROM `{liveparcels_zone_post}");
	foreach($result as $row){
			$postlist[] = array(
			  'pcode' => $row->pcode,
			  'locality' => $row->locality,	
              'pnum'=>$row->zone_number		  
			);
	}
	return json_encode($postlist);
}
