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
int LF = 10;
int LB = 11;
int RF = 12;
int RB = 13;
void setup() {
  // put your setup code here, to run once:
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
  analogWrite(LF, 255);
  analogWrite(LB, 255);
  analogWrite(RF, 255);
  analogWrite(RB, 255);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
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
    else if ((distancel < 5) or (distancer < 5))
    {
      if (lastwall == "l")
      {
        left();
      }
      else
      {
        right();
      }
    }
    else if (distances < 5)
    { stp();
      if (lastwall = "l")
      {
        right();
      }
      else
      {
        left();
      }
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
  return dist3;
}

int forward()
{
  analogWrite(LF, 255);
  analogWrite(LB, 0);
  analogWrite(RF, 255);
  analogWrite(RB, 0);
}
int left()
{
  analogWrite(LF, 0);
  analogWrite(LB, 255);
  analogWrite(RF, 255);
  analogWrite(RB, 0);
  delay(1000);
  analogWrite(LF, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 0);
}
int right()
{
  analogWrite(LF, 255);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 255);
  delay(1000);
  analogWrite(LF, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 0);
}
int stp()
{
  analogWrite(LF, 0);
  analogWrite(LB, 255);
  analogWrite(RF, 0);
  analogWrite(RB, 255);
  delay(500);
  analogWrite(LF, 0);
  analogWrite(LB, 0);
  analogWrite(RF, 0);
  analogWrite(RB, 0);
}
