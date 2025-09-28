void setup() {
  // put your setup code here, to run once:
pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(13, HIGH);
delay(20);
digitalWrite(13, LOW);
delay(20);
}
// Much lower than this and the eye cannot see that the lights are blinking