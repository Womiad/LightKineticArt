// ==========================================
// ESP32 + DRV8833 雙馬達測試程式
//
// 接線：
// AIN1 -> GPIO 26
// AIN2 -> GPIO 27
// BIN1 -> GPIO 32
// BIN2 -> GPIO 33
// STBY -> GPIO 25
//
// DRV8833 VM  -> 2x AA 電池正極
// DRV8833 GND -> 2x AA 電池負極
// DRV8833 GND -> ESP32 GND（一定要共地）
//
// ESP32 使用 USB 供電
// ==========================================


// ---------- Pin 定義 ----------

const int AIN1 = 26;
const int AIN2 = 27;

const int BIN1 = 32;
const int BIN2 = 33;

const int STBY = 25;


// ==========================================
// 馬達 A 控制
//
// direction:
//   1  = 正轉
//  -1  = 反轉
//   0  = 停止
// ==========================================

void motorA(int direction) {

  if (direction > 0) {

    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);

  } else if (direction < 0) {

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);

  } else {

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
}


// ==========================================
// 馬達 B 控制
// ==========================================

void motorB(int direction) {

  if (direction > 0) {

    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);

  } else if (direction < 0) {

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);

  } else {

    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
}


// ==========================================
// 停止
// ==========================================

void stopMotors() {

  motorA(0);
  motorB(0);

  Serial.println("STOP");
}


// ==========================================
// 前進
// ==========================================

void forward() {

  motorA(1);
  motorB(1);

  Serial.println("FORWARD");
}


// ==========================================
// 後退
// ==========================================

void backward() {

  motorA(-1);
  motorB(-1);

  Serial.println("BACKWARD");
}


// ==========================================
// 左轉
// ==========================================

void turnLeft() {

  motorA(-1);
  motorB(1);

  Serial.println("LEFT");
}


// ==========================================
// 右轉
// ==========================================

void turnRight() {

  motorA(1);
  motorB(-1);

  Serial.println("RIGHT");
}


// ==========================================
// Setup
// ==========================================

void setup() {

  Serial.begin(115200);

  // 設定 GPIO
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);


  // 開機先停止馬達
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);


  // 啟用 DRV8833
  digitalWrite(STBY, HIGH);


  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 + DRV8833 Motor Test");
  Serial.println("==============================");

  delay(2000);
}


// ==========================================
// Main Loop
// ==========================================

void loop() {

  // ---------- 前進 ----------

  Serial.println();
  Serial.println("Testing FORWARD");

  forward();

  delay(1000);

  stopMotors();

  delay(1000);


  // ---------- 後退 ----------

  Serial.println();
  Serial.println("Testing BACKWARD");

  backward();

  delay(1000);

  stopMotors();

  delay(1000);


  // ---------- 左轉 ----------

  Serial.println();
  Serial.println("Testing LEFT");

  turnLeft();

  delay(1000);

  stopMotors();

  delay(1000);


  // ---------- 右轉 ----------

  Serial.println();
  Serial.println("Testing RIGHT");

  turnRight();

  delay(1000);

  stopMotors();

  delay(2000);


  Serial.println();
  Serial.println("===== Test cycle finished =====");

  delay(2000);
}