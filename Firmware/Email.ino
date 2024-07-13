#include "Email.h"
//#include<SPIFFS.h>

SMTPSession smtp; //Declares a global SMTP session object.

void configMailClient()
{
  /*  Set the network reconnection option */
  MailClient.networkReconnect(true);
}

void sendMail(const String& htmlContent)
{
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the Session_Config for user defined session credentials */
  Session_Config config;

  /* Set the session config */
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = F("ESP32");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("ESP Test Email");
  message.addRecipient(F("Sam"), RECIPIENT_EMAIL);
  message.html.content = htmlContent.c_str();
  message.html.charSet = "utf-8";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_base64;

  /*Send raw text message
  String textMsg = "Hello World! - Sent from ESP32 board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;*/
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Connect to the server */
  if (!smtp.connect(&config)){
    ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return;
  }

  if (!smtp.isLoggedIn()){
    Serial.println("\nNot yet logged in.");
  }
  else{
    if (smtp.isAuthenticated())
      Serial.println("\nSuccessfully logged in.");
    else
      Serial.println("\nConnected with no Auth.");
  }

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());

}

void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
    Serial.println("----------------\n");

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      SMTP_Result result = smtp.sendingResult.getItem(i);
      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      //ESP_MAIL_PRINTF("Date/Time: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");

    smtp.sendingResult.clear();
  }
}

// Function to read HTML template from SPIFFS
/*
String readHTMLTemplate() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    Serial.println("Failed to open email template file");
    return String();
  }
  
  String html = file.readString();
  file.close();
  return html;
}*/

String readHTMLTemplate(){
  const char* htmlTemplate = R"rawliteral(
    <!DOCTYPE html>
    <html lang="en">
      <head>
        <meta charset="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <title>Air Pollution Monitoring System</title>
        <style>
          @import url("https://fonts.googleapis.com/css2?family=Montserrat:wght@700&display=swap");
        </style>
      </head>
      <body
        style="
          font-family: 'Montserrat', sans-serif;
          font-weight: 700;
          background-color: #efefef;
          font-size: 18px;
          max-width: 1000px;
          margin: 0 auto;
          padding: 2%;
          color: #070707;
        "
      >
        <div id="wrapper" style="background: #ffffff">
          <header style="width: 98%">
            <div id="logo" style="max-width: 220px; margin: 2% 0 0 2%; float: left">
              <img
                src="https://camo.githubusercontent.com/00698523a24aceaf26c4ee903f8fa46a7d0365da43fc64d69787e2b5f9448bef/68747470733a2f2f63646e2e616e656479612e696f2f616e656479615f626c61636b5f62616e6e65722e706e67"
                style="max-width: 100%"
              />
            </div>
            <div id="System_name" style="float: right; margin: 3.25% 2% 0 0">
              <h2>Air pollution monitoring system</h2>
            </div>
          </header>
          <div id="Dashboard" style="margin: 2% 2% 0 2%; max-width: 100%">
            <a href="https://cloud.anedya.io/login">
              <img
                src="https://i.postimg.cc/658Zm12m/Air-Quality-Monitoring-System.jpg"
                alt="Click to see the data"
                style="max-width: 100%"
              />
            </a>
          </div>
        </div>
      </body>
    </html>
    )rawliteral";
    return String(htmlTemplate);
}