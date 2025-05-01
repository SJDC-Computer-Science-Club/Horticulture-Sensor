#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 13
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  dht.begin();  // initialize the sensor
  lcd.backlight();
}

void loop() {
  delay(2000);  // wait a few seconds between measurements inorder to prevent instability reading

  float humi = dht.readHumidity();         
  float tempF = dht.readTemperature(true); // true for fahrenheit 

  lcd.clear();
  // check if any reads failed
  if (isnan(humi) || isnan(tempF)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    lcd.setCursor(0, 0);  // setCursor(Column, row) print to first row
    lcd.print("Temp: ");
    lcd.print(tempF);      // print the temperature
    lcd.print((char)223);  // print ° character
    lcd.print("F");

    lcd.setCursor(0, 1);  // Cursor to second row
    lcd.print("Humidity: ");
    lcd.print(humi); 
    lcd.print("%");
  }
}
