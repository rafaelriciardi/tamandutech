
#define lineFollowSensor1 A2
#define lineFollowSensor2 A3
#define lineFollowSensor3 A4


#define STBY  10 //standby

//Motor A
#define PotA  6 //Speed control
#define MA1  9 //Direction
#define MA2  8 //Direction

//Motor B
#define PotB  11 //Speed control
#define MB1  12 //Direction
#define MB2  2 //Direction

#define velMax 80

int LFSensor[5] = {0, 0, 0, 0, 0};
int Position = 0;

float Kp = 0.13;
float Kd = 0.24;
int erro = 0;
float vel_A = 0;
float vel_B = 0;
float P = 0;
float D = 0;
float previousErro;
float PD = 0;
int mediaPB = 800;

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
  if (LFSensor [1] < mediaPB) {
    LFSensor[1] = 1;
  } else {
    LFSensor[1] = 0;
  }
  LFSensor[2] = analogRead(lineFollowSensor2);

  if (LFSensor [2] < mediaPB) {
    LFSensor[2] = 1;
  } else {
    LFSensor[2] = 0;
  }
  LFSensor[3] = analogRead(lineFollowSensor3);

  if (LFSensor [3] < mediaPB) {
    LFSensor[3] = 1;
  } else {
    LFSensor[3] = 0;
  }

  Position = (((LFSensor[1]*0)+(LFSensor[2]*1000)+(LFSensor[3]*2000))/((LFSensor[1])+(LFSensor[2])+(LFSensor[3])));
  Serial.print("   ");
  Serial.print(LFSensor[0]);
  Serial.print("   ");
  Serial.print(LFSensor[1]);
  Serial.print("   ");
  Serial.print(LFSensor[2]);
  Serial.print("   ");
  Serial.print(LFSensor[3]);
  Serial.print("   ");
  Serial.println(LFSensor[4]);
  

  erro = Position-1000;
   //Serial.print("Erro");
   //Serial.println(erro);
  P = erro;
  D = erro - previousErro;
  previousErro = erro;


  PD = ((P * Kp) + (D * Kd));
  vel_A = 200+PD; // velocidade base do motor direito
  vel_B = 200-PD;   // velocidade base do motor esquerdo


  if (vel_A > velMax) {
    vel_A = velMax; // velocidade maxima do motor direito
  }
  if (vel_B > velMax) {
    vel_B = velMax; // velocidad maxima do motor esquerdo
  }
  // Serial.print("velDireita:  ");
  // Serial.print(vel_A);
  // Serial.print("velEsquerda:  ");
  // Serial.print(vel_B);
  // Serial.println();

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
