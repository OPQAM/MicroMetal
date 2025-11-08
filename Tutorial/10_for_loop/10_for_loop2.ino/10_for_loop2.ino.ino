int red = 9;
int yell = 6;
int pause = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(yell, OUTPUT);
}

void loop() {
  for (int i = 0; i < 9; i++) {
    if (i <4) {
      digitalWrite(yell, HIGH);
      delay(pause);
      digitalWrite(yell, LOW);
      delay(pause);
    }
    else {
      digitalWrite(red, HIGH);
      delay(pause);
      digitalWrite(red, LOW);
      delay(pause);
    }
  }
}
