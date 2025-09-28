int redLED=11;
int pip=75;
int pop=800;
int pause=500;
int bigPause=1000;

void setup() {
  // SOS program
pinMode(redLED, OUTPUT);
}

void loop() {
  // delay:
delay(bigPause);

// S
delay(pause);
digitalWrite(redLED, HIGH);
delay(pip);
digitalWrite(redLED, LOW);
delay(pause);
digitalWrite(redLED, HIGH);
delay(pip);
digitalWrite(redLED, LOW);
delay(pause);
digitalWrite(redLED, HIGH);
delay(pip);
digitalWrite(redLED, LOW);
// O
delay(pause);
digitalWrite(redLED, HIGH);
delay(pop);
digitalWrite(redLED, LOW);
delay(pause);
digitalWrite(redLED, HIGH);
delay(pop);
digitalWrite(redLED, LOW);
delay(pause);
digitalWrite(redLED, HIGH);
delay(pop);
digitalWrite(redLED, LOW);
// S
delay(pause);
digitalWrite(redLED, HIGH);
delay(pip);
digitalWrite(redLED, LOW);
delay(pause);
digitalWrite(redLED, HIGH);
delay(pip);
digitalWrite(redLED, LOW);
delay(pause);
digitalWrite(redLED, HIGH);
delay(pip);
digitalWrite(redLED, LOW);
}

