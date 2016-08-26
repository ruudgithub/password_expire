<?php
/**
 * Configuration page for password_expire
 */
function password_expire_admin_settings($form, &$form_state) {
  global $PASSWORD_EXPIRE_DEFAULT_POLICY;
  
  $tokens = password_expire_token_info();

  $token_list = "";
  if (isset($tokens['tokens']['password_expire'])) {
    foreach($tokens['tokens']['password_expire'] as $key => $value) {
      if(isset($key) && isset($value['description'])) {
        $token_list[$key] = $value['description']; 
      }
    }
  }

  $headers = array(
    array('data'=>'Token', 'field'=>'Token'),
    array('data'=>'Description', 'field'=>'Description'),
  );

  $rows = array();
  foreach ($token_list as $key => $value) {
    $rows[] = array('field' => $key, 'data' => $value);
  }

  $table_data = array(
    'title' => array(
      'data' => array(
        'header'     => $headers,
        'rows'       => $rows,
        'sticky'     => TRUE,
        'empty'      => 'No results found',
        'attributes' => array(),
        'caption'    => count($rows) . ' rows',
        'colgroups'  => array()
   		),
    ),
  );

  $form['password_expire'] = array(
    '#type' => 'vertical_tabs',
    '#title' => t('Password Expire Settings'),
  );

  $form['password_expire_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Expire Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => '',
    '#group' => 'password_expire',
  );
  $form['password_expire_settings']['password_expire_renewalrequired'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require user to request a new password if password is expired'),
    '#default_value' => variable_get('password_expire_renewalrequired', NULL),
    '#description' => t('If this option is checked, a user should request a new password after his/her password is expired. This will prevent that a password is active for a longer period then the expiry period.'),
  );
  $form['password_expire_settings']['password_expire_passwordchangedurl'] = array(
    '#type' => 'textfield',
    '#title' => t('Page Redirect URL'),
    '#default_value' => variable_get('password_expire_passwordchangedurl', NULL),
    '#description' => t('Enter the URL to redirect to after a password has been changed successfully. <br />By default (or when empty) a drupal message will be displayed that the password has been changed successfully.'),
  );
  
  $form['password_expire_roles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Expire Roles'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => '',
    '#group' => 'password_expire',
  );
  
  $userroles = user_roles(TRUE);
  if(isset($userroles[DRUPAL_ANONYMOUS_RID])) {
    unset($userroles[DRUPAL_ANONYMOUS_RID]);
  }
  if(isset($userroles[DRUPAL_AUTHENTICATED_RID])) {
    unset($userroles[DRUPAL_AUTHENTICATED_RID]);
  }
    
  $form['password_expire_roles']['password_expire_userroles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#default_value' => variable_get('password_expire_userroles', array()),
    '#description' => t('Check which roles should change their password after the specified period.'),
    '#options' => (is_array($userroles) ? $userroles : array()),  
  );

  $form['password_expire_policy'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Expire Password Policy'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => '',
    '#group' => 'password_expire',
  );
  
  $form['password_expire_policy']['password_expire_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Password Expiry Length'),
    '#default_value' => variable_get('password_expire_length', NULL),
    '#description' => t('Enter the period before a password will expire (e.g. +1week, +3months). If blank, passwords never expire.'),
  );
  $form['password_expire_policy']['password_expire_warning'] = array(
    '#type' => 'textfield',
    '#title' => t('Warning period'),
    '#default_value' => variable_get('password_expire_warning', '+1week'),
    '#description' => t('The period of time a user is warned before their password expires (e.g. +1week, +3months).'),
  );
  
  //For anyone's security force a password of at least DEFAULT_PASSWORD_LENGTH characters
  $ar_passLength = array_combine(range(DEFAULT_PASSWORD_LENGTH,100),range(DEFAULT_PASSWORD_LENGTH,100));
  $form['password_expire_policy']['password_expire_policy_password_length'] = array(
    '#type' => 'select',
    '#title' => t('Select the minimum password length'),
    '#default_value' => variable_get('password_expire_policy_password_length', array(DEFAULT_PASSWORD_LENGTH)),
    '#description' => t('Select the password policy requirements. If none of the options are selected, the default drupal behaviour will apply.'),
    '#options' => ((isset($ar_passLength) && is_array($ar_passLength)) ? $ar_passLength : array(DEFAULT_PASSWORD_LENGTH)),
  );
  
  $form['password_expire_policy']['password_expire_policy'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Define the password policy requirements'),
    '#default_value' => empty(variable_get('password_expire_policy')) ? array_keys($PASSWORD_EXPIRE_DEFAULT_POLICY) : variable_get('password_expire_policy'),
    '#description' => t('Select the password policy requirements. If none of the options are selected, the default drupal behaviour will apply.'),
    '#options' => array('lowercase' => 'Lowercase (a-z)', 'uppercase' => 'Uppercase (A-Z)', 'numbers' => 'Numbers (0-9)', 'special' => 'Special (anything not alphanumeric f.e. !@#$%^&*()-+<>/?...)', 'diff_than_username' => 'Different than username'),
  );
  
  $form['password_expire_messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Expire Site Messages'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => '',
    '#group' => 'password_expire',
  );

  $form['password_expire_messages']['password_expire_warning_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Warning message'),
    '#description' => t('The message that will be displayed upon login to the user if their password is in the warning period. Leave blank for no message.'),
    '#default_value' => variable_get('password_expire_warning_message', 'Your password will expire in [password_expire:pass-expire-days-left] day(s).'),
    '#rows' => 2,
  );
  $form['password_expire_messages']['password_expire_repeat_warning_message'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat warning'),
    '#description' => t('If this is not checked the message will only be displayed once, when the user logs on to the site.'),
    '#default_value' => variable_get('password_expire_repeat_warning_message', FALSE),
  );
  $form['password_expire_messages']['password_expire_expired_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Expired message'),
    '#description' => t('The message that will be displayed upon login to the user if their password is expired. Leave blank for no message.'),
    '#default_value' => variable_get('password_expire_expired_message', 'Your password is expired. Please change your password. Be sure to use a different password as before.'),
    '#rows' => 2,
  );
  $form['password_expire_messages']['password_expire_passwordsame_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Password should be different message'),
    '#description' => t('The message that will be displayed when a user tries to change his/her password and the password is the same as before.'),
    '#default_value' => variable_get('password_expire_passwordsame_message', 'Please choose a password that you haven\'t used before.'),
    '#rows' => 2,
  );
  $form['password_expire_messages']['password_expire_successful_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Password changed successfully message'),
    '#description' => t('The message that will be displayed when a user has changed his/her password successfully.'),
    '#default_value' => variable_get('password_expire_successful_message', 'Your password has been changed successfully.'),
    '#rows' => 2,
  );
  $form['password_expire_messages']['password_expire_error_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Error message'),
    '#description' => t('The message that will be displayed when a password could not be changed successfully.'),
    '#default_value' => variable_get('password_expire_error_message', 'Unable to set password, please contact your site administrator.'),
    '#rows' => 2,
  );

  $form['password_expire_messages']['password_expire_toosimple_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Password too simple message'),
    '#description' => t('The message that will be displayed when the entered password is too simple according to the password policy.'),
    '#default_value' => variable_get('password_expire_toosimple_message', 'Your password is too simple based on our requirements. Please check the requirements which show up when you try to enter your password.'),
    '#rows' => 2,
  );
  
  if (module_exists('token')) {
    $token_types = module_invoke('password_expire', 'password_expire_token_types', 'password_expire');

    $form['password_expire_messages']['token_tree'] = array(
      '#theme'        => 'token_tree',
      '#token_types'  => (empty($token_types) ? array() : $token_types),
    );
  } else {
    $form['password_expire_messages']['token_tree'] = array(
      '#markup' => '<p>' . t('Enable the <a href="@drupal-token">Token module</a> to view the available token browser.', array('@drupal-token' => 'http://drupal.org/project/token')) . '</p>',
    );
  }

  $form['password_expire_email'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Expire E-mails'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => '',
    '#group' => 'password_expire',
  );

  $form['password_expire_email']['password_changed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password Changed'),
    '#description' => t('This e-mail will be sent when a user has changed his/her password.'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('password_expire_email_password_changed_active') == 0 ? TRUE : FALSE,
    '#group' => 'email_password_changed',
  );

  $form['password_expire_email']['password_changed']['password_expire_email_password_changed_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active'),
    '#description' => t('Check to activate the e-mail'),
    '#default_value' => variable_get('password_expire_email_password_changed_active', FALSE),
  );

  $form['password_expire_email']['password_changed']['password_expire_email_password_changed_subject'] = array(
    '#type' => 'textfield',
    '#title' => 'Subject',
    '#description' => t('Subject of the message that will be sent when a user changed his/her password'),
    '#default_value' => variable_get('password_expire_email_password_changed_subject', 'Your password for [site:url] has been updated.'),
  );

  $form['password_expire_email']['password_changed']['password_expire_email_password_changed_body'] = array(
    '#type' => 'textarea',
    '#title' => 'Body',
    '#description' => t('The message that will be sent when a user changed his/her password'),
    '#default_value' => variable_get('password_expire_email_password_changed_body', 'Your password for [site:url] has been updated. If you are not aware of this change, please contact your site administrator as soon as possible.'),
  );

  $form['password_expire_email']['password_needs_renewal'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password expired'),
    '#description' => t('This e-mail will be sent when the password of a user has been expired and needs renewal.'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('password_expire_email_password_needs_renewal_active') == 0 ? TRUE : FALSE,
    '#group' => 'email_password_needs_renewal',
  );

  $form['password_expire_email']['password_needs_renewal']['password_expire_email_password_needs_renewal_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active'),
    '#description' => t('Check to activate the e-mail'),
    '#default_value' => variable_get('password_expire_email_password_needs_renewal_active', FALSE),
  );

  $form['password_expire_email']['password_needs_renewal']['password_expire_email_password_needs_renewal_subject'] = array(
    '#type' => 'textfield',
    '#title' => 'Subject',
    '#description' => t('Subject of the message that will be sent when the password of a user is expired.'),
    '#default_value' => variable_get('password_expire_email_password_needs_renewal_subject', 'Your password for [site:url] has been expired.'),
  );

  $form['password_expire_email']['password_needs_renewal']['password_expire_email_password_needs_renewal_body'] = array(
    '#type' => 'textarea',
    '#title' => 'Body',
    '#description' => t('The message that will be sent when the password of a user is expired.'),
    '#default_value' => variable_get('password_expire_email_password_needs_renewal_body', 'This message is to inform you that your password for [site:url] has been expired. Please change your password as soon as possible.'),
  );

  $form['password_expire_email']['password_failed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Password failed'),
    '#description' => t('This e-mail will be sent when the password of a user could not be set due to a system error.'),
    '#collapsible' => TRUE,
    '#collapsed' => variable_get('password_expire_email_password_failed_active') == 0 ? TRUE : FALSE,
    '#group' => 'email_password_failed',
  );

  $form['password_expire_email']['password_failed']['password_expire_email_password_failed_active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Active'),
    '#description' => t('Check to activate the e-mail'),
    '#default_value' => variable_get('password_expire_email_password_failed_active', FALSE),
  );

  $form['password_expire_email']['password_failed']['password_expire_email_password_failed_subject'] = array(
    '#type' => 'textfield',
    '#title' => 'Subject',
    '#description' => t('Subject of the message that will be sent when the password of a user could not be set due to a system error.'),
    '#default_value' => variable_get('password_expire_email_password_failed_subject', 'Your password for [site:url] could not be updated.'),
  );

  $form['password_expire_email']['password_failed']['password_expire_email_password_failed_body'] = array(
    '#type' => 'textarea',
    '#title' => 'Body',
    '#description' => t('The message that will be sent when the password of a user could not be set due to a system error.'),
    '#default_value' => variable_get('password_expire_email_password_failed_body', 'This message is to inform you that your password for [site:url] could not be updated due to a system error. Please contact your site administrator.'),
  );

  if (module_exists('token')) {
    $token_types = module_invoke('password_expire', 'password_expire_token_types', 'password_expire');

    $form['password_expire_email']['token_tree'] = array(
      '#theme'        => 'token_tree',
      '#token_types'  => (empty($token_types) ? array() : $token_types),
    );
  } else {
    $form['password_expire_email']['token_tree'] = array(
      '#markup' => '<p>' . t('Enable the <a href="@drupal-token">Token module</a> to view the available token browser.', array('@drupal-token' => 'http://drupal.org/project/token')) . '</p>',
    );
  }

  return system_settings_form($form);
}