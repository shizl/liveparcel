<?php

/**
 * @file
 * Store front page menu items.
 */
 
/**
 * Menu callback which provides the store administration overview page.
 */
function liveparcels_packageshow() {
	$rows['package'] = array(array('data' => '<div class="parcels-title">Define package maximum values and price</div><div class="parcels-body"><div class="parcels-note"><p>To calculate the parcel price, we use either the Dimensional Weight or the Actual Weight, whichever is the greater of the two values.</p>
<p>For more information, visit <a href="http://en.wikipedia.org/wiki/Dimensional_weight">http://en.wikipedia.org/wiki/Dimensional_weight</a></p>
<p>Dimensional weight = (L cm x W cm x H cm) x Dimensional Factor</p></div> <div class="parcels-factor">Dimensional Factor: <input type="text" class="small-text" value="'.variable_get('liveparcels_factor').'" id="factor"> &nbsp;&nbsp;<input type="button" value="update" class="form-submit" id="update-factor"></div>
<div class="package-table"><ul class="packagedata">
<li id="phead"><div class="field-small">Position</div><div class="field">Package Name</div><div class="field">Dead Weight (kg)</div><div class="field">Dimensional Weight (kg)</div><div class="field-small">Length (cm)</div><div class="field-small">Price ($)</div><div class="field">Edit/Delete</div></li>
<li class="package-line" id="n0"><div class="field-small"><input type="hidden" class="oldposition small-text" value="0"><input type="text" class="position small-text" size="4"></div><div class="field"><input type="text" class="package_name small-text"></div><div class="field"><input type="text" class="dead_weight small-text"></div><div class="field"><input type="text" class="dimen_weight small-text"></div><div class="field-small"><input type="text" class="plength small-text"></div><div class="field-small"><input type="text" class="pprice small-text"></div><div class="field"><a href="####" onclick="savenote(0,\'updateposition\')">Save</a></div></li></ul></div></div>'));
	$build['liveparcels'] = array(
	'#theme' => 'table',
	 '#caption' => '<h2>' . t('Postage calculator Admin Settings') . '</h2>',
	  '#rows' => $rows,
	  '#attributes' => array('class' => array('live-parcels-status')),
	);
drupal_add_js(drupal_get_path('module', 'liveparcels') . '/resource/liveparcels.js');
	 drupal_add_css(drupal_get_path('module', 'liveparcels') . '/resource/liveparcels.css', array('group' => CSS_DEFAULT, 'every_page' => TRUE));
	 
  return $build;
}
