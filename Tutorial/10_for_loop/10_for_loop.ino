// link yellos LED 4 times and then blink red LED 6 times
int red = 9;
int yell = 6;
int pause = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(yell, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(yell, HIGH);
    delay(pause);
    digitalWrite(yell, LOW);
    delay(pause);
  }
  
  for (int i = 0; i < 6; i++) {
    digitalWrite(red, HIGH);
    delay(pause);
    digitalWrite(red, LOW);
    delay(pause);
  }
}
