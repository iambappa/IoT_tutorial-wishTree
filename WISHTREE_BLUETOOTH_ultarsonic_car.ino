#include <SoftwareSerial.h>
#include <AFMotor.h>
SoftwareSerial bluetooth(10, 9); // RX | TX arduino side
char B;
AF_DCMotor leftmotor(4);
AF_DCMotor rightmotor(3);
int LEDPIN = 13;
int trigPin = 4;    // Trigger d5
int echoPin = 3;    // Echo  d6
long duration, cm;
void setup()
{
  bluetooth.begin(9600);  //Default Baud for comm, it may be different for your Module.
  Serial.begin(115200);
  Serial.println("WISETHINGZ BLUETOOTH CAR");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(LEDPIN, OUTPUT);
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


  if (bluetooth.available())
  {
    B = bluetooth.read();
    //    Serial.print("MESSAGE RECIEVED-");
    Serial.println(B);
    if (cm >= 20)
    {
      if (B == 'F')
      {
        Serial.println("forward moving");
        leftmotor.run(FORWARD);
        leftmotor.setSpeed(254);
        rightmotor.run(FORWARD);
        rightmotor.setSpeed(254);
      }
    }
    else if (cm <= 20)
    {
      Serial.print("OBJECT AHEAD CAN'T MOVE FORWARD--");
      Serial.println(cm);
      bluetooth.println("OBJECT AHEAD CAN'T MOVE FORWARD--");
      bluetooth.println(cm);
    }

    if (B == 'B')
    { Serial.println("backward moving");
      leftmotor.run(BACKWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(BACKWARD);
      rightmotor.setSpeed(254);
    }
    if (B == 'R')
    { Serial.println("right moving");
      leftmotor.run(FORWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(BACKWARD);
      rightmotor.setSpeed(254);
    }
    if (B == 'L')
    { Serial.println("left moving");
      leftmotor.run(BACKWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(FORWARD);
      rightmotor.setSpeed(254);
    }
    if (B == 'S')
    { Serial.println("stop moving");
      leftmotor.run(RELEASE);
      rightmotor.run(RELEASE);
    }
  }
}
