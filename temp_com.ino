/*
Temperature computer monitor Project V2.
DHT11 library (https://github.com/adafruit/DHT-sensor-library)
TM1637 library (https://github.com/reeedstudio/libraries/tree/master/DigitalTube)
Create by itsmebabysmiley.
*/
#include "DHT.h"
#include "TM1637.h"

#define CLK D6
#define DIO D5
#define DHTPIN 13 
#define DHTTYPE DHT11

TM1637 tm1637(CLK,DIO);
DHT dht(DHTPIN, DHTTYPE);

int x; //position 1 in 7segment
int y; //position 2 in 7segment
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  tm1637.init();
  tm1637.display(0,11);
  tm1637.display(1,10);
  tm1637.display(2,11);
  tm1637.display(3,4);
  tm1637.set(BRIGHT_DARKEST); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.clearDisplay();


  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float c = dht.readTemperature(); //read temperature in celsius.
// //----fahrenheit-----
//  float f = dht.readTemperature(true); //read temperature in fahrenheit.
//  x = f / 10;
//  y = int(f) % 10;
//  tm1637.display(1,x); //(position,character)
//  tm1637.display(2,y);
//  tm1637.display(3,15);  //F

// //----celsuis----
  x = c / 10;
  y = int(c) % 10;
  tm1637.display(1,x); //(position,character)
  tm1637.display(2,y);
  tm1637.display(3,12);  // C

  delay(2000);
  //Compute heat index in Celsius.
  float hc = dht.computeHeatIndex(c, h, false);
  x = hc / 10;
  y = int(hc) % 10;
  tm1637.display(1,x); //(position,character)
  tm1637.display(2,y);
  tm1637.display(3,12);  // C

  //Compute hear index in fahrenheit.
//  float hf = dht.computeHeatIndex(f, h);
//  x = hf / 10;
//  y = int(hf) % 10;
//  tm1637.display(1,x); //(position,character)
//  tm1637.display(2,y);
//  tm1637.display(3,12);  // C

  Serial.print("Humidity: ");Serial.print(h);Serial.print("%\t\t");
  Serial.print("Temperature: ");Serial.print(c);Serial.print("°C\t\t");
  Serial.print("Heat index: ");Serial.print(hc);Serial.print("°C\n");
}
