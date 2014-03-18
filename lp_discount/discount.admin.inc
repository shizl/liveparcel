<?php
function discount_settings($form,$form_state) {
  $form['removed'] = array(
      '#title' => t('Shoe size'),
      '#type' => 'item',
      '#description' => t('This question has been removed because the law prohibits us from asking your shoe size.'),
      );
  $form['default'] = array(
      '#type'=>'fieldset',
      '#title' =>'Default Discount',
      '#description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus blandit felis eros, sit amet dignissim velit sodales non. Nulla congue ipsum eget pellentesque eleifend',
      '#collapsible' => TRUE,
      );
  $form['default']['default_setting'] = array(
      '#type' => 'textfield',
      '#required' => TRUE,
      '#title' =>'Discount Default Setting',
      '#default_value' =>discount_default_rate(),
      );

  $form['roles'] = array(
      '#type'=>'fieldset',
      '#title' =>'Roles Discount',
      '#description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus blandit felis eros, sit amet dignissim velit sodales non. Nulla congue ipsum eget pellentesque eleifend',
      '#collapsible' => TRUE,
      );
  foreach(user_roles() as $tid => $roles){
    $form['roles']['roles_rate['.$tid.']'] = array(
        '#type' => 'textfield',
        '#title' =>$roles,
        '#required' => TRUE,
        '#default_value' =>discount_roles_rate($tid),
        );
  }

  $form['user'] = array(
      '#type'=>'fieldset',
      '#title' =>'User Discount',
      '#description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus blandit felis eros, sit amet dignissim velit sodales non. Nulla congue ipsum eget pellentesque eleifend',
      '#collapsible' => TRUE,
      );

  $form['user']['user_wrapper'] = array(

      '#prefix' => '<div id="user-wrapper">',
      '#suffix' => '</div>',
      '#theme'=>'user_wrapper',
      );

  $query = db_select('live_parcel_discount','tid');
  $query
    ->condition('type','user')
    ->fields('tid',array('tid'));
  $result = $query->execute();
  foreach($result as $row) {
    $form['user']['user_wrapper']['user_rate['.$row->tid.']'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' =>(user_load($row->tid)->name).' Discount Setting',
        '#default_value' =>discount_user_rate($row->tid),
        );
  }

  $form['add'] = array(
      '#title' =>'Add User Discount',
      '#description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus blandit felis eros, sit amet dignissim velit sodales non. Nulla congue ipsum eget pellentesque eleifend',
      '#type'=>'fieldset',
      );
  $form['add']['add_more_user'] = array(
      '#type' => 'textfield',
      '#title' =>'User',
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => '',
      );
  $form['add']['add_more_rate'] = array(
      '#type' => 'textfield',
      '#title' =>'Discount Rate',
      '#default_value' => '',
      );
  $form['add']['add_more_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Add User'),
      '#ajax' => array(
        'callback' => 'discount_add_more',
        'wrapper' => 'user-wrapper',
        'method' => 'replace',
        ),

      );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      '#submit' => array('discount_admin_settings_submit'),
      );

  return $form;
}

function discount_admin_settings_submit($form,&$form_state){
  $table = 'live_parcel_discount';
  $record = new stdClass();

  $default = $form['default'];
  $rate = $default['default_setting']['#value'];

  $id = db_query("SELECT id FROM {live_parcel_discount} WHERE type = :type AND tid=:tid", array(':type' => 'default', ':tid' => 0))->fetchField();
  if($id){
    db_update($table)
      ->expression('rate',$rate)
      ->condition('type','default')
      ->condition('tid',0)
      ->execute();
  }else{
    db_insert($table)
      ->fields(array(
            'id' => NULL,
            'type' => 'default',
            'rate' => $rate,
            'tid' => 0,
            ))
      ->execute();
  }

  $roles = $form['roles'];
  foreach($_POST['roles_rate'] as $tid => $rate){
    $id = db_query("SELECT id FROM {live_parcel_discount} WHERE type = :type AND tid=:tid", array(':type' => 'roles', ':tid' => $tid))->fetchField();
    if($id){
      db_update($table)
        ->expression('rate',$rate)
        ->condition('type','roles')
        ->condition('tid',$tid)
        ->execute();
    }else{
      db_insert($table)
        ->fields(array(
              'id' => NULL,
              'type' => 'roles',
              'rate' => $rate,
              'tid' => $tid,
              ))
        ->execute();
    }
  }

  $user = $form['user'];
  foreach($_POST['user_rate'] as $tid => $rate){
    $id = db_query("SELECT id FROM {live_parcel_discount} WHERE type = :type AND tid=:tid", array(':type' => 'user', ':tid' => $tid))->fetchField();
    if($id){
      db_update($table)
        ->expression('rate',$rate)
        ->condition('type','user')
        ->condition('tid',$tid)
        ->execute();
    }else{
      db_insert($table)
        ->fields(array(
              'id' => NULL,
              'type' => 'user',
              'rate' => $rate,
              'tid' => $tid,
              ))
        ->execute();
    }
  }
  //drupal_set_message('<pre>'.print_r($default,TRUE).'</pre>');
  drupal_set_message(t('Save Ok'));
}



function discount_add_more($form,$form_state){

if($form_state['values']['add_more_user'] == '' || $form_state['values']['add_more_rate'] == ''){
  drupal_set_message(t('User OR Rate NULL'),'error');

  return $form['user']['user_wrapper'];

}else{



  $table = 'live_parcel_discount';

  $name = $form['add']['add_more_user']['#value'];
  $rate = $form['add']['add_more_rate']['#value'];
  $user = user_load_by_name($name);

  $id = db_query("SELECT id FROM {live_parcel_discount} WHERE type = :type AND tid=:tid", array(':type' => 'user', ':tid' => $user->uid))->fetchField();
  if($id){
    db_update($table)
      ->expression('rate',$rate)
      ->condition('type','user')
      ->condition('tid',$user->uid)
      ->execute();
  }else{
    db_insert($table)
      ->fields(array(
            'id' => NULL,
            'type' => 'user',
            'rate' => $rate,
            'tid' => $user->uid,
            ))
      ->execute();
  }

  //drupal_set_message('<pre>'. print_r($form['user'], TRUE) .'</pre>');

  $query = db_select('live_parcel_discount','tid');
  $query
    ->condition('type','user')
    ->fields('tid',array('tid'));
  $result = $query->execute();

  foreach($result as $row) {
    $form['user']['user_wrapper']['user_rate['.$row->tid.']'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' =>(user_load($row->tid)->name).' Discount Setting',
        '#value' =>discount_user_rate($row->tid),
        );
  }
  //  print_r($form['user']['user_wrapper']);
  drupal_set_message(t('Add User OR Update Ok'));

  return $form['user']['user_wrapper'];
  }
}

