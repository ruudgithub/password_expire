# Password Expire (Drupal Module)

This drupal module allows administrators to set an expiry date on passwords. 
Users that do not renew their passwords within the given time will have to create a new password.

You can specify warning messages notifying users when their password is close to expiry. 
You can specify e-mails to be sent when a password is expired (or will expire after the warning period). 
Both messages and emails can use (but do not require) the token module (http://drupal.org/project/token) 
and provides tokens such as [password_expire:pass-expire-days-left] and [password_expire:pass-expire-date].

Note: In order for password expiry to work properly, cron must be scheduled regularly.


#### Todo

* Add possibility to define password expiry settings per user role