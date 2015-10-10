function savenote(nid,atype){
	if(atype=="delete"){
		jQuery.post('/admin/liveparcels/settings/managepackage/distance_ajax',{position:nid,atype:atype},function(data){
			if(data){
				alert('Delete  success.');	
				 document.location.reload();
                //jQuery("#n"+nid).remove();
			}
		});
	}else{
	
		var position=parseInt(jQuery("#n"+nid+" .position").val());
		var oldposition=parseInt(jQuery("#n"+nid+" .oldposition").val());
		atype= oldposition==position && oldposition>0 ? 'update':'updateposition';
		

		var distance=parseInt(jQuery("#n"+nid+" .distance").val());
		var multiplier=parseInt(jQuery("#n"+nid+" .multiplier").val());


		if(position >0 && distance >0 && multiplier >0){
		var aid=parseInt(jQuery('.packagedata .package-line:last').index())-1;

		if( aid > 2){
			if(position>parseInt(jQuery(".package-line:eq(0) .position").val())){
                if(position>parseInt(jQuery(".package-line:eq("+(aid-1)+") .position").val())){
                    if(distance == parseInt(jQuery(".package-line:eq("+(aid-1)+") .distance").val()) || multiplier == parseInt(jQuery(".package-line:eq("+(aid-1)+") .multiplier").val()) || distance < parseInt(jQuery(".package-line:eq("+(aid-1)+") .distance").val()) || multiplier < parseInt(jQuery(".package-line:eq("+(aid-1)+") .multiplier").val()) ) {

                        alert('Please input values larger than the last row or in between the row you are trying to add to.');
                        return false;
                    }
                }else{
                    if(position != oldposition){
                        if(distance < parseInt(jQuery(".package-line:eq("+(position-2)+") .distance").val()) || multiplier < parseInt(jQuery(".package-line:eq("+(position-2)+") .multiplier").val()) || distance == parseInt(jQuery(".package-line:eq("+(position-2)+") .distance").val()) || multiplier == parseInt(jQuery(".package-line:eq("+(position-2)+") .multiplier").val()) || (distance == parseInt(jQuery(".package-line:eq("+(position-1)+") .distance").val()) || multiplier == parseInt(jQuery(".package-line:eq("+(position-1)+") .multiplier").val())) || distance >parseInt(jQuery(".package-line:eq("+(position-1)+") .distance").val()) || multiplier > parseInt(jQuery(".package-line:eq("+(position-1)+") .multiplier").val())) {
                            alert('Please input values larger than the last row or in between the row you are trying to add to.');
                            return false;
                        }
                    }else{
                  
                       if((distance == parseInt(jQuery(".package-line:eq("+(position-2)+") .distance").val()) || multiplier == parseInt(jQuery(".package-line:eq("+(position-2)+") .multiplier").val())) || distance < parseInt(jQuery(".package-line:eq("+(position-2)+") .distance").val()) || multiplier < parseInt(jQuery(".package-line:eq("+(position-2)+") .multiplier").val()) || distance >parseInt(jQuery(".package-line:eq("+(position)+") .distance").val()) || multiplier > parseInt(jQuery(".package-line:eq("+(position)+") .multiplier").val()) || (distance ==parseInt(jQuery(".package-line:eq("+(position)+") .distance").val()) || multiplier == parseInt(jQuery(".package-line:eq("+(position)+") .multiplier").val())) ) {
                            alert('Please input values larger than the last row or in between the row you are trying to add to.');
                            return false;
                        } 
                    }
                }
				var newid=position;
			}else{
				if((distance >parseInt(jQuery(".package-line:eq(0) .distance").val())  || multiplier > parseInt(jQuery(".package-line:eq(0)  .multiplier").val()) || (distance==parseInt(jQuery(".package-line:eq(0)  .distance").val())  || multiplier==parseInt(jQuery(".package-line:eq(0)  .multiplier").val()))) && position != oldposition ){
					alert('Please input values larger than the last row or in between the row you are trying to add to.');
					return false;
				}
				var newid=position;	
			}
					
		}else if(aid>1){

			if(position >= parseInt(jQuery(".package-line:eq(1) .position").val()) ){
                 if(distance <=parseInt(jQuery(".package-line:eq(0) .distance").val()) ||  multiplier <= parseInt(jQuery(".package-line:eq(0)  .multiplier").val())  && position != oldposition  ){
					alert('Please input values larger than the last row or in between the row you are trying to add to.');
					return false;
				}
                var newid= parseInt(jQuery(".package-line:eq(1) .position").val())+1;
               }else if(position >= parseInt(jQuery(".package-line:eq(0) .position").val()) ){
                   
                    if(((distance>=parseInt(jQuery(".package-line:eq(1) .distance").val())  || multiplier >=parseInt(jQuery(".package-line:eq(1) .multiplier").val())) || (distance<=parseInt(jQuery(".package-line:eq(0) .distance").val())  || multiplier <=parseInt(jQuery(".package-line:eq(0) .multiplier").val()))) && position != oldposition  ){
                             alert('Please input values larger than the last row or in between the row you are trying to add to.');						return false;
                    }
                        var newid= parseInt(jQuery(".package-line:eq(0) .position").val())+1;
                }else{ 
                    if((distance == parseInt(jQuery(".package-line:eq(0) .distance").val())  || multiplier >=parseInt(jQuery(".package-line:eq(0) .multiplier").val())) || (distance>=parseInt(jQuery(".package-line:eq(0) .distance").val())  || multiplier ==parseInt(jQuery(".package-line:eq(0) .multiplier").val()))  ){
                                        alert('Please input values larger than the last row or in between the row you are trying to add to.');
                                        return false;
                                }
                                var newid=1;
                }
		}else if(aid>0){
                if(position != parseInt(jQuery(".package-line:eq(0) .position").val()) ){
                     if((distance>=parseInt(jQuery(".package-line:eq(0) .distance").val())  || multiplier >parseInt(jQuery(".package-line:eq(0) .multiplier").val())) || (distance > parseInt(jQuery(".package-line:eq(0) .distance").val())  || multiplier >= parseInt(jQuery(".package-line:eq(0) .multiplier").val())) ){ 
                        var newid=parseInt(jQuery(".package-line:eq(0) .position").val())+1;              
                    }else{
                            var newid=parseInt(jQuery(".package-line:eq(0) .position").val())-1;   
                            newid=newid>1? newid:1;    
                    }
                    
                }else{
                var newid=position;   
                }
			}else{
                var	newid=1;
            }
		
		jQuery.post('/admin/liveparcels/settings/managepackage/distance_ajax',{position:newid,oldposition:oldposition,distance:distance,multiplier:multiplier,atype:atype},function(data){
				if(data){
               //alert(data);
               document.location.reload();

            }
        });
		}else{
		
			alert('Please input value in all fields.');
			return false;
		}
	}
}


