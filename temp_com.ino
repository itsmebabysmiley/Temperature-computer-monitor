/*
Temperature computer monitor Project.
Create by itsmebabysmiley.
*/

#include "DHT.h"
#include "TM1637.h"

#define CLK D6
#define DIO D5
#define TEMP D7

TM1637 tm1637(CLK,DIO);
DHT dht;

void setup() {
  // put your setup code here, to run once:
  tm1637.init();
  tm1637.set(BRIGHT_DARKEST); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  dht.setup(TEMP); 
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(dht.getMinimumSamplingPeriod());
  
  float temperature = dht.getTemperature();
  float fahrenheit = dht.toFahrenheit(temperature);

  //fahrenheit
  int x = fahrenheit / 10;
  int y = int(fahrenheit) % 10;
  tm1637.display(1,x); 
  tm1637.display(2,y);
  tm1637.display(3,15);  // F
  delay(2000);
  //celsuis
  x = temperature / 10;
  y = int(temperature) % 10;
  tm1637.display(1,x); //(position,character)
  tm1637.display(2,y);
  tm1637.display(3,12);  // C
  delay(2000);
}
