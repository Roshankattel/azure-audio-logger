
#include <Arduino.h>
#include "httpsPostReq.h"
#include "config.h"

unsigned long soundValue = 0;
unsigned long sampleBufferValue = 0;
uint8_t sampleCount = 0;
uint64_t msgCount = 0;

#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup()
{
  Serial.begin(115200);
  pinMode(SOUND_PIN, INPUT);
  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  Serial.print("\nConnected to ");
  Serial.println(WiFi.SSID());
}

void loop()
{
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
      if ((WiFiMulti.run() == WL_CONNECTED))
      {
        int returnCode = restPostData(IOT_HUB_URL, SAS_TOKEN, postData);
        Serial.println(returnCode);
      }
    }
    sampleBufferValue = 0;
    sampleCount = 0;
  }
}
