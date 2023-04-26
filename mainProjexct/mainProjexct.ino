#include <SoftwareSerial.h>
#include<Servo.h>
#define RX 2
#define TX 3
#define dht_apin 11 // Analog Pin sensor is connected to
Servo myservo; 
//Start :
//define the pins that we will use for the first ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin1 8                                  //pin number 9 in arduino MEGA2560
#define echoPin1 9                                   // we'll use this pin to read the signal from the first sensor
//#define LED_first_ping 22                            // I/O digital or analogique ( we will use pin 22 to command an LED (on/off))
//----------------------------------------------------------------------------------------------------------------------
//define the pins that we will use for the second ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin2 10
#define echoPin2 11
//#define LED_second_ping 24
//----------------------------------------------------------------------------------------------------------------------

//used variables
//----------------------------------------------------------------------------------------------------------------------
long duration, distance, UltraSensor1, UltraSensor2; //we'll use these variable to store and generate data
int pos = 0;
char data;
String SerialData="";

String AP = "Realme 9 Pro SE";       // AP NAME
String PASS = "12345677"; // AP PASSWORD
String API = "JYMFGN4WL88T1BBG";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;
  int count=0;
SoftwareSerial esp8266(RX,TX); 
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
  // setup pins first sensor
pinMode(trigPin1, OUTPUT);                        // from where we will transmit the ultrasonic wave
pinMode(echoPin1, INPUT);                         //from where we will read the reflected wave 

//setup pins second sensor
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {

  // opening/closing segragation 
   int sensorValue = analogRead(A0);
  int mappedValue=map(sensorValue,0,1023,100,0);
  Serial.print("Moisture Present: ");
    Serial.print(mappedValue);
Serial.println("%");  
delay(1000);  
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
   count=count+1;
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
   count=count+1;
  }      // delay in readings 
  Serial.print("Count= ");
Serial.println(count);
  //wifi module command start
  if(count==5)
  {
 String getData = "GET /update?api_key="+ API +"&field1="+getDistance1()+"&field2="+getDistance2();
 sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  delay(3000);
 sendCommand("AT+CIPSEND=0,"+String(getData.length()+10),4,">");
 esp8266.println(getData);
 delay(1000);
 countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
 count=0;
 }                                            // wifi module end
}


int getDistance1(){

   SonarSensor(trigPin1, echoPin1);              // look bellow to find the difinition of the SonarSensor function
   UltraSensor1 = distance;     
   Serial.print("distance measured by the first sensor: ");
   Serial.print(UltraSensor1);
  Serial.println(" cm");  
  return int(UltraSensor1); 
  
}


int getDistance2(){

   SonarSensor(trigPin2,echoPin2);               // call the SonarSensor function again with the second sensor pins
  UltraSensor2 = distance;
  Serial.print("distance measured by the second sensor: ");
Serial.print(UltraSensor2);
Serial.println(" cm"); 
    return int(UltraSensor2); 

}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }

 void SonarSensor(int trigPinSensor,int echoPinSensor)//it takes the trigPIN and the echoPIN 
{
  //START SonarSensor FUNCTION
  //generate the ultrasonic wave
//---------------------------------------------------------------------------------------------------------------------- 
digitalWrite(trigPinSensor, LOW);// put trigpin LOW 
delayMicroseconds(2);// wait 2 microseconds
digitalWrite(trigPinSensor, HIGH);// switch trigpin HIGH
delayMicroseconds(10); // wait 10 microseconds
digitalWrite(trigPinSensor, LOW);// turn it LOW again
//----------------------------------------------------------------------------------------------------------------------

//read the distance
//----------------------------------------------------------------------------------------------------------------------
duration = pulseIn(echoPinSensor, HIGH);//pulseIn funtion will return the time on how much the configured pin remain the level HIGH or LOW; in this case it will return how much time echoPinSensor stay HIGH
distance= (duration/2) / 29.1; // first we have to divide the duration by two  
}// END SonarSensor FUNCTION


 