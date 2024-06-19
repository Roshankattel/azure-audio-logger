
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "config.h"

unsigned long soundValue = 0;
unsigned long sampleBufferValue = 0;
uint8_t sampleCount = 0;
uint64_t msgCount = 0;

// Functions
int restPostData(String URI, String authorization, String postData)
{
  int httpCode = -1;
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  // Ignore SSL certificate validation
  // client->setFingerprint(fingerprint);
  client->setInsecure();
  // create an HTTPClient instance
  HTTPClient https;
  // Initializing an HTTPS communication using the secure client
  Serial.print("[HTTPS] begin...\n");
  if (https.begin(*client, URI))
  { // HTTPS
    Serial.print("[HTTPS] POST...\n");
    // start connection and send HTTP header
    https.addHeader("Authorization", authorization);
    https.addHeader("Content-Type", "application/json");
    httpCode = https.POST(postData);
    // httpCode will be negative on error
    if (httpCode > 0)
    {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_NO_CONTENT)
      {
        String payload = https.getString();
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  }
  else
  {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
  Serial.println("Waiting 2min before the next round...");
  delay(120000);
  return httpCode;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(SOUND_PIN, INPUT);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nConnected to ");
  Serial.println(WiFi.SSID());
}

void loop()
{
  // put your main code here, to run repeatedly:
  sampleBufferValue += analogRead(SOUND_PIN);
  sampleCount++;
  if (sampleCount > NO_SAMPLE)
  {
    soundValue = sampleBufferValue / NO_SAMPLE;
    // Serial.println(soundValue);
    if (soundValue > 200)
    {
      Serial.println("\nSound Detected:" + String(msgCount));
      msgCount++;
      String postData = "{\"sound_received\":true, \"msg_count\": " + String(msgCount) + ", \"millis\": " + String(millis()) + ",\"wifi_rssi\": " + String(WiFi.RSSI()) + "}";
      Serial.println(postData);
      int returnCode = restPostData(IOT_HUB_URL, SAS_TOKEN, postData);
      // Serial.println(returnCode);
    }
    sampleBufferValue = 0;
    sampleCount = 0;
  }
}
