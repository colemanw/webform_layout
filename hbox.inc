<?php

/**
 * @file
 * Webform module hbox component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_hbox() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'extra' => array(
      'equal' => FALSE,
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_hbox($component) {
  $form = array();
  $form['display']['markup'] = array(
    '#markup' => t('Please care about the child elements width.'),
  );
  $form['display']['equal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Equal width children'),
    '#default_value' => $component['extra']['equal'],
    '#description' => t('Let children elements have equal width.'),
    '#parents' => array('extra', 'equal'),
  );
  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_hbox($component, $value = NULL, $filter = TRUE) {
  $element = array(
    '#type' => 'fieldset',
    '#title' => NULL,
    '#weight' => $component['weight'],
    '#description' => NULL,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('webform-component-fieldset', 'webform-container-hbox'), 'id' => 'webform-component-' . $component['form_key']),
    '#pre_render' => array('webform_hbox_prerender'),
    '#webform_component' => $component,
    '#attached' => array('css' => array( drupal_get_path('module', 'webform_hbox') . '/webform_hbox.css')),
  );
  return $element;
}

/**
 * Pre-render function to set a hbox ID.
 */
function webform_hbox_prerender($element) {
  if ($element['#webform_component']['extra']['equal'] and ($n = count($element['#webform_component']['children'])) > 1) {
    $element['#attributes']['class'][] = 'webform-container-hbox-equal' . $n;
  }
  $element['#attributes']['id'] = 'webform-component-' . str_replace('_', '-', implode('--', array_slice($element['#parents'], 1)));

  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_hbox($component, $value, $format = 'html') {
  if ($format == 'text') {
    $element = array(
      '#title' => $component['name'],
      '#weight' => $component['weight'],
      '#theme_wrappers' => array('webform_element_text'),
    );
  }
  else {
    $element = _webform_render_hbox($component, $value);
  }

  $element['#webform_component'] = $component;
  $element['#format'] = $format;

  return $element;
}
