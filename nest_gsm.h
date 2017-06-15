#include <arduino.h>

void callme()
{
  Serial.println("TRAITOR!");
  Serial1.println("ATD+919033482137;\r");
  delay(20000);
  Serial1.println("ATH\r");
}

void hangup()
{
  Serial1.println("ATH\r");
}

void send_message()
{
  Serial.println("Message_TRAITOR!");
  Serial1.println("AT+CMGF=1");
  delay(1000);
  Serial1.println("AT+CMGS=\"+919033482137\"");
  delay(1000);
  Serial1.println("Someone Has Just Tried To Get Into Your NEST, Please Contact Your Neighbours To Check The Status Of Your Nest! From : NEST - A Place To Live!");
  delay(100);
  Serial1.println((char)26);
  delay(1000);
}


