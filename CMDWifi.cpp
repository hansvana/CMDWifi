/*
  CMDWifi.cpp - Wrapper for the Wifi101 library
  Based on the Repeating Wifi Web Client example

  Created 23 April 2012, modified 31 May 2012
	by Tom Igoe
  Modified 13 Jan 2014
	by Federico Vanzati
  CMDWifi wrapper created 4 April 2017
	by Hans van Arken

  Released into the public domain.
*/

#include "Arduino.h"
#include <SPI.h>
#include <WiFi101.h>
#include "CMDWifi.h"
#include "string.h"

CMDWifi::CMDWifi() {
  status = WL_IDLE_STATUS;

  //Configure pins for Adafruit ATWINC1500 Breakout
  WiFi.setPins(8,7,4);
}

void CMDWifi::connect(char * ssid, char * pass, char * server, int port = 80)
{
	//Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

	if (ssid == 0 || server == 0) {
		Serial.println("SSID or server not set");
    while (true);
	}
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  hosturl = "cmd.camp";
  hostport = port;

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    if (strlen(pass) == 0) {
      // Connect to open network.
      status = WiFi.begin(ssid);
    } else {
      // Connect to WPA/WPA2 network.
      status = WiFi.begin(ssid, pass);
    }


    // wait 5 seconds for connection:
    delay(5000);
  }
  // you're connected now, so print out the status:
  printWiFiStatus();
}

String CMDWifi::read(String urlPars) {

  String str = "";

  // if there is a message waiting from the server
  // apppend it to str
  while (client.available()) {
    char c = client.read();
    str += c;
  }

  // if three seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest(urlPars);
  }

  // trim str to just the content and return it
  return grabContent(str);
}

void CMDWifi::httpRequest(String urlPars) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(hosturl.c_str(), hostport)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.print("GET ");
    client.print(urlPars);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.print(hosturl);
    client.print(":");
    client.println(hostport);
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

String CMDWifi::grabContent(String response) {
  // find the first blank line
  int endOfHeader = response.indexOf("\r\n\r\n");
  // return everything after that
  return response.substring(endOfHeader + 4);
}

void CMDWifi::printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
