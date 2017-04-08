#include <CMDWifi.h>

CMDWifi wifi;

// CHANGE THESE SETTINGS
char ssid[] = "MyWifi"; // your network SSID (name)
char pass[] = "secret"; // your network password, leave empty "" for no password
char server[] = "arduino.cc"; // the url of the webserver to connect to
int port = 80; // the port on the webserver (80 is default)
String sendKey = "/send/xxxxxxxx"; // the key you will change on the server

void setup() {
  // Don't forget to set OUTPUT or INPUT on the right ports
  pinMode(2, OUTPUT);

  // initialize the connection to the server
  wifi.connect(ssid, pass, server, port);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // connect to the server, send the sensorValue to the sendKey
  String response = wifi.read(sendKey + '/' + sensorValue);

  // wait for a short time
  delay(100);
}
