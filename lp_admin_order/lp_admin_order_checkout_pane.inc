<?php

function theme_lp_admin_order_table($variables){
     $parcels = $variables['items'];
  // Set up table header.
  $header = array(
    array('data' => t('Products'), 'class' => array('products')),
    array('data' =>t('Dimension'), 'class' => array('price')),
    array('data' =>t('Weight'), 'class' => array('price')),
    array('data' =>t('Price'), 'class' => array('price')),
  );

  // Set up table rows.
  foreach ($parcels['parcels'] as $key=>$parcel ) {
    $rows[] = array(
      array('data' => $parcel['parcelnum'], 'class' => array('products')),
      array('data' => $parcel['dimfirst'].'x'.$parcel['dimsecond'].'x'.$parcel['dimthree'].' cm','class' => array('price')),
      array('data' => $parcel['weighttext'].' kg','class' => array('price')),
      array('data' => '<input id="parcel_price_'.$key.'" type="text" size="5" maxlenght="10" value="'.str_replace(variable_get('uc_currency_sign','$'),'',$parcel['price']).'" >','class' => array('price')),
    );
  }

  // Add the subtotal as the final row.
  $rows[] = array(
    'data' => array(
      // One cell
      array(
        'data' => array(
          '#theme' => 'uc_price',
          '#prefix' => '<span id="subtotal-title">' . t('Parcels price:') . '</span> ',
          '#price' => $parcels['totals'],
        ),
        // Cell attributes
        'colspan' => 4,
        'class' => array('subtotal'),
      ),
    ),
    // Row attributes
    'class' => array('subtotal'),
  );
  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('cart-review'))));
}



