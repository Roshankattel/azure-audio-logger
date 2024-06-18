
#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

#define SOUND_PIN A0
const int NO_SAMPLE = 100;
unsigned long soundValue = 0;
unsigned long sampleBufferValue = 0;
uint8_t sampleCount = 0;

// Replace with your network credentials
const char *ssid = "bhojpure";
const char *password = "Bhojpure@4109123";

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
      Serial.println("Sound Detected");
      delay(10000);
    }
    sampleBufferValue = 0;
    sampleCount = 0;
  }
}
