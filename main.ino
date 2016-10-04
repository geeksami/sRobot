/*
  This is a self project to practise my knowledge in Arduino 
  Copyright : EZZEROUALI Sami 2016
*/

// This library will provide us the communication trough the bluetooth link
#include <SoftwareSerial.h>

// Definition of Rx,Tx pins of bluetooth shield
SoftwareSerial HC06(11,10);
const char DOUT_LED = 2;

// Definition of motor's relay command
const int m1=6;
const int m2=7;

// This variable will contain the message sent by smartphone
String messageRecu;


void droite(){
    // Here is the function to turn right
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
}
void gauche(){
    // Here is the function to turn left
    digitalWrite(m1,LOW);
    digitalWrite(m2,HIGH);
}

void devant(){
    // Here is the function to go ahead
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
}
void mStop(){
    // Here is the function to Stop the robot
    digitalWrite(m1,HIGH);
    digitalWrite(m2,HIGH);
}


void setup() {
  // this serial communication is juste for test
  Serial.begin(9600);
  
  // Starting the communication trough Bluetooth shield HC06
  HC06.begin(9600);  
  
  pinMode(DOUT_LED, OUTPUT);
  digitalWrite(DOUT_LED, LOW);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);

}
 
void loop()
{
  // Starting the programme with a mStop then we are sure the robot is stoped
  mStop();
  
  
    while(HC06.available())
    // here we concatenate the recevied message
    {
      delay(3);
      char c = HC06.read();
      messageRecu += c;
    }
    
    
    if (messageRecu.length() >0)
    // when the concatenation is done we do a switch to make a decision 
    {
      // message conversion from char to int
      int cmd=messageRecu.toInt();
      
      // here the test to see if we really received the message in the Arduino monitor
      Serial.println(cmd);
      
      
      switch(cmd){
        case 0:
          mStop();
        break;
        case 1:
          devant();
          delay(250);
          mStop();
        break;
        case 2:
          mStop();
        break;
        case 3:
          gauche();
          delay(250);
          mStop();
        break;
        case 4:
          droite();
          delay(250);
          mStop();
        break;
        default:
          Serial.println("error bleutooth msg");
        break;
        
        }
      
      // elemination of the content of message and waiting for the next one
      messageRecu="";
    }
}
