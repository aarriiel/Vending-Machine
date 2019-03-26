// master_sender.ino
// Refer to the "slave_receiver" example for use with this
#include <Wire.h>
#include <Servo.h> 
//Three servomotors
Servo myservoA;
Servo myservoB;
Servo myservoC;

//
int m = 1;
int n = 1;
int y = 1;
//A,B,C are counters about our goods. 
int A = 1;
int B = 1;
int C = 1;
const int SLAVE_ADDRESS = 1;
int incomingByte = 0; //store the photoresistor value
int money=0; //store the money

int photocellPin = 2; // photoresistor connect to analog pin 2
int photocellVal = 0; // photoresistor variable

void setup() {  
  Wire.begin();         // join I2C bus as a Master
  Serial.begin(9600);   // open the serial port, the race is 9600bps (Bits Per Second)
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  myservoA.attach(8, 500, 2400); //connect pin 9, and fix the range (500-2400)
  myservoB.attach(9, 500, 2400);
  myservoC.attach(10, 500, 2400);
  myservoA.write(0); //set the default degree with 0
  myservoB.write(0); 
  myservoC.write(0); 
  delay(3000); //wait 3000ms 
}

void loop() {
  if(A>0) //while goods not zero
    digitalWrite(7,HIGH); //light up the light which connect pin 7
  else
    digitalWrite(7,LOW);  //turn off the light which connect pin 7
  if(B>0)
    digitalWrite(6,HIGH);
  else
    digitalWrite(6,LOW);
  if(C>0)
    digitalWrite(5,HIGH);
  else
    digitalWrite(5,LOW);
  incomingByte = analogRead(photocellPin);//read the photoresistor value
  // Serial.println(incomingByte); 
  // send the received data to slave
  Wire.beginTransmission(SLAVE_ADDRESS); //set the pass address
  if(incomingByte<30){ //if the photoresistor value less than 30, means the money is through the machine
    money++;
    delay(700);
  }
  Serial.println(incomingByte); //test the photoresistor value
  Wire.write(money); //pass the money value to another arduino 
  Wire.endTransmission();
  if(money>0){ //only still have money can use the machine
    if(A>0){
      if(m % 2 ==1){ //m is calculate the motor's direction
        if(digitalRead(11)  == HIGH){
          for(int i = 500; i <= 2400; i+=100){
            myservoA.writeMicroseconds(i); // move the servomotor
            delay(50);
          } 
        m++;
        money--;
        A--;
        } 
      }
      else{
        if(digitalRead(11)  == LOW){
          for(int i = 2400; i >= 500; i-=100){
            myservoA.writeMicroseconds(i); // move the servomotor
            delay(50);
          }
          m++;
          money--;
          A--;
        } 
      }
    }
    if(B>0){
      if(n % 2 ==1){
        if(digitalRead(12)  == LOW){
          for(int i = 500; i <= 2400; i+=100){
            myservoB.writeMicroseconds(i); // move the servomotor
            delay(50);
          } 
          n++;
          money--;
          B--;
        }
      }
      else{
        if(digitalRead(12)  == HIGH){
          for(int i = 2400; i >= 500; i-=100){
            myservoB.writeMicroseconds(i); //  move the servomotor
            delay(50);
          }
          n++;
          money--;
          B--;
        }
      }
    }
    if(C>0){
      if(y % 2 ==1){
        if(digitalRead(13)  == LOW){
          for(int i = 500; i <= 2400; i+=100){
            myservoC.writeMicroseconds(i); //  move the servomotor
            delay(50);
          } 
          y++;
          money--;
          C--;
        }
      }
      else{
        if(digitalRead(13)  == HIGH){
          for(int i = 2400; i >= 500; i-=100){
            myservoC.writeMicroseconds(i); //  move the servomotor
            delay(50);
          }
          y++;
          money--;
          C--;
        }
      }
    }
  }
}
