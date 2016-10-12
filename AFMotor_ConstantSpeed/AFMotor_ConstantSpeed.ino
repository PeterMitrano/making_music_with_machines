#include <AccelStepper.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *motor = AFMS.getStepper(200, 2);

void forwardstep() {
  motor->onestep(FORWARD, DOUBLE);
}
void backwardstep() {  
  motor->onestep(BACKWARD, DOUBLE);
}

AccelStepper stepper(forwardstep, backwardstep); // use functions to step

void setup()
{  
   Serial.begin(9600);
   Serial.println("Stepper test!");
   AFMS.begin();
   motor->setSpeed(1);
   stepper.setSpeed(100);	
}

void loop()
{  
   stepper.runSpeed();
   
}
