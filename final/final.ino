#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>
#include <Encoder.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor = AFMS.getStepper(200, 2);
Encoder encoder(5, 6);

const int potPin = A0;

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  motor->setSpeed(100);
}

void loop() {
  // read the potentiometer
  int pot_angle_deg = encoder.read() * 4.0;

  // set stepper
  step_to_angle(pot_angle_deg);
}

int current_deg = 0;

void step_to_angle(int deg) {
  int diff = deg - current_deg;
  if (diff > 180) {
    diff -= 360;
  }
  if (diff < -180) {
    diff += 360;
  }

  if (diff >= 0) {
    motor->step(abs(diff), FORWARD);
  }
  else {
    motor->step(abs(diff), BACKWARD);
  }
}

