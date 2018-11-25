int lineFollowSensor0 = A1;
int lineFollowSensor1 = A2;
int lineFollowSensor2 = A3;
int lineFollowSensor3 = A4;
int lineFollowSensor4 = A5;

int STBY = 10; //standby

//Motor A
int PotA = 6; //Speed control
int MA1 = 9; //Direction
int MA2 = 8; //Direction

//Motor B
int PotB = 11; //Speed control
int MB1 = 12; //Direction
int MB2 = 2; //Direction
int LFSensor[5] = { 0, 0, 0, 0, 0};
int Position = 0;

float VelMax = 150;
float VelMed = VelMax*0.39;
float VelMin = VelMax*0.05;

float Kp = 0.13;
float Kd = 0.24;
int erro = 0;
float vel=0;
float P = 0;
float D = 0;
float previousErro;
float PD = 0;

unsigned long tempo=0;

void setup () {
  Serial.begin(9600);
  pinMode(PotA, OUTPUT);
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);

  pinMode(PotB, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
  delay(2000);

}
void loop () {
  tempo=millis();

  LFSensor[1] = analogRead(lineFollowSensor1);
  if (LFSensor [1] < 600) {
    LFSensor[1] = 1;
  } else {
    LFSensor[1] = 0;
  }
  LFSensor[2] = analogRead(lineFollowSensor2);

  if (LFSensor [2] < 600) {
    LFSensor[2] = 1;
  } else {
    LFSensor[2] = 0;
  }
  LFSensor[3] = analogRead(lineFollowSensor3);

  if (LFSensor [3] < 600) {
    LFSensor[3] = 1;
  } else {
    LFSensor[3] = 0;
  }
  LFSensor[0] = analogRead(lineFollowSensor0);

  if (LFSensor [0] < 600) {
    LFSensor[0] = 1;
  } else {
    LFSensor[0] = 0;
  }
  LFSensor[4] = analogRead(lineFollowSensor4);

  if (LFSensor [4] < 600) {
    LFSensor[4] = 1;
  } else {
    LFSensor[4] = 0;
  }
  
  Position = (((LFSensor[0]*0)+(LFSensor[1]*1000)+(LFSensor[2]*2000)+(LFSensor[3]*3000)+(LFSensor[4]*4000))/((LFSensor[0])+(LFSensor[1])+(LFSensor[2])+(LFSensor[3])+(LFSensor[4])));
  Serial.println(Position);

  if(Position == 2000){
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
    analogWrite(PotA, VelMax);
    analogWrite(PotB, VelMax);
  }

   else if(Position == 1000){
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
    analogWrite(PotA, VelMed);
    analogWrite(PotB, VelMax);
  }

   else if(Position == 3000){
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
    analogWrite(PotA, VelMax);
    analogWrite(PotB, VelMed);
  }
   else if(Position == 4000){
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
    analogWrite(PotA, VelMax);
    analogWrite(PotB, VelMin);
  }
   else if(Position == 0){
    digitalWrite(MA1, HIGH);
    digitalWrite(MA2, LOW);
    digitalWrite(MB1, LOW);
    digitalWrite(MB2, HIGH);
    analogWrite(PotA, VelMin);
    analogWrite(PotB, VelMax);
  }

  if (tempo>=25200){

  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PotA, 0);
  analogWrite(PotB, 0);
  delay(20000);
  }
}
