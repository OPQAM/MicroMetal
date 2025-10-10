int myPin=9;
int pause=500;
int bigPause=1000;

int maxIntensity=255;  // 5 volts
int noLight=0;         // 0 volts
int midIntensity=100;
int lowIntensity=20;
int highIntensity=170;


void setup() {
  // for analog write use the '~' pins
pinMode(myPin, OUTPUT);
}

void loop() {
  // From 0 to low, to high to max:

delay(bigPause);

analogWrite(myPin, noLight);
delay(pause);

analogWrite(myPin, lowIntensity);
delay(pause);

analogWrite(myPin, midIntensity);
delay(pause);

analogWrite(myPin, highIntensity);
delay(pause);

analogWrite(myPin, maxIntensity);
}
