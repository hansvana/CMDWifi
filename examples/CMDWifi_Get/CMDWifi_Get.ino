#include <CMDWifi.h>

CMDWifi wifi;

// CHANGE THESE SETTINGS
char ssid[] = "MyWifi"; // your network SSID (name)
char pass[] = "secret"; // your network password, leave empty "" for no password
char server[] = "arduino.cc"; // the url of the webserver to connect to
int port = 80; // the port on the webserver (80 is default)
char getKey[] = "xxxxxxxx"; // the key you want to read from the server

void setup() {
  // Don't forget to set OUTPUT or INPUT on the right ports
  pinMode(3, OUTPUT);

  // initialize the connection to the server
  wifi.connect(ssid, pass, server, port);

}

void loop() {
  // connect to the server, read from the getKey
  int response = wifi.get(getKey);

  // only do this part if the response is a real number
  if (response >= 0){
    // print the response (for debugging purposes only)
    Serial.println(response);

    // write the integer
    analogWrite(3, response);
  }

  // wait for a short time
  delay(100);
}
