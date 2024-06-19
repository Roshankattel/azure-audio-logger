#include "httpsPostReq.h"
#include "Arduino.h"
#include "config.h"

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
    Serial.println("Waiting 10 sec before the next round...");
    delay(10000);
    return httpCode;
}