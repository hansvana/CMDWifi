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

  hosturl = server;
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

int CMDWifi::sendGet(char* sendKey, int value, char* getKey) { sprintf(urlPars, "/send/%s/%i/get/%s", sendKey, value, getKey); return read();};
int CMDWifi::send(char* sendKey, int value) { sprintf(urlPars, "/send/%s/%i", sendKey, value); return read();};
int CMDWifi::get(char* getKey) { sprintf(urlPars, "/get/%s", getKey); return read();};

int CMDWifi::read() {

  // if three seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest(urlPars);
  }

  char buffer[50] = "";
  int recording = 0;
  int i = 0;
  // if there is a message waiting from the server
  while (client.available()) {
    char c = client.read();
    if ((recording == 0 && c == 13) || // dumps all characters until
        (recording == 1 && c == 10) || // a sequence of 13 10 13 10 (CR LF CR LF)
        (recording == 2 && c == 13) || // is detected, then records
        (recording == 3 && c == 10))   // to buffer
          recording++;
    else if (recording != 4)
      recording = 0;
    else
      buffer[i++] = c;
  }

  if (buffer[0] != '\0') { // if buffer is not empty
    buffer[i++] = '\0'; // append \0 to terminate string
    return atoi(buffer); // return buffer as an integer
  }
  else
    return -1;
}

void CMDWifi::httpRequest(char* urlPars) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(hosturl, hostport)) {
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
