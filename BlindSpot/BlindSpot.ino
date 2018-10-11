
int lineFollowSensor1 = A2;
int lineFollowSensor2 = A3;
int lineFollowSensor3 = A4;


int STBY = 10; //standby

//Motor A
int PotA = 6; //Speed control
int MA1 = 9; //Direction
int MA2 = 8; //Direction

//Motor B
int PotB = 11; //Speed control
int MB1 = 12; //Direction
int MB2 = 2; //Direction
float velb=0;
int LFSensor[5] = {0, 0, 0, 0, 0};
int Position = 0;

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
  if (LFSensor [1] < 800) {
    LFSensor[1] = 1;
  } else {
    LFSensor[1] = 0;
  }
  LFSensor[2] = analogRead(lineFollowSensor2);

  if (LFSensor [2] < 800) {
    LFSensor[2] = 1;
  } else {
    LFSensor[2] = 0;
  }
  LFSensor[3] = analogRead(lineFollowSensor3);

  if (LFSensor [3] < 800) {
    LFSensor[3] = 1;
  } else {
    LFSensor[3] = 0;
  }

  Position = (((LFSensor[1]*0)+(LFSensor[2]*1000)+(LFSensor[3]*2000))/((LFSensor[1])+(LFSensor[2])+(LFSensor[3])));
  //Serial.print("   ");
    //Serial.print(LFSensor[0]);
    //Serial.print("   ");
    //Serial.print(LFSensor[1]);
    //Serial.print("   ");
    //Serial.print(LFSensor[2]);
    //Serial.print("   ");
    //Serial.print(LFSensor[3]);
    //Serial.print("   ");
    //Serial.println(LFSensor[4]);
  

  erro = Position-1000;
   //Serial.print("Erro");
   //Serial.println(erro);
  P = erro;
  D = erro - previousErro;
  previousErro = erro;


  PD = ((P * Kp) + (D * Kd));
  vel= 200+PD; // velocidade base do motor direito
velb=200-PD;   // velocidade base do motor esquerdo


  if (vel > 150) {
    vel = 150; // velocidade maxima do motor direito
  }
  if (velb > 150) {
    velb = 150; // velocidad maxima do motor esquerdo
  }
 // Serial.print("velDireita:  ");
  // Serial.print(vel);
  // Serial.print("velEsquerda:  ");
  // Serial.print(velb);
  // Serial.println();

  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
 
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  
  analogWrite(PotA, vel);
  analogWrite(PotB, velb);

if (tempo>=83000){

  digitalWrite(MA1, HIGH);
  digitalWrite(MA2, LOW);
  digitalWrite(MB1, LOW);
  digitalWrite(MB2, HIGH);
  analogWrite(PotA, 0);
  analogWrite(PotB, 0);
  delay(20000);
}

}
