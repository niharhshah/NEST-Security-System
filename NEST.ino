#include <LiquidCrystal.h>
#include <Keypad.h>
#include "nest_gsm.h"

#define door 11
#define buzz 12
#define ir 52

String password = "0258";
String temppassword = "";

const byte ROWS = 4; //four rows
const byte COLS = 3;//three columns
bool a;

char keys[ROWS][COLS] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(53, 51, 49, 47, 45, 43);

void setup()
{
  pinMode(ir, INPUT);
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(door, OUTPUT);
  pinMode(buzz, OUTPUT);
  digitalWrite(door, HIGH);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("NEST SECURITY SYSTEM");
  lcd.setCursor(0, 2);
  lcd.print("Enter Password : ");
  lcd.setCursor(0, 3);
}

void loop()
{
  char  keypressed = keypad.getKey();

  if (keypressed)
  {
    Serial.println(keypressed);

    if (keypressed != NO_KEY)
    {

      if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' || keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' || keypressed == '8' || keypressed == '9' )
      {
        temppassword += keypressed;
        lcd.print("*");

      }
      if (keypressed == '*')
      {
        if ( temppassword == password)
        {
          lcd.setCursor(0, 0);
          lcd.print("NEST SECURITY SYSTEM");
          lcd.setCursor(0, 2);
          lcd.print("WELCOME TO NEST!");
          lcd.setCursor(0, 3);
          lcd.print("                    ");
          digitalWrite(door, LOW);
          delay(1500);
          digitalWrite(door, HIGH);
          delay(500);
        }

        else
        {
          digitalWrite(buzz, HIGH);
          callme();
          send_message();
        }
      }
      if (keypressed == '#')
      {
        temppassword = "";
        digitalWrite(buzz, LOW);
        hangup();
        a = 0;
        //lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("NEST SECURITY SYSTEM");
        lcd.setCursor(0, 2);
        lcd.print("Enter Password : ");
        lcd.setCursor(0, 3);
        lcd.print("                    ");
        lcd.setCursor(0, 3);
      }
    }
  }

  bool IR = digitalRead(ir);
  if (IR == 0)
  {
    a = 1;
  }
  else if (a == 1)
  {
    digitalWrite(buzz, HIGH);
    callme();
    send_message();
  }
  else if (a == 0)
  {
    digitalWrite(buzz, LOW);
  }
}

