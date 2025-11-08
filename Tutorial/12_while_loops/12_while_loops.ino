int i;
int pause = 500;
int smallP = 250;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  i = 1;
  delay(pause);
  // put your main code here, to run repeatedly:
  while (i <= 10) {
    Serial.println(i);
    delay(smallP);
    i++;
  }
}
