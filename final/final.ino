#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>
#include <Encoder.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(1);
Encoder flag_encoder(2, 4);
Encoder motor_encoder(3, 5);

const float kP = -.2;
const int max_speed = 200;
const int potPin = A0;
const float flag_to_motor = 16 * (3200.0 / 360.0);

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  motor->setSpeed(20); // 0-255
}

void loop() {
  // read the potentiometer
  long flag_ticks = flag_encoder.read();
  long current_motor_ticks = -motor_encoder.read();

  long target_motor_ticks = flag_to_motor * flag_ticks;

  Serial.print(current_motor_ticks);
  Serial.print(" ");
  Serial.print(target_motor_ticks);
  Serial.print(" ");

  int output = kP * (current_motor_ticks - target_motor_ticks);

  output = min(output, max_speed);
  output = max(output, -max_speed);

  Serial.println(output);

  if (output > 4) {
    motor->run(FORWARD);
     motor->setSpeed(output);
  }
  else if (output < -4) {
    motor->setSpeed(-output);
    motor->run(BACKWARD);
  }
  else {
    motor->run(RELEASE);
  }
}

