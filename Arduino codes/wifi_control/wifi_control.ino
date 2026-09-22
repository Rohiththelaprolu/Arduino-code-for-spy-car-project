// ==========================================
// SPY CAR - WIFI COMMUNICATION
// XIAO ESP32-S3 Sense
// ==========================================

#include <WiFi.h>
#include <WebServer.h>

// ESP32 creates its own Wi-Fi network
const char* ssid = "SPY_CAR";
const char* password = "12345678";

WebServer server(80);


// ==========================================
// HOME PAGE
// ==========================================

void handleRoot() {

  String page = "";

  page += "<html>";
  page += "<head>";
  page += "<title>Spy Car Control</title>";
  page += "</head>";

  page += "<body>";
  page += "<h1>SPY CAR</h1>";

  page += "<p>Wi-Fi communication working!</p>";

  page += "<button onclick=\"location.href='/forward'\">FORWARD</button><br><br>";
  page += "<button onclick=\"location.href='/backward'\">BACKWARD</button><br><br>";
  page += "<button onclick=\"location.href='/left'\">LEFT</button><br><br>";
  page += "<button onclick=\"location.href='/right'\">RIGHT</button><br><br>";
  page += "<button onclick=\"location.href='/stop'\">STOP</button>";

  page += "</body>";
  page += "</html>";

  server.send(200, "text/html", page);
}


// ==========================================
// MOVEMENT COMMANDS
// ==========================================

void handleForward() {

  Serial.println("COMMAND: FORWARD");

  server.send(200, "text/plain", "FORWARD command received");
}


void handleBackward() {

  Serial.println("COMMAND: BACKWARD");

  server.send(200, "text/plain", "BACKWARD command received");
}


void handleLeft() {

  Serial.println("COMMAND: LEFT");

  server.send(200, "text/plain", "LEFT command received");
}


void handleRight() {

  Serial.println("COMMAND: RIGHT");

  server.send(200, "text/plain", "RIGHT command received");
}


void handleStop() {

  Serial.println("COMMAND: STOP");

  server.send(200, "text/plain", "STOP command received");
}


// ==========================================
// SETUP
// ==========================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("SPY CAR WIFI STARTING");
  Serial.println("================================");


  // Create Wi-Fi hotspot
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();

  Serial.println("Wi-Fi started!");
  Serial.print("Network: ");
  Serial.println(ssid);

  Serial.print("Password: ");
  Serial.println(password);

  Serial.print("ESP32 IP address: ");
  Serial.println(IP);


  // Web pages
  server.on("/", handleRoot);

  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);


  server.begin();

  Serial.println("Web server started!");
}


// ==========================================
// LOOP
// ==========================================

void loop() {

  server.handleClient();
}