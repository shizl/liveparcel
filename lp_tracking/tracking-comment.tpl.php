<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

<tr>
<td><?php print $created; ?></td>
<td><?php print $author; ?></td>
<td>
<?php 
   $driver = empty($content['field_driver_assigned'])?'':render($content['field_driver_assigned']);
   print $driver;	
?>
</td>
<td style="width:150px;">
<?php 
  $gps= empty($content['field_gps'])?'':render($content['field_gps']);
  print $gps;
 ?>
</td>

<td>
<?php 
  $status = empty($content['field_status'])?'':render($content['field_status']);
  print $status;
 ?>
</td>

<td>
<?php 
  $starred = empty($content['field_starred'])?'':render($content['field_starred']);
  print $starred;
 ?>
</td>
<td><?php print $title; ?></td>
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
