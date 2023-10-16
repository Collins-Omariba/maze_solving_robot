//ESP LINE FOLLOWER CAR USING L298N MOTOR DRIVER*
#include <Arduino.h>

int ENA = 12; // Enable for Motor A
int ENB = 14; // Enable for Motor B
int ENA2 = 27; // Enable for Motor A2 (for the second L293D)
int ENB2 = 26; // Enable for Motor B2 (for the second L293D)

int MOTOR_A1 = 13; // Motor A, input 1
int MOTOR_A2 = 15; // Motor A, input 2
int MOTOR_B1 = 16; // Motor B, input 1
int MOTOR_B2 = 17; // Motor B, input 2

int MOTOR_A3 = 18; // Motor A2, input 1 (for the second L293D)
int MOTOR_A4 = 19; // Motor A2, input 2 (for the second L293D)
int MOTOR_B3 = 21; // Motor B2, input 1 (for the second L293D)
int MOTOR_B4 = 22; // Motor B2, input 2 (for the second L293D)

int RIGHT = 34; // Front right sensor
int LEFT = 35; // Front left sensor
int CENTER = 36; // Center sensor
int BETWEEN = 37; // Sensor between the front sensors
int RIGHT_OF_CENTER = 38; // Right of center sensor
int LEFT_OF_CENTER = 39; // Left of center sensor

bool isExploring = true;
bool hasReachedEnd = false;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(ENB2, OUTPUT);
  
  // Set the motor control pins as outputs
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  
  pinMode(MOTOR_A3, OUTPUT);
  pinMode(MOTOR_A4, OUTPUT);
  pinMode(MOTOR_B3, OUTPUT);
  pinMode(MOTOR_B4, OUTPUT);
  
  // Initialize motor control
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(ENA2, LOW);
  digitalWrite(ENB2, LOW);
}
void move_forward(){
   // MOVE FORWARD
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);
    analogWrite(ENA2, 100);
    analogWrite(ENB2, 100);

    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_A2, HIGH);
    digitalWrite(MOTOR_B1, LOW);
    digitalWrite(MOTOR_B2, HIGH);
    digitalWrite(MOTOR_A3, LOW);
    digitalWrite(MOTOR_A4, HIGH);
    digitalWrite(MOTOR_B3, LOW);
    digitalWrite(MOTOR_B4, HIGH);
}

void right_turn(){
  // MOVE RIGHT
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    analogWrite(ENA2, 255);
    analogWrite(ENB2, 255);

    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_A2, HIGH);
    digitalWrite(MOTOR_B1, LOW);
    digitalWrite(MOTOR_B2, HIGH);
    digitalWrite(MOTOR_A3, HIGH);
    digitalWrite(MOTOR_A4, LOW);
    digitalWrite(MOTOR_B3, HIGH);
    digitalWrite(MOTOR_B4, LOW);
}
void left_turn(){
  // MOVE LEFT
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    analogWrite(ENA2, 255);
    analogWrite(ENB2, 255);

    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_A2, LOW);
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, LOW);
    digitalWrite(MOTOR_A3, LOW);
    digitalWrite(MOTOR_A4, HIGH);
    digitalWrite(MOTOR_B3, LOW);
    digitalWrite(MOTOR_B4, HIGH);
}
void loop() {
  int rightValue = analogRead(RIGHT);
  int leftValue = analogRead(LEFT);
  int centerValue = analogRead(CENTER);
  int betweenValue = analogRead(BETWEEN);
  int rightOfCenterValue = analogRead(RIGHT_OF_CENTER);
  int leftOfCenterValue = analogRead(LEFT_OF_CENTER);

  if (rightValue <= 35 && leftValue <= 35) {
    move_forward();
  } else if (rightValue <= 35 && leftValue > 35) {
    right_turn();
  } else if (rightValue > 35 && leftValue <= 35) {
    left_turn();
  } else if (centerValue <= 35 || betweenValue <= 35 ||
             rightOfCenterValue <= 35 || leftOfCenterValue <= 35) {
    // ALIGN WITH CENTER, BETWEEN, RIGHT_OF_CENTER, OR LEFT_OF_CENTER SENSOR
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);
    analogWrite(ENA2, 100);
    analogWrite(ENB2, 100);

    if (centerValue <= 35) {
      // If the center sensor detects the line, move left
      digitalWrite(MOTOR_A1, HIGH);
      digitalWrite(MOTOR_A2, LOW);
      digitalWrite(MOTOR_B1, LOW);
      digitalWrite(MOTOR_B2, HIGH);
      digitalWrite(MOTOR_A3, HIGH);
      digitalWrite(MOTOR_A4, LOW);
      digitalWrite(MOTOR_B3, HIGH);
      digitalWrite(MOTOR_B4, LOW);
    } else if (betweenValue <= 35) {
      // If the between sensor detects the line, move right
      digitalWrite(MOTOR_A1, LOW);
      digitalWrite(MOTOR_A2, HIGH);
      digitalWrite(MOTOR_B1, LOW);
      digitalWrite(MOTOR_B2, HIGH);
      digitalWrite(MOTOR_A3, LOW);
      digitalWrite(MOTOR_A4, HIGH);
      digitalWrite(MOTOR_B3, LOW);
      digitalWrite(MOTOR_B4, HIGH);
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
        analogWrite(ENA2, 0);
        analogWrite(ENB2, 0);
        isExploring = false;
      } else {
        // Make a U-turn
        analogWrite(ENA, 255);
        analogWrite(ENB, 255);
        analogWrite(ENA2, 255);
        analogWrite(ENB2, 255);

        digitalWrite(MOTOR_A1, LOW);
        digitalWrite(MOTOR_A2, HIGH);
        digitalWrite(MOTOR_B1, LOW);
        digitalWrite(MOTOR_B2, HIGH);
        digitalWrite(MOTOR_A3, LOW);
        digitalWrite(MOTOR_A4, HIGH);
        digitalWrite(MOTOR_B3, LOW);
        digitalWrite(MOTOR_B4, HIGH);
        delay(1000);  // Adjust the delay for the U-turn
        isExploring = false;  // Stop exploring
      }
    }
    // Continue exploring by making a turn and set isExploring to true
  }
}
