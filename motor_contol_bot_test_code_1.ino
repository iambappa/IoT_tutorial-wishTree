#include <AFMotor.h>

AF_DCMotor leftmotor(4);
AF_DCMotor rightmotor(3);

void setup() {
  Serial.begin(115200);
  Serial.println("WISETHINGZ CAR");
}

void loop()
{

  //  MOVING FORWARD
  leftmotor.run(FORWARD);
  rightmotor.run(FORWARD);
  leftmotor.setSpeed(254);
  rightmotor.setSpeed(254);
  delay(500);
  leftmotor.run(RELEASE);
  rightmotor.run(RELEASE);
  delay(1000);

  //  MOVING BACKWARD
  leftmotor.run(BACKWARD);
  rightmotor.run(BACKWARD);
  leftmotor.setSpeed(254);
  rightmotor.setSpeed(254);
  delay(500);
  leftmotor.run(RELEASE);
  rightmotor.run(RELEASE);
  delay(1000);

  // TURNING RIGHT
  leftmotor.run(FORWARD);
  rightmotor.run(BACKWARD);
  leftmotor.setSpeed(254);
  rightmotor.setSpeed(254);
  delay(500);
  leftmotor.run(RELEASE);
  rightmotor.run(RELEASE);
  delay(1000);

  // TURNING LEFT
  leftmotor.run(BACKWARD);
  rightmotor.run(FORWARD);
  leftmotor.setSpeed(254);
  rightmotor.setSpeed(254);
  delay(1000);
  leftmotor.run(RELEASE);
  rightmotor.run(RELEASE);
  delay(1000);

 
 // RETURNING TO INITIAL POSITION
  leftmotor.run(FORWARD);
  rightmotor.run(BACKWARD);
  leftmotor.setSpeed(254);
  rightmotor.setSpeed(254);
  delay(500);
  leftmotor.run(RELEASE);
  rightmotor.run(RELEASE);
  delay(1000);

}
