//ESP LINE FOLLOWER CAR USING L298N MOTOR DRIVER*
#include <Arduino.h>

int ENA = 12;
int ENB = 14;
int MOTOR_A1 = 13;
int MOTOR_A2 = 15;
int MOTOR_B1 = 16;
int MOTOR_B2 = 17;
int A0 = 34; // Front right sensor
int A1 = 35; // Front left sensor
int A2 = 36; // Center sensor
int A3 = 37; // Sensor between the front sensors
int A4 = 38; // Right of center sensor
int A5 = 39; // Left of center sensor

int RIGHT = A0;
int LEFT = A1;
int CENTER = A2;
int BETWEEN = A3;
int RIGHT_OF_CENTER = A4;
int LEFT_OF_CENTER = A5;

bool isExploring = true;
bool hasReachedEnd = false;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(CENTER, INPUT);
  pinMode(BETWEEN, INPUT);
  pinMode(RIGHT_OF_CENTER, INPUT);
  pinMode(LEFT_OF_CENTER, INPUT);
}

void loop() {
  int rightValue = analogRead(RIGHT);
  int leftValue = analogRead(LEFT);
  int centerValue = analogRead(CENTER);
  int betweenValue = analogRead(BETWEEN);
  int rightOfCenterValue = analogRead(RIGHT_OF_CENTER);
  int leftOfCenterValue = analogRead(LEFT_OF_CENTER);

  if (rightValue <= 35 && leftValue <= 35) {
    // MOVE FORWARD
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);

    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_A2, HIGH);
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, LOW);
  } else if (rightValue <= 35 && leftValue > 35) {
    // MOVE RIGHT
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);

    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_A2, HIGH);
    digitalWrite(MOTOR_B1, LOW);
    digitalWrite(MOTOR_B2, HIGH);
  } else if (rightValue > 35 && leftValue <= 35) {
    // MOVE LEFT
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);

    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_A2, LOW);
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, LOW);
  } else if (centerValue <= 35 || betweenValue <= 35 ||
             rightOfCenterValue <= 35 || leftOfCenterValue <= 35) {
    // ALIGN WITH CENTER, BETWEEN, RIGHT_OF_CENTER, OR LEFT_OF_CENTER SENSOR
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);

    if (centerValue <= 35) {
      // If the center sensor detects the line, move left
      digitalWrite(MOTOR_A1, HIGH);
      digitalWrite(MOTOR_A2, LOW);
      digitalWrite(MOTOR_B1, LOW);
      digitalWrite(MOTOR_B2, HIGH);
    } else if (betweenValue <= 35) {
      // If the between sensor detects the line, move right
      digitalWrite(MOTOR_A1, LOW);
      digitalWrite(MOTOR_A2, HIGH);
      digitalWrite(MOTOR_B1, HIGH);
      digitalWrite(MOTOR_B2, LOW);
    } else if (rightOfCenterValue <= 35) {
      // If the right-of-center sensor detects the line, make a slight right turn
      // Adjust motor speeds and direction as needed
    } else if (leftOfCenterValue <= 35) {
      // If the left-of-center sensor detects the line, make a slight left turn
      // Adjust motor speeds and direction as needed
    }
  } else {
    // No line detected by any front sensors
    if (isExploring) {
      // Check if the robot has reached the final end (all sensors see black)
      if (rightValue <= 35 && leftValue <= 35 &&
          centerValue <= 35 && betweenValue <= 35 &&
          rightOfCenterValue <= 35 && leftOfCenterValue <= 35) {
        hasReachedEnd = true;
      }
      if (hasReachedEnd) {
        // Stop the motors or take any necessary action
        analogWrite(ENA, 0);
        analogWrite(ENB, 0);
        isExploring = false;
      } else {
        // Make a U-turn
        analogWrite(ENA, 255);
        analogWrite(ENB, 255);

        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, HIGH);
        digitalWrite(MOTOR_B1, LOW);
        digitalWrite(MOTOR_B2, HIGH);
        delay(1000);  // Adjust the delay for the U-turn
        isExploring = false;  // Stop exploring
      }
    }
    // Continue exploring by making a turn and set isExploring to true
  }
}
