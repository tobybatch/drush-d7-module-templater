<?php

/**
 * Implements hook_drush_command().
 */
function nt_module_template_drush_command() {
  $items['nt-module-template'] = array(
    'description' => 'Create an empty drupal 7 module.',
    'aliases' => array('ntmt'),
    'examples' => array(
      'drush nt-module-template site/all/modules/custom/modulename' => 'Create a module called modulename in the folder site/all/modules/custom',
    ),
    'arguments' => array(
      'path' => 'The path to the new module.',
    ),
    'options' => array(
      'package' => 'The name of the package to create.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_NONE,
  );

  return $items;
}


/**
 *
 * @param string $path
 *   Path to the new module.
 */
function drush_nt_module_template($path) {
  $module_name = basename($path);
  $module_path = $path;
  $parent_path = dirname($module_path);

  $package_name = drush_get_option('package', 'Other');

  if (!is_dir($parent_path)) {
    drush_print('Parent path (@parent) does not exist.  Will not continue.', array('@parent' => $parent_path));
    exit(1);
  }

  if (!is_dir($module_path)) {
    drush_print('Creating module folder at ' . $module_path);
    mkdir($module_path, 0755);
  }

  $module = drush_nt_module_template_parse(__DIR__ . '/templates/nt_module_template.tpl.module', $module_name, $package_name);
  $info = drush_nt_module_template_parse(__DIR__ . '/templates/nt_module_template.tpl.info', $module_name, $package_name);
  $admin = drush_nt_module_template_parse(__DIR__ . '/templates/nt_module_template.admin.tpl.inc', $module_name, $package_name);
  $install = drush_nt_module_template_parse(__DIR__ . '/templates/nt_module_template.tpl.install', $module_name, $package_name);

  $file_module = $module_path . '/' . $module_name . '.module';
  $file_info = $module_path . '/' . $module_name . '.info';
  $file_admin = $module_path . '/' . $module_name . '.admin.inc';
  $file_install = $module_path . '/' . $module_name . '.install';

  file_put_contents($file_module, $module);
  drush_print('Created ' . $file_module);

  file_put_contents($file_info, $info);
  drush_print('Created ' . $file_info);

  file_put_contents($file_admin, $admin);
  drush_print('Created ' . $file_admin);

  file_put_contents($file_install, $install);
  drush_print('Created ' . $file_install);
}

function drush_nt_module_template_parse($file, $module, $package) {
  $ucf = ucfirst(str_replace('_', ' ', $module));
  $contents = file_get_contents($file);
  $parsed = str_replace(
      'MODULE_NAME', $module, str_replace(
          'UCF_MODULE_NAME', $ucf, str_replace(
              'PACKAGE_NAME', $package, $contents
          )
      )
  );
  return $parsed;
}
