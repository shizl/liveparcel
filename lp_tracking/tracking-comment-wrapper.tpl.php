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
<table>

<thead>
<tr>
<th>Date</th>
<th>Author</th>
<th>Driver</th>
<th>Location</th>
<th>Status</th>
<?php 
if(in_array(3,$arr)||in_array('driver',$arrname)){
echo '<th>Starred</th>';
}
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
<?php if ($content['comment_form']): ?>
<h2 class="title comment-form"><?php print t('Add new update'); ?></h2>
<?php print render($content['comment_form']); ?>
<?php endif; ?>
</div>