/*
  CMDWifi.h - Wrapper for the WiFiNINA library
  Based on the Repeating Wifi Web Client example

  Created 23 April 2012, modified 31 May 2012
	by Tom Igoe
  Modified 13 Jan 2014
	by Federico Vanzati
  CMDWifi wrapper created 4 April 2017
	by Hans van Arken
  Modified 12 Febuary 2023
	by Michael Tjia

  Released into the public domain.
*/
#ifndef CMDWifi_h
#define CMDWifi_h

#include "Arduino.h"
#include <SPI.h>
#include <WiFiNINA.h>

class CMDWifi {
	public:
    CMDWifi();
    void connect(char* ssid, char* pass, char* server, int port);
		int sendGet(char* sendKey, int value, char* getKey);
		int send(char* sendKey, int value);
		int get(char* getKey);

	private:
		int read();
    void printWiFiStatus();
    void httpRequest(char* urlPars);
    char* grabContent(char* response);

    int status;
    WiFiClient client;
		char* hosturl;
		char urlPars[50];
		int hostport;
		unsigned long lastConnectionTime;
    const unsigned long postingInterval = 3L * 1000L;

};

#endif
