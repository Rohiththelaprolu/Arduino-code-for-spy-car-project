// ==========================================
// SPY CAR - ULTRASONIC SENSOR
// XIAO ESP32-S3 Sense + HC-SR04
// ==========================================

#define TRIG_PIN 1
#define ECHO_PIN 2

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  Serial.println("Ultrasonic Sensor Started");
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo time
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Calculate distance
  float distance = duration * 0.0343 / 2;

  if (duration == 0) {
    Serial.println("No object detected");
  }
  else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}