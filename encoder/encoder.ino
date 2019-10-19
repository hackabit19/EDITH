int outputAL = 2;
int outputBL = 3;
int outputAR = 4;
int outputBR = 5;
int ALstate;
int BLstate;
int ALlaststate;
int Lcounter=0;
int ARstate;
int BRstate;
int ARlaststate;
int Rcounter=0;


void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT);
pinMode(3,INPUT);
Serial.begin(9600);
ALlaststate = digitalRead(outputAL);
}

void loop() {
  // put your main code here, to run repeatedly:
ALstate=digitalRead(outputAL);
BLstate=digitalRead(outputBL);
ARstate=digitalRead(outputAR);
BRstate=digitalRead(outputBR);
if (ALlaststate!= ALstate)
 {
  LM(ALlaststate, ALstate, BLstate);
 }
if (ARlaststate!= ARstate)
 {
  RM(ARlaststate, ARstate, BRstate);
 }
 ALlaststate = ALstate;
 ARlaststate = ARstate;
}

int LM(int ALlaststate, int ALstate, int BLstate)
{
 if (digitalRead(outputBL) != ALstate) { 
       Lcounter --;
     } else {
       Lcounter ++;    }
  Serial.print("LPosition");
  Serial.println(Lcounter);
  delayMicroseconds(5);
}

int RM(int ARlaststate, int ARstate, int BRstate)
{
 if (ARstate!= BRstate)
  {
   Rcounter++;
  }
  else
  {
   Rcounter--;
  }
  //Serial.print("RPosition");
  //Serial.println(Rcounter);
  delayMicroseconds(10);
}
