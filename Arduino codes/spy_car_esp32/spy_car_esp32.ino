// ==========================================
// AI SEARCH & RESCUE SPY CAR
// ESP32 + 2x L298N + 4 DC Gear Motors
// ==========================================

// L298N #1 - LEFT SIDE
#define FL_IN1 18
#define FL_IN2 19

#define RL_IN1 21
#define RL_IN2 22

// L298N #2 - RIGHT SIDE
#define FR_IN1 23
#define FR_IN2 25

#define RR_IN1 26
#define RR_IN2 27


void setup() {

  pinMode(FL_IN1, OUTPUT);
  pinMode(FL_IN2, OUTPUT);

  pinMode(RL_IN1, OUTPUT);
  pinMode(RL_IN2, OUTPUT);

  pinMode(FR_IN1, OUTPUT);
  pinMode(FR_IN2, OUTPUT);

  pinMode(RR_IN1, OUTPUT);
  pinMode(RR_IN2, OUTPUT);

  stopCar();

  Serial.begin(115200);
}


void loop() {

  // Temporary testing sequence
  // We will replace this with Wi-Fi control later.

  forward();
  delay(2000);

  stopCar();
  delay(1000);

  backward();
  delay(2000);

  stopCar();
  delay(1000);

  left();
  delay(1500);

  stopCar();
  delay(1000);

  right();
  delay(1500);

  stopCar();
  delay(2000);
}


// ==========================================
// FORWARD
// ==========================================

void forward() {

  // Front Left
  digitalWrite(FL_IN1, HIGH);
  digitalWrite(FL_IN2, LOW);

  // Rear Left
  digitalWrite(RL_IN1, HIGH);
  digitalWrite(RL_IN2, LOW);

  // Front Right
  digitalWrite(FR_IN1, HIGH);
  digitalWrite(FR_IN2, LOW);

  // Rear Right
  digitalWrite(RR_IN1, HIGH);
  digitalWrite(RR_IN2, LOW);
}


// ==========================================
// BACKWARD
// ==========================================

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


// ==========================================
// LEFT
// ==========================================

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


// ==========================================
// RIGHT
// ==========================================

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


// ==========================================
// STOP
// ==========================================

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