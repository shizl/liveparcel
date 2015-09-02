<?php 


function lp_feature_service_settings($form,&$form_state){

$form['#attached']['css'] = array(
  drupal_get_path('module', 'lp_feature_service') . '/css.css',
);

$form['#attached']['js'] = array(
  drupal_get_path('module', 'lp_feature_service') . '/js.js',
);

 $form['optional_fees'] = array(
   '#markup'=>t('<h2>Optional Fees</h2><div class="description">help text.</div>'),
 );



  $form['current_fees'] = array(
      '#type'=>'fieldset',
      '#title' =>'Current fees',
      '#description' => 'help text.',
      '#collapsible' => TRUE,
      );
 $form['current_fees']['label'] = array(
   '#markup'=>'<div class="label"><label class="desc">description</label> <label class="val">value</label><label>action</label></div>',
  );


 $form['current_fees']['current_fee'] = array(
      '#prefix' => '<div id="current-wrapper">',
      '#suffix' => '</div>',
 );



 $result =  db_query('select * from {live_parcel_feature_service}');

 foreach($result as $row){
$form['current_fees']['current_fee']['rows-'.$row->id] = array(
      '#prefix' => '<div class="rows-wrapper">',
      '#suffix' => '</div>',
);
 $form['current_fees']['current_fee']['rows-'.$row->id]['title-'.$row->id] = array(
   '#type'=>'textfield',
   '#maxlength'=>128,
   '#size'=>25,
   '#default_value'=>$row->type,
 );
 $form['current_fees']['current_fee']['rows-'.$row->id]['value-'.$row->id] = array(
   '#type'=>'textfield',
   '#maxlength'=>10,
   '#size'=>10,
   '#default_value'=>$row->value,
 );
 $form['current_fees']['current_fee']['rows-'.$row->id]['del-'.$row->id] = array(
   '#markup'=>'<a class="del" data-id ="'.$row->id.'" href="javascript:">Delete</a>',
 );
   
 }

$form['current_fees']['current_fee']['rows'] = array(
      '#prefix' => '<div class="rows-wrapper">',
      '#suffix' => '</div>',
);

 $form['current_fees']['current_fee']['rows']['title'] = array(
   '#type'=>'textfield',
   '#maxlength'=>128,
   '#size'=>25,

 );
 $form['current_fees']['current_fee']['rows']['value'] = array(
   '#type'=>'textfield',
   '#maxlength'=>10,
   '#size'=>10,
 );


$form['actions'] = array('#type'=>'actions');
$form['actions']['submit'] = array(
 '#type'=>'submit',
 '#value'=>t('Update'),
);

  return $form;


}


function lp_feature_service_settings_submit(&$form,&$form_state){

  $title = $form_state['values']['title'];
  $value = $form_state['values']['value']; 

  if($title!=null && $value !=null){
	db_insert('live_parcel_feature_service')
        ->fields(array(
              'type' => $title,
              'value' => $value,
              ))
        ->execute();
  }

  $result = db_query('select * from {live_parcel_feature_service} ');

   foreach($result as $row){

	if(!empty($form_state['values']['title-'.$row->id]) && $form_state['values']['value-'.$row->id]){
	db_update('live_parcel_feature_service') 
	  ->fields(array(

	    'type' => $form_state['values']['title-'.$row->id],
	    'value' => $form_state['values']['value-'.$row->id],
	  ))
	  ->condition('id', $row->id , '=')
	  ->execute();	

        }
   }
  

}


