int incomingByte = 0;
int sum = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    incomingByte = Serial.parseInt();
    sum += incomingByte;
    Serial.print("Suma: ");
    Serial.println(sum);
  }
}