(function ($){
$(document).ready(function(){
	$.post("/admin/liveparcels/settings/managepackage/distance_ajax",{atype:'packagelist'},function(data){
		if(data !='[]'){
			var ndata="";
			packageData=eval('(' + data + ')');	
			for (k in packageData){
				ndata+='<li class="package-line" id="n'+packageData[k].position+'"><div class="field-small"><input type="hidden" class="oldposition small-text" value="'+packageData[k].position+'" ><input type="text" class="position small-text hide" value="'+packageData[k].position+'" size="4">'+packageData[k].position+'</div><div class="field"><input type="text" class="distance small-text" value="'+packageData[k].distance+'"></div><div class="field"><input type="text" class="multiplier small-text" value="'+packageData[k].multiplier+'"></div><div class="field field-action"><a href="####" onclick="savenote('+packageData[k].position+',\'update\')">Edit </a> / <a href="####" onclick="savenote('+packageData[k].position+',\'delete\')">Delete</a></div></li>';		
					}
			
			jQuery(".packagedata li:first").after(ndata);
               $(".parcels-list input").attr("disabled","disabled");      
		}
	});
	
	

$('#edit-distance-type input').click(function(){

    if($(this).val()=='0'){
	$('#google-wrapper').hide();
    }else{
	$('#google-wrapper').show();
    }

});


});
	
})(jQuery);
