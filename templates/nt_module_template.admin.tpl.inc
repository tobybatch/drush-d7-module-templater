<?php

/**
 * @file
 * MODULE_NAME admin functions.
 */

/**
 * Implements hook_form().
 */
function MODULE_NAME_admin_form() {
    $form = array();

  $form['MODULE_NAME'] = array(
        '#type' => 'fieldset',
    '#title' => t('UCF_MODULE_NAME'),
  );

  $form['MODULE_NAME']['MODULE_NAME_vars'] = array(
        '#type' => 'textarea',
    '#title' => t('UCF_MODULE_NAME variables'),
        '#rows' => 20,
    '#description' => t('Arbitary variable to store for UCF_MODULE_NAME.'),
        '#default_value' => variable_get('MODULE_NAME_vars', ''),
    );

    $form['MODULE_NAME']['MODULE_NAME_submit'] = array(
        '#type' => 'submit',
    '#value' => 'Save Settings',
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function MODULE_NAME_admin_form_submit($form, &$form_state) {
    form_state_values_clean($form_state);
  $values = $form_state['values'];

  foreach ($values as $key => $val) {
    variable_set($key, $val);
  }

  $params = array(':names' => implode(', ', array_keys($values)));
  $msg = t('Saved settings: :names', $params);
  drupal_set_message($msg);
}
