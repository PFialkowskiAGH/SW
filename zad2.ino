volatile int counter = 0;
const long interval = 1000;
unsigned long previousMillis = 0; 
#define interPin  2
#define pomPin 3
#define insertPin 12

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(interPin, INPUT_PULLUP);
  pinMode(insertPin, INPUT_PULLUP);
  pinMode(pomPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(interPin), resetCounter, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (millis() - previousMillis >= interval) 
  {
    // save the last time you blinked the LED
    previousMillis = millis();
    digitalWrite(7, (counter >> 0) & 1);
    digitalWrite(8, (counter >> 1) & 1);
    digitalWrite(9, (counter >> 2) & 1);
    digitalWrite(10, (counter >> 3) & 1);
    counter ++;
  }
  if (digitalRead(interPin) == LOW)
  {
    resetCounter();
  }
  if (digitalRead(insertPin) == LOW)
  {
          delay(300);

    setCounter();
  }
}

void resetCounter()
{
  counter = 0;
}

void setCounter()
{
  int pom = 0;
  counter = 0;
  while (pom < 4)
  {
    if (digitalRead(pomPin) == LOW)
    {
      delay(300);
      bitSet(counter, pom);
      pom++;
      digitalWrite(7, (counter >> 0) & 1);
      digitalWrite(8, (counter >> 1) & 1);
      digitalWrite(9, (counter >> 2) & 1);
      digitalWrite(10, (counter >> 3) & 1);
    }
    if (digitalRead(insertPin) == LOW)
    {
      delay(300);
      pom++;
      digitalWrite(7, (counter >> 0) & 1);
      digitalWrite(8, (counter >> 1) & 1);
      digitalWrite(9, (counter >> 2) & 1);
      digitalWrite(10, (counter >> 3) & 1);
    }
  }
}
