#include <Arduino.h>
#include "A4988.h"

#define MOTOR_STEPS 200 //定义步距角
#define RPM 10  //定义转速(r/min)
#define MICROSTEPS 16 //定义细分数

// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL 100
#define MOTOR_DECEL 100


#define X_DIR 55
#define X_STEP 54
#define X_EN 38
#define Z_DIR 48
#define Z_STEP 46
#define Z_EN 62



A4988 stepper(MOTOR_STEPS, Z_DIR, Z_STEP, Z_EN);
int counter = 0;


void setup() {
  // put your setup code here, to run once: i dont know what to do
  stepper.begin(RPM, MICROSTEPS);
  // stepper.begin(RPM);
  stepper.setEnableActiveState(LOW);
  stepper.enable();
  stepper.setSpeedProfile(stepper.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  Serial.begin(9600);
  Serial.println("Initialized");
  stepper.startMove(3200);
}

void loop() {
  // put your main code here, to run repeatedly:

  // delay(1000);
  // stepper.setMicrostep(16);  
  // stepper.startMove(320000);
  // stepper.move(MOTOR_STEPS*MICROSTEPS);
  // counter = counter + 2;
  // Serial.println(counter);
  // delay(1000);
  // stepper.rotate(360);
  // delay(1000);
  static int step = 0;
  unsigned wait_time = stepper.nextAction();
  if (wait_time){
      Serial.print("  step="); Serial.print(step++);
      Serial.print("  dt="); Serial.print(wait_time);
      Serial.print("  rpm="); Serial.print(stepper.getCurrentRPM());
      Serial.println();
  } else {
      stepper.disable();
      Serial.println("END");
      delay(3600000);
  }

} 
