#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;

int val1 = 0, val2 = 0, val3 = 0, count = 0;
int stor_1[10], stor_2[10], stor_3[10];

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(4, LOW);
  s1.attach(9);
  s2.attach(10);
  s3.attach(11);
  Serial.begin(9600);
}

void storeVal() {
  if (count == 10) {
    Serial.println("STEPS FULL");
    return;
  }
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  delay(500);
  stor_1[count] = map(val1, 0, 1023, 0, 180);
  stor_2[count] = map(val2, 0, 1023, 0, 180);
  stor_3[count] = map(val3, 0, 1023, 0, 180);
  delay(500);
  count++;
  digitalWrite(4, LOW);
  digitalWrite(3, HIGH);
}

void record() {
  val1 = analogRead(A1);
  val2 = analogRead(A2);
  val3 = analogRead(A3);
  s1.write(map(val1, 0, 1023, 0, 180));
  s2.write(map(val2, 0, 1023, 0, 180));
  s3.write(map(val3, 0, 1023, 0, 180));
}

void movement() {
  while (1) {
    for (int i = 0; i < count; i++) {
      s1.write(stor_1[i]);
      s2.write(stor_2[i]);
      s3.write(stor_3[i]);
      delay(1000);
    }
  }
}

void loop() {
  record();
  Serial.print(digitalRead(6));
  Serial.println(digitalRead(7));
  if (digitalRead(7) == 1) {
    storeVal();
  }
  delay(50);
  if (digitalRead(6) == 1) {
    movement();
  }
}