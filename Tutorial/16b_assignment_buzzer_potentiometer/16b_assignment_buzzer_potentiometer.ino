// When value above 1000, buzz. If below, don't.
int buzzPin = 9;
int potPin = A0;
int potVal;
int myPause = 100;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(buzzPin, OUTPUT);
pinMode(potPin, INPUT);
}

void loop() {
potVal = analogRead(potPin);
Serial.println(potVal);
delay(myPause);

if (potVal > 1000) {
  digitalWrite(buzzPin, HIGH);
} else {
  digitalWrite(buzzPin, LOW);
}
}