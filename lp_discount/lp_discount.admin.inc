<?php
function lp_discount_settings($form,$form_state) {
  $form['removed'] = array(
      '#title' => t(''),
      '#type' => 'item',
      '#description' => t('You may configure discount by role or user. Enter 0 for no discount, 0.1 for 10% discount, 0.3 for 30% discount, 1 for free service, i.e. 100% discount, etc.'),
      );

  $form['roles'] = array(
      '#type'=>'fieldset',
      '#title' =>'Discount by role',
      '#description' => 'Discount entered here will be applied to all users who belong to that role.',
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
      '#title' =>'Discount by user',
      '#description' => 'User based discount supersedes role based discount even if the role based discount is larger. To delete user discount, input 0.',
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
      '#description' => 'Type the user name you want to apply a discount, enter the discount rate and then click Add User.',
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
      '#title' =>'Discount rate',
      '#default_value' => '',
      );
  $form['user']['add']['add_more_submit'] = array(
      '#type' => 'button',
      '#value' => t('Add User'),
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
  drupal_set_message(t('Settings saved'));
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
          '#title' =>(user_load($row->tid)->name).' discount rate',
          '#value' =>lp_discount_user_rate($row->tid),
          );
    }
    drupal_set_message(t('Discount added/updated'));
    return $form['user']['user_wrapper'];
  }
}