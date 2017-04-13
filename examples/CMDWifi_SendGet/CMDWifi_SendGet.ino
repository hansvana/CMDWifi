#include <CMDWifi.h>

CMDWifi wifi;

// CHANGE THESE SETTINGS
char ssid[] = "Network"; // your network SSID (name)
char pass[] = "secret"; // your network password, leave empty "" for no password
char server[] = "arduino.cc"; // the url of the webserver to connect to
int port = 80; // the port on the webserver (80 is default)
char sendKey[] = "xxxxx"; // the key you will change on the server
char getKey[] = "xxxxx"; // the key you want to read from the server

void setup() {
  // Don't forget to set OUTPUT or INPUT on the right ports
  pinMode(3, OUTPUT);

  // initialize the connection to the server
  wifi.connect(ssid, pass, server, port);
}

void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  // connect to the server, send the sensorValue to the sendKey
  // and read from the getKey. Here be magic.
  char* response = wifi.sendGet(sendKey, sensorValue, getKey);

  // only do this part if there is a response from the server
  if (response != ""){
    // print the response (for debugging purposes only)
    Serial.println(response);

    // right now the response is a string, but we want to use it
    // as a number (integer), so we convert it with atoi(). The resulting
    // number is stored in responseInt.
    int responseInt = atoi(response);

    // do something with responseInt
    if (responseInt == 1) {
      digitalWrite(3, HIGH);
    } else {
      digitalWrite(3, LOW);
    }

  }

  // wait for a short time
  delay(100);
}
