<?php

/**
 * @file
 * Store front page menu items.
 */
 
/**
 * Menu callback which provides the store administration overview page.
 */
function liveparcels_packageshow() {

$items = menu_get_item('liveparcels/parcel_quote');
$item = array(
  'link_path'=>$items['path'],
  'link_title'=>$items['title'],
  'description'=>$items['description']
 );
$count = db_query("SELECT count(*) FROM {menu_links} where menu_name = 'navigation' and link_path ='liveparcels/parcel_quote' ")->fetchField();
if($count == 0){
menu_link_save($item);
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
		 <input class="deliver" type="radio" name="items" checked value="1" >
		 Deliver one or more items
         <input class="pick-up" type="radio" name="items" value="2" >
         Pick-up one or more items
      </div>
      <div class="page-content-address" >
           <strong class="package-from">Destination post/suburb:</strong>
           <input id="0" class="post-suburb" type="text" >
           <input class="pnum-from" type="hidden" >
           <ul class="fpcode" id="pcode0"></ul>
      </div>
      <div class="post-all">
          <div class="parcel"><strong>Parcel #1</strong>
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
                  <span class="package-to">Pickup postcode/suburb:</span>
               </td>
               <td class="des-text">
                 <input class="postcode-suburb"  id="1" type="text" >
                 <input class="pnum-to" type="hidden" >
                  <ul class="pcode" id="pcode1">
                  </ul>
                </td>
              </tr>
            </table>
          </div>
        <div class="post-btn">
             <div class="duplicate">
                <input class="form-submit" type="button" name="duplicate" value="Duplicate">
             </div>
        </div>
      </div>
          <div class="add_new">
               <input class="form-submit" type="button" name="add_new" value="Add new">
          </div>   
      </div>
      </div>
      <div class="order sidebar">
	 <div class="block">	
          <h2>Order summary</h2>
          <ul>
          <li class="order-first">Pending...</li>
          </ul>
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
 <script type="text/javascript">
  (function($){
  var zonedata='.(liveparcels_getZonelistData()<>'' ? liveparcels_getZonelistData():'').';
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
     $(".deliver").click(function(){
         $(".package-from").text("Pickup postcode/suburb:");
         $(".package-to").text("Destination postcode/suburb:");
        });
    $(".pick-up").click(function(){
         $(".package-to").text("Pickup postcode/suburb:");
         $(".package-from").text("Destination postcode/suburb:");
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
              var ptype=1;
              if($(".deliver").attr("checked")){
                     var postto = $(".post-all:eq("+(f-1)+")").find(".pnum-to").val();
                    var postfrom =$(".pnum-from").val();
                    ptype=1;
                }else{
                    var postfrom = $(".post-all:eq("+(f-1)+")").find(".pnum-to").val();
                    var postto =$(".pnum-from").val();
                     ptype=2;
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
              ajaxrequest+=(ajaxrequest !="" ? ",":"")+ \'{"parcelnum":"\'+parcelnum+\'","dimfirst":"\'+dimfirst+\'","dimsecond":"\'+dimsecond+\'","dimthree":"\'+dimthree+\'","max":"\'+max+\'","dimenstext":"\'+dimenstext+\'","weighttext":"\'+weighttext+\'","postfrom":"\'+postfrom+\'","postto":"\'+postto+\'"}\' ; 
              
             if(f<tlen){ 
                getprice(f+1,tlen,postfrom,ajaxrequest);
                
            }else{
                $.get("/admin/liveparcels/getzoneprice/ajax", 
                     {ajaxrequest:"["+ajaxrequest+"]",action:"updateprice"},function(zone){
                         
                       if(zone != ""){ 
                          $(".order ul").append(zone.parcels);
                          if( zone.error=="1"){
                              $(".header-warning").show();
                                $(".parcelsPost").val("");
                            }else{
                              
                                var parcelsjson=eval("(" +"{\\"parcels\\":["+ ajaxrequest +"]}"+ ")");
                                  for (k in zone.pprice){
                                      parcelsjson.parcels[k].price=zone.pprice[k];
                                    }
                                    parcelsjson.ptype= ptype;
                                    parcelsjson.totals= zone.totals;
                                   // parcelsjson.discount= zone.discount;  
                                    $(".parcelsPost").val(json2str(parcelsjson)); 
                            }
                              
							$(".order-total").html("Total: '.variable_get('uc_currency_sign','$').'" + zone.totals);
					    }else{
                            $(".header-warning").show();
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

	 drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/package_show.css', 
	 array('group' => CSS_DEFAULT, 'every_page' => TRUE));
	 
     return $build;
}

function liveparcels_getPackageprice($max,$dimenstext,$weighttext) {

	$weight = $dimenstext>$weighttext?$dimenstext:$weighttext;
	$items=0;
	if($max>0 && $dimenstext>0 && $weighttext>0){ 
		
		$arr = db_query("SELECT `weight`,`plength` FROM 
		`{liveparcels_package}` ORDER BY `pprice` DESC LIMIT 1")->fetchAssoc();
		if($arr['weight'] < $weight || $arr['plength'] < $max){
		     $items=0;
                }else{
                                        
                    $pprice = db_query("SELECT `pprice` FROM `{liveparcels_package}` 
                   WHERE `plength`>=". $max ." ORDER BY `pprice` ASC  LIMIT 1")
                   ->fetchField();
        $lprice = db_query("SELECT `pprice` FROM `{liveparcels_package}` 
                   WHERE `weight`>=". $weight ." 
                   ORDER BY `pprice` ASC  LIMIT 1")
                   ->fetchField();
        $nowprice=$lprice >$pprice ? $lprice:$pprice;
                    if($nowprice>0){
                      $items= $nowprice;
                    }else{
                    $items = db_query("SELECT `pprice` FROM `{liveparcels_package}` 
                    ORDER BY `pprice` ASC LIMIT 1 ")->fetchField();
                    }
              }
      }
		return $items;
}  

function liveparcels_getZoneprice() {
    $ajaxrequest = $_REQUEST['ajaxrequest'];
    $pricedata =json_decode($ajaxrequest,true);
	$action = $_REQUEST['action'];
    $parcels='';
    $totals=0;
    $error=0;
    $parcels_price=array();
	if($action =="updateprice" && count($pricedata)>0){
        foreach($pricedata as $key=>$pdata){
            $pprice=liveparcels_getPackageprice($pdata['max'],$pdata['dimenstext'],$pdata['weighttext']);
            
            if($pprice>0){
                $pzon = db_query("SELECT `multiplier` FROM `{liveparcels_zone_price}` 
		WHERE `zone_from_number`='". $pdata['postfrom'] ."' AND   
		`zone_to_number`='". $pdata['postto']."'")->fetchField();	
        
                if($pzon>0){
                    $pzone=$pzon*$pprice; 
                }else{
                    $pzone=0;
                }
               
            }else{
                  $pzone=0;  
            }
            $parcels_price[]=variable_get('uc_currency_sign','$').$pzone;
            $totals+=$pzone;
            if($pzone=='0'){
            $error=1;    
            }
            $parcels.=$pzone=='0' ? "<li>". $pdata['parcelnum'].": <span style='color:red'>??</span></li>":"<li>". $pdata['parcelnum'].": <span>".variable_get('uc_currency_sign','$').$pzone."</span></li>";
        }
	}
    $discount=50;
    $returndata=array('error'=>$error,'discount'=>$discount,'totals'=>$totals,'parcels'=>$parcels,'pprice'=>$parcels_price);
		echo json_encode($returndata);		
}

