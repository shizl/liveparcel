jQuery(document).ready(function(){


str = jQuery('dd.userpoints-item-reason').text();

str1 =  str.substring(str.indexOf('<'),str.indexOf('>')+1);
str = str.replace(str1,'');

str2 = str.substring(str.indexOf('<'),str.indexOf('>')+1);
str = str.replace(str2,'');

if(jQuery('dd.userpoints-item-reason a').text()!=''){

 jQuery('dd.userpoints-item-reason a').text(str);

}else{
 jQuery('dd.userpoints-item-reason').html(str);
}


});
