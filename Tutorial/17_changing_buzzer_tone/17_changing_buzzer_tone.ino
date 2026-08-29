int buzzPin = 8;
int dt1 = 2;
int dt2 = 4;
int counter;
void setup() {
  // put your setup code here, to run once:
pinMode(buzzPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
for (counter = 1; counter <= 100; counter++) {
  digitalWrite(buzzPin, HIGH);
  delay(dt1);
  digitalWrite(buzzPin, LOW);
  delay(dt1);
}
for (counter = 1; counter <= 100; counter++) {
  digitalWrite(buzzPin, HIGH);
  delay(dt2);
  digitalWrite(buzzPin, LOW);
  delay(dt2);
}
}
