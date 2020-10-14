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

For extra security an option is added to reset passwords to a random secure string using cron if passwords have not been changed for a specified period.
This is configurable on the settings page including the period of expiration.
This will prevent that if a users' password is leaked and you have a user in your system with the same username and password, this user's account password will not be vulnerable longer than the specified period.
This is also useful for single sign-on modules where the drupal password is not used anymore and so won't be changed by the user.

## Installation

1. Copy the password_expire folder to Drupal's directory: sites/all/modules
2. Go to Drupal, open 'Modules', and install/enable the module 'Password Expire'
3. Configure the password expiration settings on the configuration page: Configuration -> People -> Account settings -> Password Expire or use the 'Configure' button on the modules page.

Note: In order for the password expiry to work properly, cron must be scheduled regularly.

Password expiration will be checked and set on every cron run.

To schedule a reset of expired passwords:
1. Enable 'Reset password to a random (secure) string when passwords are expired'
   on the configuration page: Configuration -> People -> Accounts settings -> Password Expire -> Tab 'Password Reset on Expiration'

2. Schedule a cron job:
For example if you want the expired passwords to reset on every 1th day of the month at 3:00 AM, add the following line to /etc/crontab:
0 3 1 * *   drushuser    drush password-expire-reset-expired-passwords
where drushuser is your cron-user which is allowed to run drush

Or use any other method of running a scheduled job and use the command:
drush password-expire-reset-expired-passwords

## Future Ideas

* Add possibility to define a password policy per user role