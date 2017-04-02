/*
  CMDWifi.h - Wrapper for the Wifi101 library
  Based on the Repeating Wifi Web Client example

  Created 23 April 2012, modified 31 May 2012
	by Tom Igoe
  Modified 13 Jan 2014
	by Federico Vanzati
  CMDWifi wrapper created 4 April 2017
	by Hans van Arken

  Released into the public domain.
*/
#ifndef CMDWifi_h
#define CMDWifi_h

#include "Arduino.h"
#include <SPI.h>
#include <WiFi101.h>

class CMDWifi {
	public:
    CMDWifi();
    void connect(char * ssid, char * pass);
    String read();

	private:
    void printWiFiStatus();
    void httpRequest();
    String grabContent(String response);

    int status;
    WiFiClient client;
    unsigned long lastConnectionTime;
    const unsigned long postingInterval = 3L * 1000L;
};

#endif
