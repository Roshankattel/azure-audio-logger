#ifndef HTTP_POST_REQ_H
#define HTTP_POST_REQ_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int restPostData(String URI, String authorization, String postData);

#endif