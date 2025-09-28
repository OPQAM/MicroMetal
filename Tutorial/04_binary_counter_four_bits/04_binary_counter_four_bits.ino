// Using 4 bits, write numbers 0 to 15 (4 LEDs)

int bitOne=9;
int bitTwo=10;
int bitThree=11;
int bitFour=12;

int pause=500;

void setup() {
  // put your setup code here, to run once:
pinMode(bitOne, OUTPUT);
pinMode(bitTwo, OUTPUT);
pinMode(bitThree, OUTPUT);
pinMode(bitFour, OUTPUT);
}

void loop() {
  // Delay
delay(pause);

  // 0:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, LOW);

delay(pause);

  // 1:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 2:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, LOW);

delay(pause);

  // 3:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 4:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, LOW);

delay(pause);

  // 5:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 6:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, LOW);

delay(pause);

  // 7:
digitalWrite(bitOne, LOW);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 8:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, LOW);

delay(pause);

  // 9:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 10:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, LOW);

delay(pause);

  // 11:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, LOW);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 12:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, LOW);

delay(pause);

  // 13:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, LOW);
digitalWrite(bitFour, HIGH);

delay(pause);

  // 14:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, LOW);

delay(pause);

  // 15:
digitalWrite(bitOne, HIGH);
digitalWrite(bitTwo, HIGH);
digitalWrite(bitThree, HIGH);
digitalWrite(bitFour, HIGH);
}
