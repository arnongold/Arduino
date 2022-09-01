
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 

int delay_ms = 5;
int buzzer_pin = 9;
int analogValue;
int previousValue;
int WPM;
int unit;
const int dit = 1;
const int da = 2;
bool transmittingDit = false;
bool transmittingDa = false;
bool transmittingPause = false;
unsigned long transmittionStartedAt;
unsigned long transmittionEndedAt;
unsigned long lastClickAt;
int transmitNext;

String letter = "";
String line = "";
bool spacePrinted = false;

void setup() {
    pinMode(4,INPUT_PULLUP);
    pinMode(5,INPUT_PULLUP);
    pinMode(7,INPUT_PULLUP);
    
    pinMode(buzzer_pin, OUTPUT);
    Serial.begin(9600);

  lcd.init();              
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Morse Keyer");
  lcd.setCursor(3,1);
  lcd.print("by 4X4RD");
  delay(2000);
  lcd.clear();
  
  lastClickAt = millis();
  letter = "";
  transmitNext = 0;
}

void loop() {
    getWPM();
    readKey();
    TransmitMorse();

    checkClear();
}

void TransmitMorse()
{
  if (transmittingPause) {
    if (millis() > transmittionStartedAt + unit) {
        transmittingPause = false;
        transmittionEndedAt = millis();
    }
  } else if (transmittingDit){
    if (millis() > transmittionStartedAt + unit)
    {
        analogWrite(buzzer_pin, 0);
        transmittingDit = false;
        transmittingPause = true;
        transmittionStartedAt = millis();
        transmitNext = 0;
    }
  } else if (transmittingDa) {
    if (millis() > transmittionStartedAt + (unit * 3))
    {
        analogWrite(buzzer_pin, 0);
        transmittingDa = false;
        transmittingPause = true;
        transmittionStartedAt = millis();
        transmitNext = 0;
    }
  } else {
      if (transmitNext != 0) {
        switch (transmitNext){
          case dit:
            analogWrite(buzzer_pin, 50);
            transmittingDit = true;
            transmittionStartedAt = millis();
            break;
          case da:
            analogWrite(buzzer_pin, 50);
            transmittingDa = true;
            transmittionStartedAt = millis();
            break;
        }
      }
   }
}

void getWPM()
{
    analogValue = analogRead(A7);
    WPM = 5 + (analogValue / 33);
    if (previousValue != WPM)
    {
      lcd.setCursor(0,1);
      lcd.print("WPM:");
      lcd.setCursor(4,1);
      lcd.print("     ");
      lcd.setCursor(4,1);
      lcd.print(WPM);
      previousValue = WPM;
      unit = 1.2/WPM*1000;
      Serial.print(analogValue);
      Serial.print("  Unit:" );
      Serial.print(unit);
      Serial.print("  WPM:" );
      Serial.print(WPM);
      Serial.print("\n");
    }
}

void readKey()
{
    if (transmitNext != 0)
      return;
    if (digitalRead(4) == LOW)
    {
      if (millis() > lastClickAt + unit)
      {
        transmitNext = dit;
        lastClickAt = millis();
        letter = letter + dit;
      } 
    }
    
    if (digitalRead(5) == LOW)
    {
      if (millis() > lastClickAt + unit)
      {
        transmitNext = da;
        lastClickAt = millis();
        letter = letter + da;
      } 
    }

    if ((millis() > lastClickAt + (unit * 2)) && letter != "") {
      decodeLetter();
    }

    if (millis() > max(transmittionEndedAt,transmittionStartedAt) + (unit * 6)) {
      printSpace();
    }
}

void decodeLetter()
{
  Serial.print(letter + "\n");

  switch(letter.length()){
    case 1:
      if (letter == "1") printLetter("E");
      else printLetter("T");
      break;
    case 2:
      if (letter == "12") printLetter("A");
      else if (letter == "21") printLetter("N");
      else if (letter == "11") printLetter("I");
      else if (letter == "22") printLetter("M");
      break;
    case 3:
      if (letter == "111") printLetter("S");
      else if (letter == "112") printLetter("U");
      else if (letter == "121") printLetter("R");
      else if (letter == "122") printLetter("W");
      else if (letter == "211") printLetter("D");
      else if (letter == "212") printLetter("K");
      else if (letter == "221") printLetter("G");
      else if (letter == "222") printLetter("O");
      break;
    case 4:
      if (letter == "1111") printLetter("H");
      else if (letter == "1112") printLetter("V");
      else if (letter == "1121") printLetter("F");
      else if (letter == "1211") printLetter("L");
      else if (letter == "1221") printLetter("P");
      else if (letter == "1222") printLetter("J");
      else if (letter == "2111") printLetter("B");
      else if (letter == "2112") printLetter("X");
      else if (letter == "2121") printLetter("C");
      else if (letter == "2122") printLetter("Y");
      else if (letter == "2211") printLetter("Z");
      else if (letter == "2212") printLetter("Q");
      else if (letter == "2221") printLetter(".");
      else if (letter == "2222") printLetter("-");
      break;
    case 5:
      if (letter == "12222") printLetter("1");
      else if (letter == "11222") printLetter("2");
      else if (letter == "11122") printLetter("3");
      else if (letter == "11112") printLetter("4");
      else if (letter == "11111") printLetter("5");
      else if (letter == "21111") printLetter("6");
      else if (letter == "22111") printLetter("7");
      else if (letter == "22211") printLetter("8");
      else if (letter == "22221") printLetter("9");
      else if (letter == "22222") printLetter("0");
      break;
  }
  
  letter = "";
  spacePrinted = false;
}

void printSpace()
{
  if (!spacePrinted) {    
    printLetter(" ");
    spacePrinted = true;
  }
}
void checkClear()
{
  if (digitalRead(7) == LOW)
    clearLine();
}

void clearLine()
{
  line = "";
  lcd.setCursor(0,0);
  lcd.print("                ");
}
void printLetter(String newLetter)
{
  line = line + newLetter;
    if (line.length() > 16)
    line = line.substring(1);
  lcd.setCursor(0,0);
  lcd.print(line);

}
