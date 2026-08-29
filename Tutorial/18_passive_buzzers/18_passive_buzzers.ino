int buzzPin = 8;
int buzzTime1 = 1;
int buzzTime2 = 300;

void setup() {
  pinMode(buzzPin, OUTPUT);

}

void loop() {
  digitalWrite(buzzPin, HIGH);
  delayMicroseconds(buzzTime2);
  digitalWrite(buzzPin, LOW);
  delayMicroseconds(buzzTime2);

}
