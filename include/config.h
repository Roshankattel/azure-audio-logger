#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"

#define SOUND_PIN A0

#define NO_SAMPLE 100

// wifi details
const char *ssid = "bhojpure";
const char *password = "Bhojpure@4109123";

const char IOT_HUB_URL[] PROGMEM = R"=====(https://koili-iot-staging.azure-devices.net/devices/2407-sound-feedback/messages/events?api-version=2020-03-13)=====";
const char SAS_TOKEN[] PROGMEM = R"=====(SharedAccessSignature sr=koili-iot-staging.azure-devices.net%2Fdevices%2F2407-sound-feedback&sig=MX%2Fz2G6FPYLCONnBT2p8SwE0beuHHlNgV2VrT05Is%2Fc%3D&se=3432591426)=====";
const char IOT_HUB_FINGERPRINT[] PROGMEM = R"=====(64:F2:D3:B8:13:6C:18:AF:B5:59:9B:BF:28:FA:32:3A:B1:43:0A:12)=====";

#endif