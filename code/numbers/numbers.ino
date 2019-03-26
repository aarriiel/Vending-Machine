// slave_receiver.ino 
// Refer to the "master_sender" example for use with this 
#include <Wire.h> 
#define digit1 12 
#define digit2 9 
#define digit3 8 
#define aa 11 
#define bb 7 
#define cc 5 
#define dd 3 
#define ee 2 
#define ff 10 
#define gg 6 
#define dp 4 
int money=0; 
int ten=0; //calculate the tens
int hon=0; //calculate the hundreds
int k=0; 
const int SLAVE_ADDRESS = 1; 
int incomingByte = 0; 
const byte segs_data[11]={B01111110, B00110000, B01101101, B01111001, B00110011, B01011011, B01011111, 
B01110000, B01111111, B01110011, B00000001} ; 
const byte seg_pins[8]={gg,ff,ee,dd,cc,bb,aa,dp}; 
const byte digit_pins[3]={digit1,digit2,digit3}; 
void LightChar(byte digit, byte index, boolean dot) 
{ 
// digit = 0, 1, 2 
// index = 0..10 

byte segments = segs_data[index]; 
if (dot) segments |= B10000000; 

// select digit 
for ( byte i=0; i<3; i++) 
{ 
// common anode, set output to HIGH to select digit what you want, the other digits must be set to LOW 
// common cathode, set output to LOW to select digit what you want, the other digits must be set to HIGH 

if (i==digit) digitalWrite(digit_pins[i], HIGH); 
else digitalWrite(digit_pins[i], LOW); 
} 

// according char data, light each segments on digit 
for ( byte i=0; i<8; i++) 
{ 
// common anode, set output to LOW to light up LED, HIGH to off LED 
// common cathode, set output to HIGH to light up LED, LOW to off LED 

if ((segments & B00000001) == 1) digitalWrite(seg_pins[i], LOW); 
else digitalWrite(seg_pins[i], HIGH); 
segments >>=1; 
} 


} 
void setup() { 
Wire.begin(SLAVE_ADDRESS); // join I2C bus as a slave with address 1 
Wire.onReceive(receiveEvent); // register event 
pinMode(digit1, OUTPUT); 
pinMode(digit2, OUTPUT); 
pinMode(digit3, OUTPUT); 
pinMode(aa, OUTPUT); 
pinMode(bb, OUTPUT); 
pinMode(cc, OUTPUT); 
pinMode(dd, OUTPUT); 
pinMode(ee, OUTPUT); 
pinMode(ff, OUTPUT); 
pinMode(gg, OUTPUT); 
pinMode(dp, OUTPUT); 
Serial.begin(9600); 
} 

void loop() { 
LightChar(0, hon, false); //light the hundreds
delay(10); 
LightChar(1, ten, false); //light the tens
delay(10); 
LightChar(2, 0, false); //the ones is always zero because our goods are always 10 dollars.
delay(10); 

} 

void receiveEvent(int howMany) 
{ 
while (Wire.available()) //receive the money from another arduino
{ 
// receive one byte from Master 
  incomingByte = Wire.read(); 
  money=incomingByte; 
  Serial.println(money); //check the value
  ten=money%10; 
  hon=money/10; 
  LightChar(0, hon, false); 
  delay(10); 
  LightChar(1, ten, false); 
  delay(10); 
  LightChar(2, 0, false); 
  delay(10); 
} 
}
