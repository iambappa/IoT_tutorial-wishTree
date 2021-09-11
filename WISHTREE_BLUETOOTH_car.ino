#include <SoftwareSerial.h>
#include <AFMotor.h>
SoftwareSerial bluetooth(10, 9); // RX | TX arduino side
char B;
AF_DCMotor leftmotor(4);
AF_DCMotor rightmotor(3);
int LEDPIN = 13;
void setup()
{
  bluetooth.begin(9600);  //Default Baud for comm, it may be different for your Module.
  Serial.begin(115200);
  Serial.println("WISETHINGZ BLUETOOTH CAR");
  pinMode(LEDPIN, OUTPUT);
}
void loop()
{
  if (bluetooth.available())
  {
    B = bluetooth.read();
    //    Serial.print("MESSAGE RECIEVED-");
    Serial.println(B);

    if (B == 'F')
    {Serial.println("forward moving");
      leftmotor.run(FORWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(FORWARD);
      rightmotor.setSpeed(254);
    }  
    if (B == 'B')
    {Serial.println("backward moving");
      leftmotor.run(BACKWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(BACKWARD);
      rightmotor.setSpeed(254);
    }
    if (B == 'R')
    {Serial.println("right moving");
      leftmotor.run(FORWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(BACKWARD);
      rightmotor.setSpeed(254);
    }
    if (B == 'L')
    {Serial.println("left moving");
      leftmotor.run(BACKWARD);
      leftmotor.setSpeed(254);
      rightmotor.run(FORWARD);
      rightmotor.setSpeed(254);
    }
    if (B == 'S')
    {Serial.println("stop moving");
      leftmotor.run(RELEASE);
      rightmotor.run(RELEASE);
    }
  }
}
