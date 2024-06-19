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

const uint8_t IOT_HUB_FINGERPRINT[] = {0x64, 0xf2, 0xd3, 0xb8, 0x13, 0x6c, 0x18, 0xaf, 0xb5, 0x59, 0x9b, 0xbf, 0x28, 0xfa, 0x32, 0x3a, 0xb1, 0x43, 0x0a, 0x12};

#endif