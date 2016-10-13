#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <utility/Adafruit_MS_PWMServoDriver.h>
#include <Encoder.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(1);
Encoder flag_encoder(2, 4);
Encoder motor_encoder(3, 5);

const float kP = -.03;
const int max_speed = 20, min_speed = 10;
const float flag_to_motor = 16 * (3200.0 / 360.0);
const int meander_step = 20;
const int meander_interval = 2000;
long current_target;
unsigned long last_meander = millis();

void setup() {
  Serial.begin(9600);
  AFMS.begin();
}

long meander(long flag_ticks) {
  long meander_output = flag_ticks;
  float r = random(0, 100) / 100.0;
  if (r < 0.2) {
    meander_output += random(0 , meander_step);
  }
  else if (r < 0.4) {
    meander_output -= random(0 , meander_step);
  }


  return meander_output;
}

void loop() {
  // read the potentiometer
  long flag_ticks = flag_encoder.read();
  long current_motor_ticks = -motor_encoder.read();

  unsigned long now = millis();
  if (now - last_meander > meander_interval) {
    current_target = meander(flag_ticks);
    last_meander = now;
  }


  long target_motor_ticks = flag_to_motor * current_target;

  int output = kP * (current_motor_ticks - target_motor_ticks);

  output = min(output, max_speed);
  output = max(output, -max_speed);

  if (output > min_speed) {
    motor->run(FORWARD);
    motor->setSpeed(output);
  }
  else if (output < -min_speed) {
    motor->setSpeed(-output);
    motor->run(BACKWARD);
  }
  else {
    motor->run(RELEASE);
  }
}
