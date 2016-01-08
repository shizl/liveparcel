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

<?php if(!empty($comment)):  ?>

<tr>

<?php 
   $driver = empty($content['field_created'])?'':render($content['field_created']);
 if($node->uid == $user->uid ||in_array(3,$arr)||in_array('driver',$arrname)){
   print '<td>'.$created.'</td>';	
 }
?>

<td><?php print $customDate; ?></td>
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

  $starred_value = !empty($content['field_starred'])?$content['field_starred']['#object']->field_starred['und'][0]['value']:'';

  $starred = empty($content['field_starred']) ?'':render($content['field_starred']);

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
<?php endif ;?>