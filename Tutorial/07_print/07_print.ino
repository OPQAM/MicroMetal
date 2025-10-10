int j=1;
int pause=750;
String myString="j = ";
int x=3;
int y=7;
int z;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print(myString);
Serial.println(j);
z=x+y;

Serial.print(z);
j=j+1;
delay(pause);
}
