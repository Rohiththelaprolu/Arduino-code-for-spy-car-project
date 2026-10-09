
#include <WiFi.h>
#include <WebServer.h>

// ==========================================
// SPY CAR - NORMAL ESP32
// Motors + Wi-Fi + Ultrasonic
// ==========================================

const char* ssid = "SPY_CAR_CTRL";
const char* password = "12345678";

WebServer server(80);

// Provisional motor pins: verify before wiring
#define FL_IN1 18
#define FL_IN2 19
#define RL_IN1 21
#define RL_IN2 22

#define FR_IN1 23
#define FR_IN2 25
#define RR_IN1 26
#define RR_IN2 27

// Ultrasonic pins: verify before wiring
#define TRIG_PIN 32
#define ECHO_PIN 33

void stopCar() {
  digitalWrite(FL_IN1, LOW);
  digitalWrite(FL_IN2, LOW);
  digitalWrite(RL_IN1, LOW);
  digitalWrite(RL_IN2, LOW);
  digitalWrite(FR_IN1, LOW);
  digitalWrite(FR_IN2, LOW);
  digitalWrite(RR_IN1, LOW);
  digitalWrite(RR_IN2, LOW);
}

void forward() {
  digitalWrite(FL_IN1, HIGH);
  digitalWrite(FL_IN2, LOW);
  digitalWrite(RL_IN1, HIGH);
  digitalWrite(RL_IN2, LOW);
  digitalWrite(FR_IN1, HIGH);
  digitalWrite(FR_IN2, LOW);
  digitalWrite(RR_IN1, HIGH);
  digitalWrite(RR_IN2, LOW);
}

void backward() {
  digitalWrite(FL_IN1, LOW);
  digitalWrite(FL_IN2, HIGH);
  digitalWrite(RL_IN1, LOW);
  digitalWrite(RL_IN2, HIGH);
  digitalWrite(FR_IN1, LOW);
  digitalWrite(FR_IN2, HIGH);
  digitalWrite(RR_IN1, LOW);
  digitalWrite(RR_IN2, HIGH);
}

void left() {
  digitalWrite(FL_IN1, LOW);
  digitalWrite(FL_IN2, HIGH);
  digitalWrite(RL_IN1, LOW);
  digitalWrite(RL_IN2, HIGH);
  digitalWrite(FR_IN1, HIGH);
  digitalWrite(FR_IN2, LOW);
  digitalWrite(RR_IN1, HIGH);
  digitalWrite(RR_IN2, LOW);
}

void right() {
  digitalWrite(FL_IN1, HIGH);
  digitalWrite(FL_IN2, LOW);
  digitalWrite(RL_IN1, HIGH);
  digitalWrite(RL_IN2, LOW);
  digitalWrite(FR_IN1, LOW);
  digitalWrite(FR_IN2, HIGH);
  digitalWrite(RR_IN1, LOW);
  digitalWrite(RR_IN2, HIGH);
}

float readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0343f / 2.0f;
}

void sendStatus() {
  float distance = readDistanceCM();

  String message = "SPY CAR STATUS\nDistance: ";
  if (distance < 0) {
    message += "No echo";
  } else {
    message += String(distance, 1) + " cm";
  }

  server.send(200, "text/plain", message);
}

void setup() {
  Serial.begin(115200);

  pinMode(FL_IN1, OUTPUT);
  pinMode(FL_IN2, OUTPUT);
  pinMode(RL_IN1, OUTPUT);
  pinMode(RL_IN2, OUTPUT);
  pinMode(FR_IN1, OUTPUT);
  pinMode(FR_IN2, OUTPUT);
  pinMode(RR_IN1, OUTPUT);
  pinMode(RR_IN2, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopCar();

  server.on("/", []() {
    server.send(200, "text/html",
      "<h1>SPY CAR CONTROL</h1>"
      "<p><a href='/forward'>Forward</a></p>"
      "<p><a href='/backward'>Backward</a></p>"
      "<p><a href='/left'>Left</a></p>"
      "<p><a href='/right'>Right</a></p>"
      "<p><a href='/stop'>STOP</a></p>"
      "<p><a href='/status'>Sensor status</a></p>");
  });

  server.on("/forward", []() {
    forward();
    server.send(200, "text/plain", "Forward");
  });

  server.on("/backward", []() {
    backward();
    server.send(200, "text/plain", "Backward");
  });

  server.on("/left", []() {
    left();
    server.send(200, "text/plain", "Left");
  });

  server.on("/right", []() {
    right();
    server.send(200, "text/plain", "Right");
  });

  server.on("/stop", []() {
    stopCar();
    server.send(200, "text/plain", "Stopped");
  });

  server.on("/status", sendStatus);

  WiFi.softAP(ssid, password);

  Serial.println("Spy Car controller started");
  Serial.print("Wi-Fi: ");
  Serial.println(ssid);
  Serial.print("Controller IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  server.handleClient();
}
