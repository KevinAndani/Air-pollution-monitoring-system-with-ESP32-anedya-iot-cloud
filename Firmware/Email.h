#ifndef EMAIL_H_
#define EMAIL_H_
#include <ESP_Mail_Client.h>

/** The smtp host name e.g. smtp.gmail.com for GMail or smtp.office365.com for Outlook or smtp.mail.yahoo.com */
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "esp32.anedya@gmail.com"
#define AUTHOR_PASSWORD "rerx mnwl wltp mhoy"

/* Recipient's email*/
#define RECIPIENT_EMAIL "sam.m325511@gmail.com"

void configMailClient();
String readHTMLTemplate();
void sendMail(const String& htmlContent);
void smtpCallback(SMTP_Status status);  //Callback Function Declaration

#endif