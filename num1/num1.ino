#include <Servo.h>

const int push1 = 2;
const int push2 = 3;
const int push3 = 4;

const int pot = A0;

const int IN1 = 9;
const int IN2 = 10;
const int ENA = 5;

const int IR = 11;
const int ledfire = 12;
const int buzz1 = 13;

const int ldr = A2;
const int led1 = A3;
const int led2 = A4;
const int led3 = A5;

const int trig = 7;
const int echo = 8;

const int ledi1 = 14;
const int ledi2 = 15;
const int ledi3 = 16;

const int trig2 = 17;
const int echo2 = 18;

int mode = 0;
bool last_push1 = false;
bool last_push2 = false;
bool last_push3 = false;

int human = 0;
bool personPresent = false;

Servo inyminy;
Servo potservo;

int getDistance();
int getDistance2();

void setup() {
  Serial.begin(9600);

  pinMode(push1, INPUT_PULLUP);
  pinMode(push2, INPUT_PULLUP);
  pinMode(push3, INPUT_PULLUP);

  inyminy.attach(5);
  potservo.attach(6);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IR, INPUT);
  pinMode(ledfire, OUTPUT);
  pinMode(buzz1, OUTPUT);

  pinMode(ldr, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(ledi1, OUTPUT);
  pinMode(ledi2, OUTPUT);
  pinMode(ledi3, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {
  if (digitalRead(push2) == LOW) {
    mode = 1;
    delay(200);
    if (digitalRead(push3) == LOW) {
      mode = 2;
      delay(200);
      if (digitalRead(push1) == LOW) {
        mode = 3;
        delay(200);
      }
    }
  }

  switch (mode) {
    case 1:
      last_push2 = !last_push2;
      mode = 0;
      break;
    case 2:
      last_push3 = !last_push3;
      mode = 0;
      break;
    case 3:
      last_push1 = !last_push1;
      inyminy.write(90);
      mode = 0;
      break;
  }

  int potval = analogRead(pot);
  int angle = map(potval, 0, 1023, 0, 180);
  potservo.write(angle);

  if (digitalRead(IR) == HIGH) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);
    
    digitalWrite(ledfire, HIGH);
    delay(200);
    digitalWrite(ledfire, LOW);
    
    tone(buzz1, 600);
    delay(200);
    noTone(buzz1);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }

  int ldrval = analogRead(ldr);
  int bright = map(ldrval, 0, 1023, 0, 255);

  if (ldrval < 400) {
    analogWrite(led1, 255);
    analogWrite(led2, 255);
    analogWrite(led3, 255);
  } else {
    analogWrite(led1, bright);
    analogWrite(led2, bright);
    analogWrite(led3, bright);
  }

  int distzz = getDistance();

  if (distzz > 20 && distzz < 40) {
    digitalWrite(ledi1, HIGH);
  } else {
    digitalWrite(ledi1, LOW);
  }

  if (distzz > 50 && distzz < 100) {
    digitalWrite(ledi2, HIGH);
  } else {
    digitalWrite(ledi2, LOW);
  }

  if (distzz > 110 && distzz < 150) {
    digitalWrite(ledi3, HIGH);
  } else {
    digitalWrite(ledi3, LOW);
  }

  int doorDist = getDistance2();

  if (doorDist > 10 && doorDist < 180) {
    if (!personPresent) {
      human++;
      personPresent = true;
      Serial.print("Person detected! Total in house: ");
      Serial.println(human);
    }
  } else if (doorDist >= 180 || doorDist == 0) {
    personPresent = false;
  }

  delay(50);
}

int getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 0;
  return duration * 0.03446 / 2.0;
}

int getDistance2() {
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  long duration2 = pulseIn(echo2, HIGH, 30000);
  if (duration2 == 0) return 0;
  return duration2 * 0.03446 / 2.0;
}
