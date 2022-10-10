#include <stdio.h>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>


#define TIME_STEP 50
#define MAX_SPEED 6.28

using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();


  //distance sensor
  DistanceSensor *ds[2];
  char dsNames[2][10]  = {"dsL", "dsR"};
  for (int i = 0; i < 2; i++) {
  ds[i] = robot->getDistanceSensor(dsNames[i]);
  DistanceSensor *dsL = robot->getDistanceSensor("dsL");
  DistanceSensor *dsR = robot->getDistanceSensor("dsR");
    dsL->enable(TIME_STEP);
    dsR->enable(TIME_STEP);
  }

  //initialise motors
  Motor *wheels[2];
  char wheels_names[2][4]= {"wheel1", "wheel2"};
  Motor *leftMotor = robot->getMotor("wheel1");
  Motor *rightMotor = robot->getMotor("wheel2");
  for (int i = 0; i < 2; i++) {
  wheels[i] = robot->getMotor(wheels_names[i]);
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  leftMotor->setVelocity(1.0);
  rightMotor->setVelocity(1.0);
  }


  //obstacle avoidance step
  int ObstacleAvoidanceCounter = 0;
  while (robot->step(TIME_STEP) != -1) {
  double leftSpeed = 1.0;
  double rightSpeed = 1.0;

  double dsL_val = dsL ->getValue();
  double dsR_val = dsR ->getValue();

   //to get the distance sensor values/readings
   std::cout << "Distance Sensor left: " << dsL_val << std::endl;
   std::cout << "Distance Sensor right: " << dsR_val << std::endl;

    if (ObstacleAvoidanceCounter > 0) {
      ObstacleAvoidanceCounter--;
      else if (left_obstacle) {
      //turn right
      leftSpeed = 0.5 * MAX_SPEED;
      rightSpeed = -0.5 * MAX_SPEED;
      }

      else  {
       // turn left
      leftSpeed  = -0.5 * MAX_SPEED;
      rightSpeed = 0.5 * MAX_SPEED;

    leftMotor->setVelocity(leftSpeed);
    rightMotor->setVelocity(rightSpeed);
    }
  }

    else { // read sensor values
      for (int i = 0; i < 2; i++) {
        if (ds[i]->getValue() < 900.0)
        ObstacleAvoidanceCounter = 100;

      }
    }
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);

  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}
