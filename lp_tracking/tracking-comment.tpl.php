<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
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
<tr>
<td><?php print $created; ?></td>
<td><?php print $author; ?></td>

<?php 
   $driver = empty($content['field_driver_assigned'])?'':render($content['field_driver_assigned']);
 if($node->uid == $user->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
   print '<td>'.$driver.'</td>';	
 }
?>


<?php 
  $gps= empty($content['field_gps'])?'':render($content['field_gps']);
if($user->uid!=0 ||in_array(3,$arr)||in_array('driver',$arrname)){
  print '<td style="width:200px;">'.$gps .'</td>';
}

?>

<td>
<?php 
  $status = empty($content['field_status'])?'':render($content['field_status']);
  print $status;
 ?>
</td>


<?php 
//  $starred = empty($content['field_starred'])?'':render($content['field_starred']);

//if(in_array(3,$arr)||in_array('driver',$arrname)){
//  print '<td>'.$starred .'</td>';
// }

 ?>

<style>
 .subject a{
 color:red !important;
 font-weight: bold;
}
</style> 
<?php  

  $starred_value = !empty($content['field_starred'])?$content['field_starred']['#object']->field_starred['und'][0]['value']:'';

if($user->uid == $node->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
 print $starred_value=='' || $starred_value=='0'?'<td>'.$title.'</td>':'<td class="subject">'.$title.'</td>';
 }
?> 

<?php  
//if($user->uid == $node->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
// print '<td>'.$title.'</td>'; 
// }
?>
</tr>

<?php if(!empty($content['field_photo'])): ?>
<tr>
<td colspan="7">
<?php print render($content['field_photo']);?>
</td>
</tr>
<?php endif ;?>
<tr>
<td colspan="7">
<?php print render($content['links']); ?>
</td>
</tr>
<!--
<div class="attribution">

<div class="submitted">
<p class="commenter-name">
<?php print $author; ?>
</p>
<p class="comment-time">
<?php print $created; ?>
</p>

</div>
</div>
<div class="comment-text">


<?php print render($title_prefix); ?>
<h3<?php print $title_attributes; ?>><?php print $title; ?></h3>
<?php print render($title_suffix); ?>
<div class="content"<?php print $content_attributes; ?>>
<?php
// We hide the comments and links now so that we can render them later.
hide($content['links']);

print render($content);
?>

</div> 
<?php print render($content['links']); ?>
</div> 
-->
</div>