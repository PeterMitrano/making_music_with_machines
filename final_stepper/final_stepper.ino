#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>
#include <Encoder.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor = AFMS.getStepper(200, 2);
Encoder encoder(2, 3);

const int potPin = A0;
const long deg_to_step = 2750 / 360;

long current_steps = 0;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  motor->setSpeed(1);
}

void loop() {
  // read the potentiometer
  long pot_angle_deg = encoder.read();

  long target_steps = deg_to_step * pot_angle_deg;
  
  
  if (target_steps > current_steps) {
    motor->onestep(FORWARD, DOUBLE);
    current_steps++;
  }
  else if  (target_steps < current_steps) {
    motor->onestep(BACKWARD, DOUBLE);
    current_steps--;
  }
}

