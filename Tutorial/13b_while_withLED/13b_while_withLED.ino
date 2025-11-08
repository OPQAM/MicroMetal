int numBlinks;
String msg="How many blinks you want:";
int i;
int blinkTime=500;
int redPin=12;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(redPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(msg);
while (Serial.available()==0) {
}
numBlinks=Serial.parseInt();
Serial.println(numBlinks);
for (i=1;i<=numBlinks;i++) {
  digitalWrite(redPin,HIGH);
  delay(blinkTime);
  digitalWrite(redPin,LOW);
  delay(blinkTime);
}
}

// NOTES:
// Issue was that the LED was very weak.
// Troubleshooting: we forgot to do the pinMode. Now on.