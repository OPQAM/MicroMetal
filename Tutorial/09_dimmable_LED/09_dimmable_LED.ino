int potPin=A0;
int redPin=9;
int potVal;
float LEDVal;
int pause=100;

void setup() {
  // put your setup code here, to run once:
pinMode(potPin, INPUT);
pinMode(redPin, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
potVal=analogRead(potPin);
LEDVal=(255./1023.)*potVal;
analogWrite(redPin,LEDVal);
Serial.println(LEDVal);
delay(pause);
}
