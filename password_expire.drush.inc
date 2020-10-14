<?php
/**
 * Implements hook_drush_command().
 */
function password_expire_drush_command() {

  $commands['password-expire-reset-expired-passwords'] = array(
    'description' => 'Drush command to reset expired passwords to a random string',
    'callback' => 'drush_password_expire_reset_expired_passwords',
    'aliases' => array(),
    'arguments' => array(),
    'options' => array(
      'only-user-uid' => 'Process only the specified user ID: Useful for debugging'
    ),
    'examples' => array(
      'drush password-expire-reset-expired-passwords' => 'Executes the password expiration job which resets expired passwords to a random string.'
    ),
  );

  return $commands;
}

/**
 * Drush command logic.
 * drush_[COMMAND_NAME]().
 */
function drush_password_expire_reset_expired_passwords(){
  _password_expire_handle_expired_passwords();
}
?>