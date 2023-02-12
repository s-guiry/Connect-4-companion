#include <Servo.h>

#define ENA 6
#define LEFT_FWD 11
#define LEFT_BCK 9
#define RIGHT_FWD 8
#define RIGHT_BCK 7
#define ENB 5

#define SERVO_1 3
#define SERVO_2 2

Servo servo1;
Servo servo2;

// set current column
int cur_col = -1;

void setup() {
  // set pinmodes
  pinMode(ENA, OUTPUT);
  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_BCK, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_BCK, OUTPUT);
  pinMode(ENB, OUTPUT);

  // setup servo
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);

  // start serial
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    int col = Serial.read() - 'a' - 1;

    if (col == 10) { // reset the piece
      col = -1;
    }

    // move to the column
    moveTo(col);
    
    // drop piece
    servo1.write(180);
    delay(1000);
    servo1.write(90);
    delay(1000);

    // queue next piece
    servo2.write(180);
    delay(1000);
    servo2.write(90);
    delay(1000);

    // put the robot back into place
    moveTo(-1);
  }
}

void moveTo(int col) {
  bool fwd = col > cur_col;

  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(LEFT_FWD, fwd);
  digitalWrite(LEFT_BCK, !fwd);
  digitalWrite(RIGHT_FWD, !fwd);
  digitalWrite(RIGHT_BCK, fwd);
  
  delay(20 * abs(col - cur_col));

  digitalWrite(LEFT_FWD, 0);
  digitalWrite(LEFT_BCK, 0);
  digitalWrite(RIGHT_FWD, 0);
  digitalWrite(RIGHT_BCK, 0);

  cur_col = col;
}