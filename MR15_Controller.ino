/*
  CONTROLLER
  Control subsystem for MR15
  Handles vehicle steering, dynamic ballast and engine
*/

/* --- Libraries --- */
#include <DualVNH5019MotorShield.h>

/* --- Pins --- */
#define STEERING_POSITION_PIN 0 // Steering potentiometer
#define ACTUATOR_POSITION_PIN 1 // Actuator potentiometer
#define BALLAST_SPEED_PIN 2 // Ballast potentiometer
#define STOP_RELAY_PIN 2
#define REGULATOR_RELAY_PIN 3
#define STARTER_RELAY_PIN 4

/* --- Commands --- */
char C_KILL = '0';
char C_STANDBY = '1';
char C_IGNITION = '2';
char C_RUN = '3';

/* --- Objects --- */
DualVNH5019MotorShield MOTORS;

/* --- Constants --- */
const int BAUD = 9600;

/* --- Variables --- */
volatile int STEERING_POSITION = 0;
volatile int ACTUATOR_POSITION = 0;
volatile int STEERING_SPEED = 100;

/* --- Character Buffer --- */
char COMMAND;

/* --- Boolean States --- */
boolean STOP_RELAY = false;
boolean STARTER_RELAY = false;
boolean REGULATOR_RELAY = false;

/* --- Setup --- */
void setup() {
  Serial.begin(BAUD);
}

/* --- Loop --- */
void loop() {
  
  // Attempt to get command
  COMMAND = Serial.read();  
 
  // Base Action on received command 
  if (char(COMMAND) == char(C_KILL)) {
    Serial.println("...");
    delay(500);
    digitalWrite(STOP_RELAY_PIN, LOW);
    digitalWrite(STARTER_RELAY_PIN, LOW);
    digitalWrite(REGULATOR_RELAY_PIN, LOW);
  }
  else if (COMMAND == C_STANDBY) {
    Serial.println("*click*");
    delay(500);
    digitalWrite(STOP_RELAY_PIN, LOW);
    digitalWrite(STARTER_RELAY_PIN, LOW);
    digitalWrite(REGULATOR_RELAY_PIN, LOW);
  }
  else if (COMMAND == C_IGNITION) {
    Serial.println("HRNGrrgrgrg");
    delay(500);
    digitalWrite(STOP_RELAY_PIN, LOW);
    digitalWrite(STARTER_RELAY_PIN, LOW);
    digitalWrite(REGULATOR_RELAY_PIN, LOW);
  }
  else if (COMMAND == C_RUN) {
    Serial.println("Vrrrrrrrrroom");
    delay(500);
    digitalWrite(STOP_RELAY_PIN, LOW);
    digitalWrite(STARTER_RELAY_PIN, LOW);
    digitalWrite(REGULATOR_RELAY_PIN, LOW);
  }
  else {
    // This is what the controller will do if a string 
    // is not parsed properly or if it is no longer
    // receiving serial commands.
    Serial.println("*crickets*");
    delay(1);
  }
  
  // Handle steering
  STEERING_POSITION = analogRead(STEERING_POSITION_PIN);
  ACTUATOR_POSITION = analogRead(ACTUATOR_POSITION_PIN);
  if (ACTUATOR_POSITION > STEERING_POSITION) {
    MOTORS.setM1Speed(STEERING_SPEED);
  }
  else if (ACTUATOR_POSITION < STEERING_POSITION) {
    MOTORS.setM1Speed(-STEERING_SPEED);
  }
  else {
    MOTORS.setM1Speed(0);
  }
  
}
