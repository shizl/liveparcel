<?php

/**
 * @file
 * Store front page menu items.
 */

function lp_parcel_getPackageprice($max,$dimenstext,$weighttext) {

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
