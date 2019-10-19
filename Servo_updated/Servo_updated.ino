#include <Servo.h>
Servo ser;
int pos=0;


int ang=0;
int x=0,y=0;

//wall follower
int trigpins = 4;
int echopins = 5;
float distances;
float durations;
float dist1;
int trigpinr = 6;
int echopinr = 7;
float distancer;
float durationr;
float dist2;
int trigpinl = 8;
int echopinl = 9;
float distancel;
float durationl;
float dist3;
char lastwall;
int LF = 22;
int LB = 23;
int RF = 24;
int RB = 25;
int REN=10;
int LEN=11;
//encoder

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
int lastLSB = 0;
void updateEncoder();
void updateEncoder2();


void setup() {
  ser.attach(12);

 Serial.begin (9600);
  
  // wall follower
  pinMode(trigpins, OUTPUT);
  pinMode(echopins, INPUT);
  pinMode(trigpinr, OUTPUT);
  pinMode(echopinr, INPUT);
  pinMode(trigpinl, OUTPUT);
  pinMode(echopinl, INPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  digitalWrite(LF, HIGH);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, HIGH);
  //Serial.begin(9600);

  //encoder

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

void loop() {

  Serial.println(x);
  Serial.println(y);

  x=x+(((encoderValue+encoderValue2)/100)*cos(ang));
  y=y+(((encoderValue+encoderValue2)/100)*sin(ang));
   
  distances = USs();
  distancer = USr();
  distancel = USl();

  if (distances > 5)
  {
    if ((distancel < 5) or (distancer < 5))
    {
      forward();
      if (distancel < 5)
      {
        lastwall = "l";
      }
      else
      {
        lastwall = "r";
      }
    }
    else if ((distancel > 5) or (distancer > 5))
    {  
      stp();
      if (lastwall == "l")
      {
        left();
      }
      else
      {
        right();
      }
    }}
    
    else if (distances < 5)
    { stp();
      
      //Serial.println("T")
      scan();
      
      
      if (lastwall = "l")
      {
        rights();
      }
      else
      {
        lefts();
      }
    }
  }

  
int USs()
{
  digitalWrite(trigpins, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpins, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpins, LOW);
  durations = pulseIn(echopins, HIGH);
  distances = 0.034 / 2 * (durations);
  dist1 = distances;
  return dist1;
}

int USr()
{
  digitalWrite(trigpinr, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpinr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinr, LOW);
  durationr = pulseIn(echopinr, HIGH);
  distancer = 0.034 / 2 * (durationr);
  dist2 = distancer;
  return dist2;
}

int USl()
{
  digitalWrite(trigpinl, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpinl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpinl, LOW);
  durationl = pulseIn(echopinl, HIGH);
  distancel = 0.034 / 2 * (durationl);
  dist3 = distancel;
  return dist3;
}

int forward()
{
  digitalWrite(LF, HIGH);
  digitalWrite(LB, 0);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, 0);
  analogWrite(LEN,  255);
  analogWrite(REN,  255);
}
int left()
{
  digitalWrite(LF, 0);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, 0);
    analogWrite(LEN,  255);
  analogWrite(REN,  255);
  delay(500);
  digitalWrite(LF, 0);
  digitalWrite(LB, 0);
  digitalWrite(RF, 0);
  digitalWrite(RB, 0);
    analogWrite(LEN,  255);
  analogWrite(REN,  255);
}

int lefts()
{
  digitalWrite(LF, 0);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, 0);
    analogWrite(LEN,  255);
  analogWrite(REN,  255);
  delay(1000);
  digitalWrite(LF, 0);
  digitalWrite(LB, 0);
  digitalWrite(RF, 0);
  digitalWrite(RB, 0);
    analogWrite(LEN,  255);
  analogWrite(REN,  255);
}

int right()
{
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
  delay(500);


digitalWrite(LF, LOW);
digitalWrite(LB, LOW);
digitalWrite(RF, LOW);
digitalWrite(RB, LOW);
}

int rights()
{
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
  delay(1000);


digitalWrite(LF, LOW);
digitalWrite(LB, LOW);
digitalWrite(RF, LOW);
digitalWrite(RB, LOW);
}

int stp()
{
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
  delay(500);
  digitalWrite(LF, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, LOW);
}

void scan()
{
  Serial.println('S');
   for (pos = 0; pos <= 90; pos++)
   { 
    ser.write(pos);      
    Serial.println(pos);        
    delay(60);                      
   }
    for (pos = 90; pos >= 0; pos--)
   { 
    ser.write(pos);      
    Serial.println(pos);        
    delay(60);                      
   }

}
//encoder
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
