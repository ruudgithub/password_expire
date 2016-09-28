# Password Expire (Drupal 7 Module)

This drupal module allows administrators to set an expiry date on passwords. 
Users that do not renew their password within the given time will have to create a new password.

You can specify a password policy, options to configure:
  - Expiry period: Period before a password expires
  - Warning period: Period in which the user gets a warning that his/her password is about to expire
  - Minimum password length: The minimum length a password should meet 
  - Password requirements: Does a password require lowercase/uppercase/numbers/special characters (or all of them)

You can specify messages messages, notifying users when their password is close to expiry or expired. 
You can specify e-mails to be sent when a password is expired (or will expire after the warning period). 
Both messages and emails can use (but do not require) the token module (https://www.drupal.org/project/token) and provides tokens such as [password_expire:pass-expire-days-left] and [password_expire:pass-expire-date].

## Installation

1. Copy the password_expire folder to Drupal's directory: sites/all/modules
2. Go to Drupal, open 'Modules', and install/enable the module 'Password Expire'
3. Configure the password expiration settings on the configuration page: Configuration -> People -> Account settings -> Password Expire or use the 'Configure' button on the modules page.

Note: In order for password expiry to work properly, cron must be scheduled regularly.

#### Future Ideas

* Add possibility to define a password policy per user role
* Just an idea for extra security: Add an option to reset passwords automatically using cron if a user has not logged on for a specified period (f.e. 1 year). Of course this will be configurable on the settings page to turn it on/off. This will prevent that if any site on earth is hacked and you have the same user with the same password, this user's account will not be vulnerable longer than the specified period.