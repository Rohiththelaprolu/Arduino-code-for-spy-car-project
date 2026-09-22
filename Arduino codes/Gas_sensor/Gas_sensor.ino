// ==========================================
// SPY CAR - GAS SENSOR
// XIAO ESP32-S3 Sense + MQ-2
// ==========================================

#define MQ2_PIN 4

void setup() {
  Serial.begin(115200);

  pinMode(MQ2_PIN, INPUT);

  Serial.println("MQ-2 Gas Sensor Started");
  Serial.println("Warming up sensor...");
}

void loop() {

  int gasValue = analogRead(MQ2_PIN);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > 2000) {
    Serial.println("WARNING: High gas reading!");
  }
  else {
    Serial.println("Gas level: Normal");
  }

  Serial.println("--------------------");

  delay(1000);
}