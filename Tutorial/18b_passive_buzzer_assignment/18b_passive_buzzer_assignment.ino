int buzzPin = 8;
int potVal;
int potPin = A1;
int toneVal;

void setup() {
  pinMode(buzzPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  potVal = analogRead(potPin);
  toneVal = (9940./1023.) * potVal + 60;

  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(toneVal);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(toneVal);
}