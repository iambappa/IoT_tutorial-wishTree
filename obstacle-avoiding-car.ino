#include <AFMotor.h>
int trigPin = 4;    // Trigger d5
int echoPin = 3;    // Echo  d6
long duration, cm;
AF_DCMotor leftmotor(4);
AF_DCMotor rightmotor(3);

void setup()
{

  Serial.begin (115200);
  Serial.println("WISETHINGZ ULTRASONIC CAR");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  delay(5000);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = duration * (0.0160);   // change values according to your required calibration
  Serial.println(cm);

  if (cm >= 20) {
    leftmotor.run(FORWARD);
    leftmotor.setSpeed(254);
    rightmotor.run(FORWARD);
    rightmotor.setSpeed(254);
  }
  else if (cm <= 20)
  {
    leftmotor.run(RELEASE);
    rightmotor.run(RELEASE);
    delay(1000);
    leftmotor.run(BACKWARD);
    leftmotor.setSpeed(254);
    rightmotor.run(BACKWARD);
    rightmotor.setSpeed(254);
    delay(500);
    leftmotor.run(BACKWARD);
    leftmotor.setSpeed(254);
    rightmotor.run(FORWARD);
    rightmotor.setSpeed(254);
    delay(500);
    leftmotor.run(RELEASE);
    rightmotor.run(RELEASE);
    delay(1000);
  }


}
