#define lineFollowSensor1 A2
#define lineFollowSensor2 A3
#define lineFollowSensor3 A4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
 int data1 = analogRead(A4);
 int data2 = analogRead(A3);
 int data3 = analogRead(A2);

 Serial.print(data1);
 Serial.print("  ");
 Serial.print(data2);
 Serial.print("  ");
 Serial.println(data3);

}
