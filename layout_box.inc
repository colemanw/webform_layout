<?php

/**
 * @file
 * Webform module layout_box component.
 */

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_layout_box() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'extra' => array(
      'private' => FALSE,
      'equal' => FALSE,
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_layout_box($component) {
  $form = array();
  $form['display']['equal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Equal width fields'),
    '#default_value' => $component['extra']['equal'],
    '#description' => t('Gives fields in this container equal width.'),
    '#parents' => array('extra', 'equal'),
  );
  $form['extra']['description'] = array(); // Hide the description box.
  return $form;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_layout_box($component, $value = NULL, $filter = TRUE) {
  $element = array(
    '#weight' => $component['weight'],
    '#pre_render' => array('webform_layout_box_prerender'),
    '#webform_component' => $component,
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    '#attached' => array('css' => array(drupal_get_path('module', 'webform_layout') . '/layout_box.css')),
  );
  return $element;
}

/**
 * Pre-render function to set a layout_box ID and classes.
 */
function webform_layout_box_prerender($element) {
  $classes = array('webform-layout-box');
  if (!empty($element['#webform_component']['extra']['equal'])
  && ($n = count($element['#webform_component']['children'])) > 1) {
    $classes[] = 'equal-width-children';
    $classes[] = 'layout_box-child-width-' . $n;
  }
  else {
    $classes[] = 'variable-width-children';
  }
  $id = 'webform-component-' . str_replace('_', '-', implode('--', array_slice($element['#parents'], 1)));
  $element['#prefix'] = '<div id="' . $id . '" class="' . implode(' ', $classes) . '">';
  return $element;
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_layout_box($component, $value, $format = 'html') {
  if ($format == 'text') {
    $element = array(
      '#title' => $component['name'],
      '#weight' => $component['weight'],
      '#theme_wrappers' => array('webform_element_text'),
    );
  }
  else {
    $element = _webform_render_layout_box($component, $value);
  }

  $element['#webform_component'] = $component;
  $element['#format'] = $format;

  return $element;
}
