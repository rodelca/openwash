 #include <LiquidCrystal.h>
#include <EEPROM.h>
// LCD shield use digital pins from our Arduino board.
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// these values are for out signal for our mach3 or cnc control board, remember aduino outs 0 and 5 Volts
const int pintimer =  2;
const int pinamarillo =  3;
const int pinrojo =  11;
const int pinbomba =  12;
// finish pinouts you can use a Led to test.

int lavado_heavy = 14, enjuage_heavy = 8,  lavado_normal = 10, enjuage_normal = 5, lavado_ligero = 7, enjuage_ligero = 4, centrifugado = 8, exprimir = 4, ButtonVoltage = 0, ButtonPressed = 0, keystatus=0;
unsigned long timestamp = 0;


// this variables are defined by dfrobot shield for push button numbers
#define BUTTON_SELECT 5
#define BUTTON_LEFT 4
#define BUTTON_DOWN 3
#define BUTTON_UP 2
#define BUTTON_RIGHT 1
#define BUTTON_NONE 0


// here we have a function for return numbers into LCD screen with correct format.
void printnum(int n)
{

 for(int i = n;  i > 0; i--)
 {
 delay(1000);  
 lcd.setCursor(0, 10);
 lcd.print("T=");
  if (i < 1000)
  {
    lcd.print(" ");
    if (i < 100)
    {
      lcd.print(" ");
      if (i < 10)
      {
        lcd.print(" ");
      }
    }
  }
 lcd.print(i);
 }
}

void lavar(int n)
{
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("lavando");
      // outputs start
      digitalWrite(pinamarillo, LOW);
      digitalWrite(pinrojo, HIGH);
      delay(30);
      digitalWrite(pintimer, LOW);
      printnum(n);
      digitalWrite(pintimer, HIGH);
      delay(2000);
}

void llenar(int n)
{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Llenando");
      // outputs start
      digitalWrite(pinbomba, LOW);
      printnum(n);
      digitalWrite(pinbomba, HIGH);
      delay(2000);
}


void centrifugar(int n)
{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("exprimiendo");
      // outputs start
      digitalWrite(pinamarillo, HIGH);
      digitalWrite(pinrojo, LOW);
      delay(30);
      digitalWrite(pintimer, LOW);
      printnum(n);
      digitalWrite(pintimer, HIGH);
      delay(2000);
}

void centrifugar2(int n)
{
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("centrifugando");
      // water start
      digitalWrite(pinbomba, LOW);
      digitalWrite(pinamarillo, HIGH);
      digitalWrite(pinrojo, LOW);
      delay(30);
      digitalWrite(pintimer, LOW);
      printnum(50);
      digitalWrite(pinbomba, HIGH);
      printnum(n);
      digitalWrite(pintimer, HIGH);
      delay(2000);
}
void setup()
{
  pinMode(pinrojo, OUTPUT);
  pinMode(pinamarillo, OUTPUT);
  pinMode(pintimer, OUTPUT);
  pinMode(pinbomba, OUTPUT);
  lcd.clear();
  lcd.begin(16, 2);
  digitalWrite(pinrojo, HIGH);
  digitalWrite(pinamarillo, HIGH);
  digitalWrite(pinbomba, HIGH);
  digitalWrite(pintimer, HIGH);
}

void loop()
{
  unsigned long currentMillis = millis();
 ButtonVoltage = analogRead(0); 
  if (ButtonVoltage > 800) ButtonPressed = BUTTON_NONE;
  else if (ButtonVoltage > 610) ButtonPressed = BUTTON_SELECT;
  else if (ButtonVoltage > 400) ButtonPressed = BUTTON_LEFT;
  else if (ButtonVoltage > 220) ButtonPressed = BUTTON_DOWN;
  else if (ButtonVoltage > 80) ButtonPressed = BUTTON_UP;
  else ButtonPressed = BUTTON_RIGHT;
 
  if (ButtonPressed != BUTTON_NONE)
  {
    switch (ButtonPressed)
    {
      case BUTTON_SELECT:
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Carga Pesada");
      delay(5000);
      llenar(360);
      lavar(600);
     centrifugar(120);
      llenar(360);
      lavar(480);
      centrifugar(120);
      centrifugar2(500);
      lcd.clear();
        break;
      case BUTTON_LEFT:
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Carga ligera");
      delay(5000);
      llenar(200);
      lavar(600);
     centrifugar(120);
      llenar(200);
      lavar(480);
      centrifugar(120);
      centrifugar2(500);
      lcd.clear();
        break;
      case BUTTON_DOWN:
      centrifugar(120);
      centrifugar(600);
      lcd.clear();
        break;
      case BUTTON_UP:
        break;
      case BUTTON_RIGHT:
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Carga ligera");
      delay(5000);
      llenar(10);
      lavar(10);
     centrifugar(10);
      llenar(10);
      lavar(10);
      centrifugar(10);
      centrifugar2(10);
      lcd.clear();
        break;
      case BUTTON_NONE:
        break;
    }
  }
  else
    {
      digitalWrite(pinrojo, HIGH);
      digitalWrite(pinamarillo, HIGH);
      digitalWrite(pinbomba, HIGH);
      digitalWrite(pintimer, HIGH);
      lcd.setCursor(0, 0); 
      lcd.print("press key");
      delay(10);
    }

}
