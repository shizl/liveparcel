<?php
function lp_discount_settings($form,$form_state) {
  $form['removed'] = array(
      '#title' => t('Shoe size'),
      '#type' => 'item',
      '#description' => t('This question has been removed because the law prohibits us from asking your shoe size.'),
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
        '#default_value' =>lp_discount_roles_rate($tid),
        );
  }

  $form['user'] = array(
      '#type'=>'fieldset',
      '#title' =>'User Discount',
      '#description' => 'If delete user discount please input 0',
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
        '#title' =>(user_load($row->tid)->name),
        '#default_value' =>lp_discount_user_rate($row->tid),
        );
  }
  $form['user']['add'] = array(
      '#title' =>'Add User Discount',
      '#description' => 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus blandit felis eros, sit amet dignissim velit sodales non. Nulla congue ipsum eget pellentesque eleifend',
      '#type'=>'fieldset',
      );
  $form['user']['add']['add_more_user'] = array(
      '#type' => 'textfield',
      '#title' =>'User',
      '#autocomplete_path' => 'user/autocomplete',
      '#default_value' => '',
      );
  $form['user']['add']['add_more_rate'] = array(
      '#type' => 'textfield',
      '#title' =>'Discount Rate',
      '#default_value' => '',
      );
  $form['user']['add']['add_more_submit'] = array(
      '#type' => 'button',
      '#value' => t('Add User'),
      '#validate' => array('lp_discount_add_more_validate'),
      '#ajax' => array(
        'callback' => 'lp_discount_add_more',
        'wrapper' => 'user-wrapper',
        'method' => 'replace',
        ),
      );

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
      );
  return $form;
}
function lp_discount_settings_validate($form,&$form_state) {
  $input = $form_state['input']['roles_rate'];
  foreach($input as $id => $rate ){
    if(!is_numeric($rate)){
      form_set_error('roles_rate['.$id.']',t('Please input number'));
    }
  }
  if(isset($form_state['input']['user_rate'])){
    $input = $form_state['input']['user_rate'];
    foreach($input as $id => $rate ){
      if(!is_numeric($rate)){
        form_set_error('user_rate['.$id.']',t('Please input number'));
      }
    }
  }
}
function lp_discount_settings_submit($form,&$form_state) {
  $table = 'live_parcel_discount';
  $record = new stdClass();

  $roles = $form_state['input']['roles_rate'];
  foreach($roles as $tid => $rate){
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
  if(isset($form_state['input']['user_rate'])){
    $user = $form_state['input']['user_rate'];
    if(isset($_POST['user_rate'])){
      foreach($user as $tid => $rate){
        $id = db_query("SELECT id FROM {live_parcel_discount} WHERE type = :type AND tid=:tid", array(':type' => 'user', ':tid' => $tid))->fetchField();
        if(!$rate){
          db_delete($table)
            ->condition('type','user')
            ->condition('tid',$tid)
            ->execute();
        }else{
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
      }
    }
  }
  //  drupal_set_message('<pre>'.print_r($user,TRUE).'</pre>');
  drupal_set_message(t('Save Ok'));
}

function lp_discount_add_more_validate($form,&$form_state) {

  if($form_state['input']['add_more_user'] == '' || $form_state['input']['add_more_rate'] == ''){
  form_set_error('add_more_rate',t('asdfasdf'));
  }
  //print_r($form_state);
  //exit();

}

function lp_discount_add_more($form,$form_state){
  if($form_state['values']['add_more_user'] == '' || $form_state['values']['add_more_rate'] == ''){
    drupal_set_message(t('User OR Rate NULL'),'error');

    return $form['user']['user_wrapper'];

  }else{
    $table = 'live_parcel_discount';
    $name = $form['user']['add']['add_more_user']['#value'];
    $rate = $form['user']['add']['add_more_rate']['#value'];
    $user = user_load_by_name($name);
    if(!$user){
      drupal_set_message(t('User name not sure'),'error');
      return $form['user']['user_wrapper'];
    }
    if(!is_numeric($rate)){
      drupal_set_message(t('Please input number'),'error');
      return $form['user']['user_wrapper'];
    }

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
          '#value' =>lp_discount_user_rate($row->tid),
          );
    }
    drupal_set_message(t('Add User OR Update Ok'));
    return $form['user']['user_wrapper'];
  }
}

