#include<Servo.h>
Servo myservo; 
    int pos = 0;    // variable to store the servo position
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int mappedValue=map(sensorValue,0,1023,100,0);
    Serial.println(mappedValue);
  // print out the value you read:
  if (mappedValue>15)
  {
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   }
  delay(1000);
  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
   
  }
   else if(mappedValue>2 && mappedValue<15)
   {
     for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
     }
         delay(1000);

   for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   }
  }
  delay(100);        // delay in between reads for stability
}



 // create servo object to control a servo
// twelve servo objects can be created on most boards
