<?php

/**
 * @file
 * Store administration menu items.
 */

/**
 * Menu callback which provides the store administration overview page.
 */
function liveparcels_admin_settings() {
  if((!empty($_REQUEST['act']) && $_REQUEST['act']<>'') || (!empty($_REQUEST['fact']) && $_REQUEST['fact']<>'')){
    liveparcels_fileupload();
  }
  liveparcels_updatecount();
  $rows['package'] = array(array('data' => '<div class="parcels-title">Define package maximum values and price</div><div class="parcels-body"><div class="parcels-note"><p>To calculate the parcel price, we use either the Dimensional Weight or the Dead Weight, whichever is the greater of the two values.</p>
        <p>For more information, visit <a href="http://en.wikipedia.org/wiki/Dimensional_weight" target="_blank">http://en.wikipedia.org/wiki/Dimensional_weight</a></p>
        <p>Dimensional weight = (L cm x W cm x H cm) x Dimensional Factor</p></div> <div class="parcels-factor">Dimensional Factor: <input type="text" class="small-text" value="'.variable_get('liveparcels_factor',0.0002).'" id="factor"> &nbsp;&nbsp;<input type="button" value="update" class="form-submit" id="update-factor"></div>
        <div class="package-table"><ul class="packagedata">
        <li id="phead"><div class="field-small">Position</div><div class="field">Package Name</div><div class="field">Weight (kg)</div><div class="field-small">Length (cm)</div><div class="field-small">Price ('.variable_get('uc_currency_sign','$').')</div><div class="field">Edit/Delete</div></li>
        <li class="package-line" id="n0"><div class="field-small"><input type="hidden" class="oldposition small-text" value="0"><input type="text" class="position small-text" size="4"></div><div class="field"><input type="text" class="package_name small-text"></div><div class="field"><input type="text" class="weight small-text"></div><div class="field-small"><input type="text" class="plength small-text"></div><div class="field-small"><input type="text" class="pprice small-text"></div><div class="field"><a href="####" onclick="savenote(0,\'updateposition\')">Save</a></div></li></ul></div></div>'));
  $rows['zone_post'] = array(array('data' => '<div class="parcels-title">Postcode, region and zone settings</div><div class="parcels-body"><div class="parcels-note"><p>If you would like to check the complete list of postcodes/regions/zones stored in LiveParcels, click export and open the saved csv file using spreadsheet software such as Microsoft Excel or <a href="http://www.libreoffice.org/" target="_blank">LibreOffice</a>. After you have modified the csv, you can update the postcode, region and zone settings on LiveParcels by clicking the Choose File button, browse and import the csv file you have modified. Please make sure the csv you import follows the same structure as the csv exported from LiveParcels or it will not be processed correctly.</p> <p>In order to allow you to manage/set the pricing more easily, multiple postcodes (associated with suburb/state) are grouped into zones; multiple zones are grouped into regions. Grouping of zones into region is optional, its only purpose is to allow you to find the zones more easily in the price table below. You can leave the region column blank if you don&#39t want to use region grouping. If you decide to group zones into region, please make sure that each zone only belongs to one region or it will be ignored.</p><p>By default, we do not provide the postcode database. You would have to provide your own. You are encouraged to find the postcode database(csv) of the country you requires from your local post office&#39s web site or you may can try <a href="http://download.geonames.org/export/zip/" target="_blank">geoname&#39s postcode database</a>. Do note that geoname&#39s postcode database tends to have missing information for each postcode and you may have to fill it in manually. We can provide some assistance if you have troubles here.</p>
        </div> <div class="parcels-factor">Postcode Settings: The current data contain '.(variable_get('liveparcels_postcount') >0 ? variable_get('liveparcels_postcount').' rows':variable_get('liveparcels_postcount').'row').'<br><form id="zonepost" class="submit_form1" method="post" action="/admin/liveparcels/settings" enctype="multipart/form-data"> <input type="hidden" name="fact" value="importzonepost"> <input type="file" id="zone-import" name="zonepost">  <input type="submit" value="Upload" class="form-submit" id="import-zone"> <input type="button" value="Export" class="form-submit" id="export-zone"  onclick="location.href=\'/admin/liveparcels/settings/fileupload/ajax/?act=exportzonepost\'"></form></div>
        <div class="parcels-note"><strong style="color:#ff0000">Warning: Uploading a new csv file will replace the existing postcode/zone settings on the system and reset zone price multiplier to zero. Please make sure you have made a backup before you do this.
        </strong></div>
        <div class="parcels-title">Zone price multiplier</div><div class="parcels-body"><div class="parcels-note"><p>To calculate the price to deliver a package from one zone to another, you need to configure the zone multipler here which multiples the base price of a package as configured above.</p>
        <p>After you have imported the postcode region and zone settings, click the export button below to obtain the default zone price multipler csv, modify and then import it. </p>
        </div> <div class="parcels-factor">Import/Export zone price multipler: The current data contain '.(variable_get('liveparcels_pricecount') >0 ? variable_get('liveparcels_pricecount').' rows':variable_get('liveparcels_pricecount').'row').'<br><form id="zoneprice" class="submit_form1" method="post" action="/admin/liveparcels/settings" enctype="multipart/form-data" > <input type="hidden" name="fact" value="importzoneprice"> <input type="file" id="zone-pirce-import" name="zoneprice">  <input type="submit" value="Upload" class="form-submit" id="import-zone-pirce"> <input type="button" value="Export" class="form-submit" id="export-zone-pirce" onclick="location.href=\'/admin/liveparcels/settings/fileupload/ajax/?act=exportzoneprice\'" ></form></div><div class="parcels-note"><strong style="color:#ff0000">Warning: Uploading a new csv file will replace the existing zone price multipler on the system. Please make sure you have made a backup before you do this.</strong></div>'));

  $rows['zone_price_show'] = array(array('data' => '<div class="parcels-title">Price table (calculated)</div><div class="parcels-body"><div class="parcels-note"><p>The price table below is calculated based on your settings above. It shows you the cost to deliver a parcel from the pickup zone to different delivery zone. Please select a pickup zone to see the corresponding price.</p>
        <p><input type="checkbox" value="1" class="useregion"> Enable grouping of zones into region.</p>
        </div> <div class="pickup-search">Pickup from:   &nbsp;&nbsp;&nbsp; <span class="show-region">Region: <select name="state-pickup" class="form-select state-pickup">'.liveparcels_zonedata('stateoption').'</select>  </span>&nbsp;&nbsp;&nbsp;Zone name: <select name="zone-pickup" class="form-select zone-pickup">'.liveparcels_zonedata('zoneoption').'</select> </div><div class="pickup-result"><input type="hidden" class="path_page" value="oadmin"><table><tr class="table-head"><th><a href="####" class="znumber">Zone number <input type="hidden" class="oid" value=""><img typeof="foaf:Image" src="/sites/all/modules/liveparcels/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th><th><a href="####" class="zname">Zone Name<input type="hidden" class="oname" value="asc"><img typeof="foaf:Image" src="/sites/all/modules/liveparcels/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th><th><a href="####" class="zstate">Region <input type="hidden" class="ostate" value=""><img typeof="foaf:Image" src="/sites/all/modules/liveparcels/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th>'.liveparcels_packagename('name').'</tr></table></div> '.(!empty($_SESSION['liveparcels_status']) && count($_SESSION['liveparcels_status'])>1 ? '<script> jQuery(\'.region-content\').before(\'<div id="console" class="clearfix"><div class="messages '.( $_SESSION['liveparcels_status']['status'] ? 'status':'error').'"><h2 class="element-invisible">'.( $_SESSION['liveparcels_status']['status'] ? 'Success':'Falise').' message</h2>'. $_SESSION['liveparcels_status']['message'].'</div></div>\');</script>':'')));
  unset($_SESSION['firrow']);
  unset($_SESSION['liveparcels_status']);
  $build['liveparcels'] = array(
      '#theme' => 'table',
      /*  Page heading disabled    */
      /*	 '#caption' => '<h2>' . t('Postage calculator Admin Settings') . '</h2>',*/
      '#rows' => $rows,
      '#attributes' => array('class' => array('live-parcels-status')),
      );
  drupal_add_js(drupal_get_path('module', 'liveparcels') . '/resource/liveparcels.js');
  drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/liveparcels.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));

  return $build;
}

function liveparcels_factor_settings(){
  $factor=$_REQUEST['factor'];
  variable_set('liveparcels_factor',$factor);
  echo 1;
}
function liveparcels_managepackage(){
  $atype=!empty($_REQUEST['atype']) ? trim($_REQUEST['atype']):'';
  if($atype=="packagelist"){
    $items=array();
    $result = db_query("SELECT * FROM `{liveparcels_package}` ORDER BY `position` ASC");
    foreach ($result as $row) {
      $items[$row->position] = array(
          'position' => $row->position,
          'package_name' => $row->package_name,
          'weight' => $row->weight,
          'plength' => $row->plength,
          'pprice' => $row->pprice,
          );
    }

    echo json_encode($items);

  }elseif($atype=="updateposition"){
    db_query("UPDATE `{liveparcels_package}` SET `position`=`position`+1 WHERE `position` >= '".$_REQUEST['position']."' ORDER BY `position` DESC");
    db_query("INSERT INTO `{liveparcels_package}` VALUES('".$_REQUEST['position']."','".$_REQUEST['package_name']."','".$_REQUEST['weight']."','".$_REQUEST['plength']."','".$_REQUEST['pprice']."')");
    echo 1;

  }elseif($atype=="update"){
    db_query("UPDATE `{liveparcels_package}` SET `package_name`='".$_REQUEST['package_name']."',`weight`='".$_REQUEST['weight']."',`plength`='".$_REQUEST['plength']."',`pprice`='".$_REQUEST['pprice']."' WHERE `position`='".$_REQUEST['oldposition']."'");			
    echo 1;

  }elseif($atype=="delete"){

    $result=db_query("DELETE FROM `{liveparcels_package}` WHERE `position`='".$_REQUEST['position']."'");
    $result = db_query("SELECT `position` FROM `{liveparcels_package}` WHERE `position` > '".$_REQUEST['position']."' ");

    if(count($result)>0){
      foreach ($result as $row) {
        db_query("UPDATE `{liveparcels_package}` SET `position`=`position`-1 WHERE `position` >= '".$row->position."'  ORDER BY `position` ASC");
      } 		
    }	
    echo 1;
  }
}

function liveparcels_fileupload()
{
  $action = empty($_REQUEST['act']) ? !empty($_REQUEST['fact']) ? $_REQUEST['fact']:'':$_REQUEST['act'];
  if($action=='exportzonepost'){
    $result = db_query("SELECT * FROM `{liveparcels_zone_post}`");
    if(count($result)>0){
      $data="postcode,suburb,state,region,zone_number,zone_name\n";
      foreach($result as $row){
        $data.=$row->pcode.','.$row->locality.','.$row->state.','.$row->region.','.$row->zone_number.','.$row->bspname."\n";
      }
      liveparcels_exportcvs($data,$file_name = 'export_zone_post');			
    }		

  }elseif($action=='exportzoneprice'){
    $result = db_query("SELECT * FROM `{liveparcels_zone_price}`");

    if(count($result)>0){
      $data="zone_from_number,zone_from,zone_from_region,zone_to_number,zone_to,zone_to_region,multiplier\n";

      foreach($result as $row){
        $data.=$row->zone_from_number.','.$row->zone_from.','.$row->zone_from_region.','.$row->zone_to_number.','.$row->zone_to.','.$row->zone_to_region.','.$row->multiplier."\n";
      }
      liveparcels_exportcvs($data,$file_name = 'export_zone_price');			
    }

  }elseif($action=='importzonepost'){

    $picname = @$_FILES['zonepost']['name'];
    $picsize = @$_FILES['zonepost']['size'];
    $error='';
    if ($picname != "") {
      if ($picsize > 10240000) {
        $error.='file size more than 10M';
      }
      $type = strstr($picname, '.');
      if ($type != ".csv" && $type != ".xls") {
        $error.='file type error！ Only upload csv or xls.';

      }
      if($error==''){
        $handle = fopen($_FILES['zonepost']['tmp_name'], 'r'); 
        $result = liveparcels_inputcsv($handle); //query_csv
        $len_result = count($result); 
        if($len_result==0){ 
          $error.='Not data '; 
        } 

        $secount=0;
        $fcount=0;
        $fline="";
        $data_values="";
        if($result[0][4]<>""){
          for ($i = 0; $i < $len_result; $i++) {  
            if($result[$i][0]<>"" && $result[$i][1]<>"" && $result[$i][2]<>"" && $result[$i][3]<>"" && $result[$i][4]<>"" && $result[$i][5]<>""){
              $secount++;
              $result[$i][1]=str_replace("'","\'",$result[$i][1]);
              $result[$i][2]=str_replace("'","\'",$result[$i][2]);
              $result[$i][3]=str_replace("'","\'",$result[$i][3]);
              $result[$i][5]=str_replace("'","\'",$result[$i][5]);
              $data_values .= ( $secount>1 ? ',':'')."('".$result[$i][0]."','".$result[$i][1]."','".$result[$i][2]."','".$result[$i][3]."','".$result[$i][4]."','".$result[$i][5]."')"; 
            }else{
              $fcount++;
              $fline.=($fcount>1 ? ',':'').$i;
            }
          }  
        }else{
          $error.= 'Data formart error<br>';
        }
        fclose($handle); 
        if($data_values<>''){
          db_query("DELETE FROM `{liveparcels_zone_post}`;");//delete old data
          $query = db_query("INSERT INTO `{liveparcels_zone_post}`  VALUES $data_values;");//insert data  

          db_query("DELETE FROM `{liveparcels_zone_price}`;");//delete old data
          $resultpost = db_query("SELECT `zone_number`,`bspname`,`region` FROM `{liveparcels_zone_post}` GROUP BY `zone_number` ORDER BY `BSPname` ASC ");
          $zonepost=array();
          foreach($resultpost as $rpost){
            $bspname=str_replace("'","\'",$rpost->bspname);
            $region=str_replace("'","\'",$rpost->region);
            $zonepost[$rpost->zone_number]=array('name'=>$bspname,'region'=>$region);
          }
          $price_data_values='';
          $i=0;
          foreach($zonepost as $key=>$val){
            foreach($zonepost as $tokey=>$toval){
              $i++;

              $price_data_values .= ( $i>1 ? ',':'')."('".$key."','".$val['name']."','".$val['region']."','".$tokey."','".$toval['name']."','".$toval['region']."','0')";

            }
          }

          $query = db_query("INSERT INTO `{liveparcels_zone_price}`  VALUES $price_data_values;");//insert data  

        }

      }
    }else{
      $error.='Please select upload file.';
    }

    $_SESSION['liveparcels_status']=array('status'=>$error<>'' ? 0:1,'message'=>$error <> '' ? $error : 'Failure Line:'.$fline.';<br>Failure count:'.$fcount.';<br>Success count:'.$secount);
  }elseif($action=='importzoneprice'){
    $picname = @$_FILES['zoneprice']['name'];
    $picsize = @$_FILES['zoneprice']['size'];
    $error='';
    if ($picname != "") {
      if ($picsize > 10240000) {
        $error.='file size more than 10M<br>';
        ;
      }
      $type = strstr($picname, '.');
      if ($type != ".csv" && $type != ".xls") {
        $error.= 'file type error！ Only upload csv or xls.<br>';

      }
      if($error==""){
        $handle = fopen($_FILES['zoneprice']['tmp_name'], 'r'); 
        $result = liveparcels_inputcsv($handle); //query_csv
        $len_result = count($result); 
        if($len_result==0){ 
          $error.= 'Not data <br>'; 

        } 
        $secount=0;
        $fcount=0;
        $fline="";
        $data_values="";
        if($result[0][4]<>""){
          for ($i = 0; $i < $len_result; $i++) {  
            if($result[$i][0]<>"" && $result[$i][1]<>"" && $result[$i][2]<>"" && $result[$i][3]<>"" && $result[$i][4]<>"" && $result[$i][5]<>"" && $result[$i][6]<>""){
              $secount++;
              $result[$i][1]=str_replace("'","\'",$result[$i][1]);
              $result[$i][2]=str_replace("'","\'",$result[$i][2]);
              $result[$i][4]=str_replace("'","\'",$result[$i][4]);
              $result[$i][5]=str_replace("'","\'",$result[$i][5]);
              $data_values .= ($secount>1 ? ',':'')."('".$result[$i][0]."','".$result[$i][1]."','".$result[$i][2]."','".$result[$i][3]."','".$result[$i][4]."','".$result[$i][5]."','".$result[$i][6]."')"; 
            }else{
              $fcount++;
              $fline.=($fcount>1 ? ',':'').$i;
            }
          } 
        }else{
          $error.= 'Data formart error<br>';
        }
        fclose($handle); 
        if($data_values<>''){
          db_query("DELETE FROM `{liveparcels_zone_price}`;");//delete old data
          $query = db_query("INSERT INTO `{liveparcels_zone_price}`  VALUES $data_values;");//insert data  
        }
      }
    }else{
      $error.='Please select upload file.';
    }

    $_SESSION['liveparcels_status']=array('status'=>$error<>'' ? 0:1,'message'=>$error <> '' ? $error : 'Failure Line:'.$fline.';<br>Failure count:'.$fcount.';<br>Success count:'.$secount);
  }

}

/*
   export csv file package post
 */
function liveparcels_exportcvs($data,$file_name = 'export')
{
  header('Content-Type: text/cvs'); 
  header ( "Content-type:application/vnd.ms-excel;charset=utf-8" );
  $str = mb_convert_encoding($file_name, 'gbk', 'utf-8');         
  header('Content-Disposition: attachment;filename="' .$str . '.csv"');      
  header('Cache-Control:must-revalidate,post-check=0,pre-check=0');        
  header('Expires:0');         
  header('Pragma:public');
  echo $data;    
  exit;
}

function liveparcels_inputcsv($handle) { 
  $out = array (); 
  $n = 0; 

  if(count(fgetcsv($handle, 10000,","))>1){
    while ($data = fgetcsv($handle, 10000,",")) { 
      $num = count($data); 
      for ($i = 0; $i < $num; $i++) { 
        $out[$n][$i] = $data[$i]; 
      } 
      $n++; 
    } 
  }elseif(count(fgetcsv($handle, 10000,"\t"))>1){
    while ($data = fgetcsv($handle, 10000,"\t")) { 
      $num = count($data); 
      for ($i = 0; $i < $num; $i++) { 

        $out[$n][$i] = $data[$i]; 
      } 
      $n++; 
    } 
  }elseif(count(fgetcsv($handle, 1000," "))>1){
    while ($data = fgetcsv($handle, 1000," ")) { 
      $num = count($data); 
      for ($i = 0; $i < $num; $i++) { 

        $out[$n][$i] = $data[$i]; 
      } 
      $n++; 
    } 
  }
  return $out; 
}
function liveparcels_zoneresult(){
  $oid=!empty($_REQUEST['oid']) ? $_REQUEST['oid']:'';
  $oname=!empty($_REQUEST['oname']) ? $_REQUEST['oname']:'';
  $ostate=!empty($_REQUEST['ostate']) ? $_REQUEST['ostate']:'';
  if($oid<>'' || $oname<>'' || $ostate<>''){
    if($oid<>''){
      $orderby= $oid<>'desc' ? " ORDER BY `zone_to_number` ASC":" ORDER BY `zone_to_number` DESC";
    }
    if($ostate<>''){
      $orderby= $ostate<>'desc' ? " ORDER BY `zone_to_region` ASC":" ORDER BY `zone_to_region` DESC";
    }
    if($oname<>''){
      $orderby= $oname<>'desc' ? " ORDER BY `zone_to` ASC":" ORDER BY `zone_to` DESC";
    }
  }else{
    $orderby= " ORDER BY `zone_to` ASC"; 
  }
  if($_REQUEST['region'] <>'' && $_REQUEST['zone']<>'' ){
    $result = db_query("SELECT `zone_to`,`zone_to_number`,`zone_to_region`,`multiplier` FROM `{liveparcels_zone_price}` WHERE `zone_from_region`='".$_REQUEST['region']."' AND `zone_from_number`='".$_REQUEST['zone']."' ".$orderby);
  }elseif($_REQUEST['region'] <>''){
    $result = db_query("SELECT `zone_to`,`zone_to_number`,`zone_to_region`,`multiplier` FROM `{liveparcels_zone_price}` WHERE `zone_from_region`='".$_REQUEST['region']."' ".$orderby);
  }elseif($_REQUEST['zone'] <>''){
    $result = db_query("SELECT `zone_to`,`zone_to_number`,`zone_to_region`,`multiplier` FROM `{liveparcels_zone_price}` WHERE `zone_from_number`='".$_REQUEST['zone']."' ".$orderby);
  }else{
    $result = db_query("SELECT `zone_to`,`zone_to_number`,`zone_to_region`,`multiplier` FROM `{liveparcels_zone_price}` ".$orderby);  
  }


  
if($_REQUEST['path'] == 'ouser'){


if(module_exists(lp_discount)){

  $s=0;
  $trs='';
  $tprice=liveparcels_packagename('price');

    foreach ($result as $row) {
    $packdata="";
    foreach($tprice as $pprice){
      $packdata.=$row->multiplier > 0 ? '<td>'.variable_get('uc_currency_sign','$').lp_discount_get_pricing($pprice*floatval($row->multiplier)).'</td>':'<td>Undefined</td>';
    }
    $s++;
    $trs .= '<tr class="draggable '.($s%2 ==0 ? 'old':'even').'"><td>'. $row->zone_to_number.'</td><td>'.$row->zone_to.'</td><td>'.$row->zone_to_region.'</td>'.$packdata.'</tr>';
  }

}else{


  $s=0;
  $trs='';
  $tprice=liveparcels_packagename('price');
  foreach ($result as $row) {
    $packdata="";
    foreach($tprice as $pprice){
      $packdata.=$row->multiplier > 0 ? '<td>'.variable_get('uc_currency_sign','$').$pprice*floatval($row->multiplier).'</td>':'<td>Undefined</td>';
    }
    $s++;
    $trs .= '<tr class="draggable '.($s%2 ==0 ? 'old':'even').'"><td>'. $row->zone_to_number.'</td><td>'.$row->zone_to.'</td><td>'.$row->zone_to_region.'</td>'.$packdata.'</tr>';
  }




}
  
}elseif($_REQUEST['path'] == 'oadmin'){
  $s=0;
  $trs='';
  $tprice=liveparcels_packagename('price');
  foreach ($result as $row) {
    $packdata="";
    foreach($tprice as $pprice){
      $packdata.=$row->multiplier > 0 ? '<td>'.variable_get('uc_currency_sign','$').$pprice*floatval($row->multiplier).'</td>':'<td>Undefined</td>';
    }
    $s++;
    $trs .= '<tr class="draggable '.($s%2 ==0 ? 'old':'even').'"><td>'. $row->zone_to_number.'</td><td>'.$row->zone_to.'</td><td>'.$row->zone_to_region.'</td>'.$packdata.'</tr>';
  }

}
  echo $trs;

}
function liveparcels_packagename($type ='name'){//price or name
  $resultpackage = db_query("SELECT `package_name`,`pprice` FROM `{liveparcels_package}` ORDER BY `position` ASC");

  if($type=='price'){
    $tprice=array();
    foreach($resultpackage as $pack){
      $tprice[]=$pack->pprice;
    }  
    return $tprice; 
  }elseif($type=='name'){
    $thead='';
    foreach($resultpackage as $pack){
      $thead.='<th>'.$pack->package_name.'</th>';
    } 
    return $thead;
  }



}
/**
  live parcels pickup search option and result 
type: option or result table
 */

function liveparcels_zonedata($atype='zoneoption',$region=''){
  if($atype=="zoneoption"){
    $options ='';
    if($region<>''){
      $andwhere=" WHERE `zone_from_region`='".$region."'";  
    }else{
      $andwhere='';
    }
    $result = db_query("SELECT `zone_from`,`zone_from_number` FROM `{liveparcels_zone_price}`  ".$andwhere."  GROUP BY `zone_from` ORDER BY `zone_from` ASC ");

    foreach ($result as $row) {

      $options .= '<option value="'. $row->zone_from_number.'" >'. $row->zone_from.'</option>';
    }
    return $options;
  }elseif($atype=="stateoption"){
    $options ='';
    $result = db_query("SELECT `zone_from_region` FROM `{liveparcels_zone_price}` GROUP BY `zone_from_region` ORDER BY `zone_from_region` ASC ");
    $firrow='';
    foreach ($result as $row) {
      if($options==''){
        $firrow= $row->zone_from_region;
      }
      $options .= '<option value="'. $row->zone_from_region.'" >'. $row->zone_from_region.'</option>';
    }
    $_SESSION['firrow']=$firrow;
    return $options;
  }
}

/*live parcels post or price count rows*/
function liveparcels_updatecount(){
  $result = db_query("SELECT count(`pcode`) as post FROM `{liveparcels_zone_post}`");
  $result1 = db_query("SELECT count(`zone_from`) as price FROM `{liveparcels_zone_price}`");
  foreach ($result as $row) {
    variable_set('liveparcels_postcount',$row->post);
  }
  foreach ($result1 as $row) {
    variable_set('liveparcels_pricecount',$row->price);
  }

}
/*live parcels post or price count rows*/
function liveparcels_updatezone(){

  echo liveparcels_zonedata('zoneoption',$_REQUEST['region']);

}
function liveparcels_configpage() {
  $menu = menu_get_item('admin/liveparcels');
  $content = system_admin_menu_block($menu);

  $build['menu'] = array(
      '#theme' => 'admin_block_content',
      '#content' => $content,
      '#weight' => 5,
      );

  return $build;
}

function liveparcels_live_parcel_price() {
    global $user;
    if ($user->uid==0) {
         header("location:/user");
        }
    $rows['package'] = array(array('data' => '<div class="parcels-list"><div class="parcels-title">Define package maximum values and price</div><div class="parcels-body"><div class="parcels-note"><p>To calculate the parcel price, we use either the Dimensional Weight or the Dead Weight, whichever is the greater of the two values.</p>
        <p>For more information, visit <a href="http://en.wikipedia.org/wiki/Dimensional_weight" target="_blank">http://en.wikipedia.org/wiki/Dimensional_weight</a></p>
        <p>Dimensional weight = (L cm x W cm x H cm) x Dimensional Factor</p></div> <div class="parcels-factor">Dimensional Factor:'.variable_get('liveparcels_factor',0.0002).'</div>
        <ul class="packagedata">
        <li id="phead"><div class="field-small">Position</div><div class="field">Package Name</div><div class="field">Weight (kg)</div><div class="field-small">Length (cm)</div><div class="field-small">Price ('.variable_get('uc_currency_sign','$').')</div></li>
        </ul></div></div>'));
$rows['zone_price_show'] = array(array('data' => '<div class="parcels-title">Price table (calculated)</div><div class="parcels-body"><div class="parcels-note"><p>The price table below is calculated based on your settings above. It shows you the cost to deliver a parcel from the pickup zone to different delivery zone. Please select a pickup zone to see the corresponding price.</p>
        <p><input type="checkbox" value="1" class="useregion"> Enable grouping of zones into region.</p>
        </div> <div class="pickup-search">Pickup from:   &nbsp;&nbsp;&nbsp; <span class="show-region">Region: <select name="state-pickup" class="form-select state-pickup">'.liveparcels_zonedata('stateoption').'</select>  </span>&nbsp;&nbsp;&nbsp;Zone name: <select name="zone-pickup" class="form-select zone-pickup">'.liveparcels_zonedata('zoneoption').'</select> </div><div class="pickup-result"><input type="hidden" class="path_page" value="ouser"><table><tr class="table-head"><th><a href="####" class="znumber">Zone number <input type="hidden" class="oid" value=""><img typeof="foaf:Image" src="/sites/all/modules/liveparcels/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th><th><a href="####" class="zname">Zone Name<input type="hidden" class="oname" value="asc"><img typeof="foaf:Image" src="/sites/all/modules/liveparcels/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th><th><a href="####" class="zstate">Region <input type="hidden" class="ostate" value=""><img typeof="foaf:Image" src="/sites/all/modules/liveparcels/resource/arrow-desc.png" class="hide" width="13" height="13" ></a></th>'.liveparcels_packagename('name').'</tr></table></div> '.(!empty($_SESSION['liveparcels_status']) && count($_SESSION['liveparcels_status'])>1 ? '<script> jQuery(\'.region-content\').before(\'<div id="console" class="clearfix"><div class="messages '.( $_SESSION['liveparcels_status']['status'] ? 'status':'error').'"><h2 class="element-invisible">'.( $_SESSION['liveparcels_status']['status'] ? 'Success':'Falise').' message</h2>'. $_SESSION['liveparcels_status']['message'].'</div></div>\');</script>':'')));
  unset($_SESSION['firrow']);
  unset($_SESSION['liveparcels_status']);
  $build['liveparcels'] = array(
      '#theme' => 'table',
      /*  Page heading disabled    */
      /*	 '#caption' => '<h2>' . t('Postage calculator Admin Settings') . '</h2>',*/
      '#rows' => $rows,
      '#attributes' => array('class' => array('live-parcels-status')),
      );
  drupal_add_js(drupal_get_path('module', 'liveparcels') . '/resource/liveparcels.js');
  drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/liveparcels.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));

  return $build;
}
function liveparcels_admin_message_form($form, &$form_state) {

  $form['liveparcels_info_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Welcome message'),
      '#description' => t('This message will be shown just below the heading of the quote and book page.'),
      '#default_value' => variable_get('liveparcels_info_message'),

      );
  $form['liveparcels_error_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Error message'),
      '#description' => t('This message will be shown whenever pricing is undefined and LiveParcels is unable to determine the price automatically.'),
      '#default_value' => variable_get('liveparcels_error_message'),

      );
  $form['liveparcels_note_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Bottom message'),
      '#description' => t('This message will be shown at the bottom of the quote and book page.'),
      '#default_value' => variable_get('liveparcels_note_message'),

      );
  $form['liveparcels_discount_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Discount Message'),
      '#description' => t('This message will be shown at the bottom of the quote and book page.'),
      '#default_value' => variable_get('liveparcels_discount_message'),

      );

  return system_settings_form($form);
}
