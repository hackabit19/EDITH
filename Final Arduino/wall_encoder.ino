#include<math.h>
#include<Servo.h>
int trigpin = 4;
int Rechopin = 7;
int Sechopin = 5;
int LF = 22;
int LB = 23;
int RF = 30;
int RB = 31;
int LEN = 10;
int REN = 11;
float Sdist;
float Rdist;
float Stime;
float Rtime;
float v;

int leftencoderPin1 = 2;
int leftencoderPin2 = 3;
int rightencoderPin1 = 18;
int rightencoderPin2 = 19;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile int lastEncoded2 = 0;
volatile long encoderValue2 = 0;

long lastencoderValue = 0;
long lastencoderValue2 = 0;


int lastMSB = 0;
float d=0;
int lastLSB = 0;
int angle;
int x;
int y;
Servo S;
int pos=90;





void setup(){
  pinMode(trigpin, OUTPUT);
  pinMode(Sechopin, INPUT);
  pinMode(Rechopin, INPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(REN, OUTPUT);
  analogWrite(LEN, 255);
  analogWrite(REN, 255);
  S.attach(12);
  Serial.begin (9600);

  pinMode(leftencoderPin1, INPUT); 
  pinMode(leftencoderPin2, INPUT);
  pinMode(rightencoderPin1, INPUT); 
  pinMode(rightencoderPin2, INPUT);

  digitalWrite(leftencoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(leftencoderPin2, HIGH); 
   digitalWrite(rightencoderPin1, HIGH); 
  digitalWrite(rightencoderPin2, HIGH); 

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3) 
  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), updateEncoder2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(19), updateEncoder2, CHANGE);
  
  }

void loop(){
  
  d=((encoderValue+encoderValue2)/164);
  x=d*cos(angle);
  y=(d-x)*sin(angle);
  Serial.println(pos);
  Serial.println(x);
  Serial.println(y);
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  Stime = pulseIn(Sechopin, HIGH);
  Rtime = pulseIn(Rechopin, HIGH);
  Sdist = (0.034/2) *(Stime);
  Rdist = (0.034/2) * (Rtime);
  if (Sdist<20)
  {
   if (Rdist < 15)
    { 
     v = millis();
     while(millis()-v <= 1000)
     {
     digitalWrite(LF, LOW);//left turn
     digitalWrite(LB, HIGH);
     digitalWrite(RF, HIGH);
     digitalWrite(RB, LOW);  
      }

     digitalWrite(LF, LOW);//stop
     digitalWrite(LB, LOW);
     digitalWrite(RF, LOW);
     digitalWrite(RB, LOW);  
    

     
     angle=angle+90;
     
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    S.write(pos);              // tell servo to go to position in variable 'pos'
    delay(250);  
    Serial.println(pos);
    Serial.println(x);
    Serial.println(y);}

    
     digitalWrite(LF, HIGH);
     digitalWrite(LB, LOW);
     digitalWrite(RF, HIGH);
     digitalWrite(RB, LOW);
    }
    
    
         
    else
    {
      x = 0;
     v = millis();
     while(millis()-v <= 1000){
     digitalWrite(LF, HIGH);
     digitalWrite(LB, LOW);
     digitalWrite(RF, LOW);
     digitalWrite(RB, HIGH);
     }
     digitalWrite(LF, HIGH);
     digitalWrite(LB, LOW);
     digitalWrite(RF, HIGH);
     digitalWrite(RB, LOW);
     
    }  
  }
 
     
  }
   void updateEncoder(){
  int MSB = digitalRead(leftencoderPin1); 
  int LSB = digitalRead(leftencoderPin2); 

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //update encovalue
}


void updateEncoder2()//SIMILAR TO PREVIOUS FUNC
{
  int MSB2 = digitalRead(rightencoderPin1); 
  int LSB2 = digitalRead(rightencoderPin2); 

  int encoded2 = (MSB2 << 1) |LSB2; 
  int sum2  = (lastEncoded2 << 2) | encoded2; //adding it to the previous encoded value

  if(sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011) encoderValue2 ++;
  if(sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000) encoderValue2 --;

  lastEncoded2 = encoded2; //updTE enco val2
}
  
 
