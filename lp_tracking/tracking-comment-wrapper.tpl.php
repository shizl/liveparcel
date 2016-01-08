<div id="comments" class="<?php print $classes; ?>"<?php print $attributes; ?>>
<?php

global $user;

  $arr = array();
  $arrname = array(); 
  $roles = db_query('select rid from {users_roles} where uid = '.$user->uid);
  foreach($roles as $role){
  $arr[] = $role->rid;
  $rname = db_query('select name from {role} where rid='.$role->rid)->fetchfield();
  $arrname[] = $rname;		
  }

?>

<?php if($content['comments']): ?>

<table>

<thead>
<tr>

<?php
if($node->uid == $user->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
echo '<th>Upload date/time</th>';
}
?>

<th>Transaction date/time</th>
<th>Author</th>

<?php
if($node->uid == $user->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
echo '<th>Driver</th>';
}
?>

<?php
if($user->uid!=0 ||in_array(3,$arr)||in_array('driver',$arrname)){
echo '<th>Location</th>';
}
?>

<th>Status</th>
<?php 
//if(in_array(3,$arr)||in_array('driver',$arrname)){
//echo '<th>Starred</th>';
//}
?>
<?php
if($node->uid == $user->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
echo '<th>Comments</th>';
}
?>
</tr>
</thead>

<?php print render($content['comments']); ?>
</table>
<?php endif; ?>

<?php if ($content['comment_form']): ?>
<h2 class="title comment-form"><?php print t('Add new update'); ?></h2>
<?php print render($content['comment_form']); ?>
<?php endif; ?>
</div>