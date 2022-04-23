int Wnumber;
int Lnumber;
void setup() {
  // put your setup code here, to run once:
  //Czerwony
  pinMode(4, OUTPUT);
  //Zielony
  pinMode(5, OUTPUT);
  //Niebieski
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  //Lnumber = random(-50,50);
  //Serial.println(Lnumber);
}

void loop() {
  // put your  code here, to run repeatedly:
//  delay(1000);
  if (Serial.available() > 0)
  {
    Lnumber = Serial.parseInt();
    Wnumber = Serial.parseInt();
    Serial.println(Lnumber);
    Serial.println(Wnumber);
    if (Lnumber < 2)
    {
      Lnumber = 2;
    }
    for(int i = Lnumber; i < Wnumber; i++)
    {
      boolean isFirst = true;
        for(int j=2; j < i; j++)
        {
          if (i % j == 0)
          {
            isFirst = false;
          }
        }
      if (isFirst == true)
      {
        Serial.println(i);
      }
    }
//      Wnumber = Serial.parseInt();
//      if (Wnumber == Lnumber)
//      {
//        digitalWrite(5, HIGH);
//        digitalWrite(6, LOW);
//        digitalWrite(4, LOW);
//      }
//      else if (abs(Wnumber - Lnumber) <= 10)
//      {
//        digitalWrite(6, HIGH);
//        digitalWrite(5, LOW);
//        digitalWrite(4, LOW);
//      }
//      else if (abs(Wnumber - Lnumber) > 10)
//      {
//        digitalWrite(4, HIGH);
//        digitalWrite(6, LOW);
//        digitalWrite(5, LOW);
//      }
//    color = Serial.read();
//    if (color == 'r')
//    {
//      digitalWrite(4, HIGH);
//    }
//    if (color == 'g')
//    {
//      digitalWrite(5, HIGH);
//    }
//    if (color == 'b')
//    {
//      digitalWrite(6, HIGH);
//    }
//    if (color == 'e')
//    {
//      digitalWrite(6, LOW);
//      digitalWrite(5, LOW);
//      digitalWrite(4, LOW);
//    }
    
//    if (color == 'rg')
//    {
//      digitalWrite(6, LOW);
//      digitalWrite(5, HIGH);
//      digitalWrite(4, HIGH);
//    }
//    if (color == 'rb' || color == 'br')
//    {
//      digitalWrite(6, HIGH);
//      digitalWrite(5, LOW);
//      digitalWrite(4, HIGH);
//    }
//    if (color == 'bg')
//    {
//      digitalWrite(6, HIGH);
//      digitalWrite(5, HIGH);
//      digitalWrite(4, LOW);
//    }
//    if (color == 'rgb' || color == 'rbg' || color == 'bgr' || color == 'brg' || color == 'grb' || color == 'gbr')
//    {
//      digitalWrite(6, HIGH);
//      digitalWrite(5, HIGH);
//      digitalWrite(4, HIGH);
//    }
  }
}
