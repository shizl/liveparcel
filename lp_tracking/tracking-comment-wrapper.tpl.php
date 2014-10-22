<div id="comments" class="<?php print $classes; ?>"<?php print $attributes; ?>>
<table>
<thead><tr><th>Date</th><th>Author</th><th>Driver</th><th>GPS</th><th>Status</th><th>Starred</th><th>Comments</th></tr></thead>
<?php print render($content['comments']); ?>
</table>
<?php if ($content['comment_form']): ?>
<h2 class="title comment-form"><?php print t('Add new Update'); ?></h2>
<?php print render($content['comment_form']); ?>
<?php endif; ?>
</div> 

