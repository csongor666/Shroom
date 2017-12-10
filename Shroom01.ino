//CO2
#include "CO2Sensor.h"
CO2Sensor co2Sensor(A0, 0.99, 100);

//Temp, Hum
#include <SimpleDHT.h>
// for DHT22,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22 = 2;
SimpleDHT22 dht22;

//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int relay = 7;
int relay2 = 7;

void setup() {

  Serial.begin(9600);
  lcd.init();           // initialize the lcd
  co2Sensor.calibrate();

  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  int co2concentration = co2Sensor.read();

  // read Temperature samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperature = 0;
  float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(pinDHT22, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.println(err); delay(2000);
    return;
  }

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(8, 0);
  lcd.print("Hum: ");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print((char)223);  lcd.print("C");
  lcd.setCursor(8, 1);
  lcd.print(humidity);
  lcd.print("%");
  
  delay(1000);
  lcd.clear();
  delay(100);
  
  lcd.setCursor(12, 0);
  lcd.print("CO2: ");
  lcd.setCursor(13, 1);
  lcd.println(co2concentration);

  delay(1000);
  lcd.clear();
  delay(100);
  
  Serial.print("Sample OK: ");
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.println((float)humidity); Serial.println(" RH%");
  Serial.print("CO2: ");
  Serial.println(co2concentration);
  
  if (temperature < 22)
  {
    digitalWrite(7, HIGH);
  }
  else

  { digitalWrite(7, LOW);
  }

  if (co2concentration > 1000)
  {
    digitalWrite(8, HIGH);
  }
  else

  { digitalWrite(8, LOW);
  }


}
