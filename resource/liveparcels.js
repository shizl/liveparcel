function savenote(nid,atype){
	if(atype=="delete"){
		jQuery.post('/admin/liveparcels/settings/managepackage',{position:nid,atype:atype},function(data){
			if(data){
				alert('Delete package success.');	
				 document.location.reload();
                //jQuery("#n"+nid).remove();
			}
		});
	}else{
	
		var position=parseInt(jQuery("#n"+nid+" .position").val());
		var oldposition=parseInt(jQuery("#n"+nid+" .oldposition").val());
		atype= oldposition==position && oldposition>0 ? 'update':'updateposition';
		
		var package_name=jQuery("#n"+nid+" .package_name").val();
		var weight=parseFloat(jQuery("#n"+nid+" .weight").val());
		

		var plength=parseFloat(jQuery("#n"+nid+" .plength").val());
		var pprice=parseFloat(jQuery("#n"+nid+" .pprice").val());
		weight=weight.toFixed(3);
		plength=plength.toFixed(3);
		pprice=pprice.toFixed(3);
	
		if(position >0 && package_name !='' && weight>0  && plength >0 && pprice >0){
		var aid=parseInt(jQuery('.packagedata .package-line:last').index())-1;
//alert(position);alert(aid);
		if( aid > 2){
			if(position>parseInt(jQuery(".package-line:eq(0) .position").val())){
                if(position>parseInt(jQuery(".package-line:eq("+(aid-1)+") .position").val())){
                    if((weight == parseFloat(jQuery(".package-line:eq("+(aid-1)+") .weight").val()) && plength <= parseFloat(jQuery(".package-line:eq("+(aid-1)+") .plength").val())) || (weight <= parseFloat(jQuery(".package-line:eq("+(aid-1)+") .weight").val()) && plength == parseFloat(jQuery(".package-line:eq("+(aid-1)+") .plength").val())) ) {

                        alert('Please input values larger than the last row or in between the row you are trying to add to.');
                        return false;
                    }
                }else{
                    if(position != oldposition){
                        if((weight == parseFloat(jQuery(".package-line:eq("+(position-2)+") .weight").val()) && plength <= parseFloat(jQuery(".package-line:eq("+(position-2)+") .plength").val())) ||(weight <= parseFloat(jQuery(".package-line:eq("+(position-2)+") .weight").val()) && plength == parseFloat(jQuery(".package-line:eq("+(position-2)+") .plength").val())) || (weight == parseFloat(jQuery(".package-line:eq("+(position-1)+") .weight").val()) && plength >= parseFloat(jQuery(".package-line:eq("+(position-1)+") .plength").val())) || (weight >=parseFloat(jQuery(".package-line:eq("+(position-1)+") .weight").val()) && plength == parseFloat(jQuery(".package-line:eq("+(position-1)+") .plength").val()))) {

                            alert('Please input values larger than the last row or in between the row you are trying to add to.');
                            return false;
                        }
                    }else{
                  
                       if((weight == parseFloat(jQuery(".package-line:eq("+(position-2)+") .weight").val()) && plength <= parseFloat(jQuery(".package-line:eq("+(position-2)+") .plength").val())) || (weight <= parseFloat(jQuery(".package-line:eq("+(position-2)+") .weight").val()) && plength == parseFloat(jQuery(".package-line:eq("+(position-2)+") .plength").val())) || (weight ==parseFloat(jQuery(".package-line:eq("+(position)+") .weight").val()) && plength >= parseFloat(jQuery(".package-line:eq("+(position)+") .plength").val())) || (weight >=parseFloat(jQuery(".package-line:eq("+(position)+") .weight").val()) && plength == parseFloat(jQuery(".package-line:eq("+(position)+") .plength").val())) ) {

                            alert('Please input values larger than the last row or in between the row you are trying to add to.');
                            return false;
                        } 
                    }
                }
				var newid=position;
			}else{
				if(weight >parseFloat(jQuery(".package-line:eq(0) .weight").val())  || plength > parseFloat(jQuery(".package-line:eq(0)  .plength").val()) || (weight==parseFloat(jQuery(".package-line:eq(0)  .weight").val())  && plength==parseFloat(jQuery(".package-line:eq(0)  .plength").val())) ){
					alert('Please input values larger than the last row or in between the row you are trying to add to.');
					return false;
				}
				var newid=position;	
			}
					
		}else if(aid>1){

			if(position >= parseInt(jQuery(".package-line:eq(1) .position").val()) ){
                 if(weight <=parseFloat(jQuery(".package-line:eq(1) .weight").val()) &&  plength <= parseFloat(jQuery(".package-line:eq(1)  .plength").val())  && position != oldposition  ){
					alert('Please input values larger than the last row or in between the row you are trying to add to.');
					return false;
				}
                var newid= parseInt(jQuery(".package-line:eq(1) .position").val())+1;
               }else if(position >= parseInt(jQuery(".package-line:eq(0) .position").val()) ){
                   
                if(((weight>=parseFloat(jQuery(".package-line:eq(1) .weight").val())  && plength >=parseFloat(jQuery(".package-line:eq(1) .plength").val())) || (weight<=parseFloat(jQuery(".package-line:eq(0) .weight").val())  && plength <=parseFloat(jQuery(".package-line:eq(0) .plength").val()))) && position != oldposition  ){
                         alert('Please input values larger than the last row or in between the row you are trying to add to.');						return false;
                }
                    var newid= parseInt(jQuery(".package-line:eq(0) .position").val())+1;
                }else{ 
                    if(weight>=parseFloat(jQuery(".package-line:eq(0) .weight").val())  && plength >=parseFloat(jQuery(".package-line:eq(0) .plength").val()) && position != oldposition  ){
                                        alert('Please input values larger than the last row or in between the row you are trying to add to.');
                                        return false;
                                }
                                var newid=1;
                }
		}else if(aid>0){
                if(position != parseInt(jQuery(".package-line:eq(0) .position").val()) ){
                     if((weight>=parseFloat(jQuery(".package-line:eq(0) .weight").val())  && plength >parseFloat(jQuery(".package-line:eq(0) .plength").val())) || (weight > parseFloat(jQuery(".package-line:eq(0) .weight").val())  && plength >= parseFloat(jQuery(".package-line:eq(0) .plength").val())) ){ 
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
		
		jQuery.post('/admin/liveparcels/settings/managepackage',{position:newid,oldposition:oldposition,package_name:package_name,weight:weight,plength:plength,pprice:pprice,atype:atype},function(data){
				if(data){
              // alert(data);
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
	$.post("/admin/liveparcels/settings/managepackage",{atype:'packagelist'},function(data){
		if(data !='[]'){
			var ndata="";
			packageData=eval('(' + data + ')');	
			for (k in packageData){
				ndata+='<li class="package-line" id="n'+packageData[k].position+'"><div class="field-small"><input type="hidden" class="oldposition small-text" value="'+packageData[k].position+'" ><input type="text" class="position small-text hide" value="'+packageData[k].position+'" size="4">'+packageData[k].position+'</div><div class="field"><input type="text" value="'+packageData[k].package_name+'" class="package_name small-text"></div><div class="field"><input type="text" class="weight small-text" value="'+packageData[k].weight+'"></div><div class="field-small"><input type="text" class="plength small-text" value="'+packageData[k].plength+'"></div><div class="field-small"><input type="text" class="pprice small-text" value="'+packageData[k].pprice+'"></div><div class="field"><a href="####" onclick="savenote('+packageData[k].position+',\'update\')">Edit </a> / <a href="####" onclick="savenote('+packageData[k].position+',\'delete\')">Delete</a></div></li>';		
					}
			
			jQuery(".packagedata li:first").after(ndata);
		}
	});
	
	$('#update-factor').click(function(){
		var factor=parseFloat($('#factor').val());
		if(factor>0){
            $.post('/admin/liveparcels/settings/updatefactor',{factor:factor},function(msg){
                if(msg){
                alert('Updated successfully.');
                }
            });
		}else{
		alert('Please input float value');
		}

	});	
    $('.zone-pickup').change(function(){
            if($('.useregion').attr('checked')==true){
                var region_id=$('.state-pickup').val();
            }else{
                var region_id='';
            }
            $.post('/admin/liveparcels/settings/zoneresult',{region:region_id,zone:$(this).val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
                if(msg){
                     $('.pickup-result .draggable').remove();
                    $('.table-head').after(msg);
                }
            });
       
    });
    $('.state-pickup').change(function(){
            $.post('/admin/liveparcels/settings/updatezone',{region:$(this).val()},function(msg){
                if(msg){
                     $('.zone-pickup').html(msg);
                    if($('.useregion').attr('checked')==true){
                        var region_id=$('.state-pickup').val();
                    }else{
                        var region_id='';
                    }
                 $.post('/admin/liveparcels/settings/zoneresult',{region:region_id,zone:$('.zone-pickup').val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
                if(msg){
                     $('.pickup-result .draggable').remove();
                    $('.table-head').after(msg);
                   
                }
            });
                }
            });
           
        
    });
    $('.znumber').click(function(){
        
        var zid= $('.oid').val()!='asc' ?  'asc':'desc';
        $('.table-head img').addClass('hide');
        $('.table-head th').removeClass('active');
        $(this).parent().addClass('active');
        $('.table-head input').val('');
        $(this).find('img').removeClass('hide');
        $(this).find('img').attr('src','/sites/all/modules/liveparcels/resource/arrow-'+zid+'.png');
       $('.oid').val(zid);
       if($('.useregion').attr('checked')==true){
            var region_id=$('.state-pickup').val();
        }else{
            var region_id='';
        }
        $.post('/admin/liveparcels/settings/zoneresult',{region:region_id,zone:$('.zone-pickup').val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
                if(msg){
                    $('.pickup-result .draggable').remove();
                    $('.table-head').after(msg);
                }
            });
    });
    $('.zname').click(function(){
        
        var zid= $('.oname').val()!='asc' ?  'asc':'desc';
        $('.table-head img').addClass('hide');
        $('.table-head th').removeClass('active');
        $(this).parent().addClass('active');
        $('.table-head input').val('');
        $(this).find('img').removeClass('hide');
        $(this).find('img').attr('src','/sites/all/modules/liveparcels/resource/arrow-'+zid+'.png');
       $('.oname').val( zid);
       if($('.useregion').attr('checked')==true){
            var region_id=$('.state-pickup').val();
        }else{
            var region_id='';
        }
        $.post('/admin/liveparcels/settings/zoneresult',{region:region_id,zone:$('.zone-pickup').val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
                if(msg){
                    $('.pickup-result .draggable').remove();
                    $('.table-head').after(msg);
                }
            });
    });
     $('.zstate').click(function(){
        var zid= $('.ostate').val()!='asc' ?  'asc':'desc';
        $('.table-head img').addClass('hide');
        $('.table-head th').removeClass('active');
        $(this).parent().addClass('active');
         $('.table-head input').val('');
        $(this).find('img').removeClass('hide');
        $(this).find('img').attr('src','/sites/all/modules/liveparcels/resource/arrow-'+zid+'.png');
       $('.ostate').val( zid);
        if($('.useregion').attr('checked')==true){
            var region_id=$('.state-pickup').val();
        }else{
            var region_id='';
        }
        $.post('/admin/liveparcels/settings/zoneresult',{region:region_id,zone:$('.zone-pickup').val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
                if(msg){
                    $('.pickup-result .draggable').remove();
                    $('.table-head').after(msg);
                }
            });
    });
   $('.useregion').click(function(){
        if($(this).attr('checked')==true){
            $('.show-region').show();
            var region_id=$('.state-pickup').val();
        }else{
            $('.show-region').hide();
            var region_id='';
        }
        
        $.post('/admin/liveparcels/settings/updatezone',{region:region_id},function(msg){
                if(msg){
                     $('.zone-pickup').html(msg);
                 $.post('/admin/liveparcels/settings/zoneresult',{region:region_id,zone:$('.zone-pickup').val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
                if(msg){
                     $('.pickup-result .draggable').remove();
                    $('.table-head').after(msg);
                   
                }
            });
                }
            });
    });
     $.post('/admin/liveparcels/settings/zoneresult',{region:'',zone:$('.zone-pickup').val(),oid:$('.oid').val(),oname:$('.oname').val(),ostate:$('.ostate').val()},function(msg){
            if(msg){
                $('.pickup-result .draggable').remove();
                $('.table-head').after(msg);
            }
       });
});
	
})(jQuery);
