#include <CMDWifi.h>

CMDWifi wifi;

// CHANGE THESE SETTINGS
char ssid[] = "MyWifi"; // your network SSID (name)
char pass[] = "secret"; // your network password, leave empty "" for no password
char server[] = "arduino.cc"; // the url of the webserver to connect to
int port = 80; // the port on the webserver (80 is default)
String getKey = "/get/xxxxxxxx"; // the key you want to read from the server

void setup() {
  // Don't forget to set OUTPUT or INPUT on the right ports
  pinMode(3, OUTPUT);

  // initialize the connection to the server
  wifi.connect(ssid, pass, server, port);

}

void loop() {
  // connect to the server, read from the getKey
  char* response = wifi.get(getKey);

  // only do this part if there is a response from the server
  if (response != ""){
    // print the response (for debugging purposes only)
    Serial.println(response);

    // right now the response is a string, but we want to use it
    // as a number (integer), so we convert it with toInt. The resulting
    // number is stored in responseInt.
    int responseInt = response.toInt();

    // write the integer
    analogWrite(3, responseInt);
  }

  // wait for a short time
  delay(100);
}
