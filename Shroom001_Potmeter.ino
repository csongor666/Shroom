//Temp, Hum
#include <SimpleDHT.h>
// for DHT22,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT22up = 4;
SimpleDHT22 dht22;

//Potentiometer
int potPin = 6;
int val= 0;
int val2=0;
int degree=0;
char statuspara=(char)46;
char statusfutes=(char)46;

//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

int ventillator = 7;
int heatmat = 8;

void setup() {
  Serial.begin(9600);
  lcd.init();           // initialize the lcd
  pinMode(heatmat, OUTPUT); //relay A
  pinMode(ventillator, OUTPUT); //relay B
}

void loop() {
   // read Temperature samples.
  // @remark We use read2 to get a float data, such as 10.1*C
  //    if user doesn't care about the accurate data, use read to get a byte data, such as 10*C.
  float temperatureup = 0;
  float humidityup = 0;
  int errup = SimpleDHTErrSuccess;
  if ((errup = dht22.read2(pinDHT22up, &temperatureup, &humidityup, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22up failed, err="); Serial.println(errup); delay(2000);
    return;
  }

  Serial.print((float)temperatureup);
  Serial.print(";");
  Serial.println((float)humidityup);

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.setCursor(2,0);
  lcd.print(temperatureup);
  lcd.setCursor(6,0);
  lcd.print("->t=");
  lcd.setCursor(10,0);
  lcd.print(degree);
  lcd.setCursor(12,0);
  lcd.print((char)223);  lcd.print("C");
  lcd.setCursor(15,0);
  lcd.print(statusfutes);
  
  lcd.setCursor(0, 1);
  lcd.print("H=");
  lcd.setCursor(2,1);
  lcd.print(humidityup);
  lcd.setCursor(6,1);
  lcd.print("->t=80%");
  lcd.setCursor(15,1);
  lcd.print(statuspara);
  
  delay(2000);

  val = analogRead(potPin);    // read the value from the sensor
  val2 = map(val, 165, 1023, 0, 10);
  Serial.println((float)val);
  Serial.println((float)val2);
  degree = (val/90)+19;
  Serial.println(degree);
  
//  if (temperatureup < degree)
//  {
//    digitalWrite(heatmat, HIGH);
//    statusfutes=(char)42;
//  }
//  else
//  { digitalWrite(heatmat, LOW);
//    statusfutes=(char)46;
//  }
//
//  if (humidityup < 80)
//  {
//    digitalWrite(ventillator, HIGH);
//    statuspara=(char)42;
//  }
//  else
//  { digitalWrite(ventillator, LOW);
//    statuspara=(char)46;
//  }
  //Relay control
  if (temperatureup > degree)
  {
    Serial.println("if 1, mért>beállított-0,25");
    if (temperatureup > (degree - 0.25)) {
      digitalWrite(heatmat, LOW);
      statusfutes = (char)46;
      Serial.println("if 1.1, >,>");
    }
    else {
      digitalWrite(heatmat, HIGH);
      statusfutes = (char)42;
      Serial.println("if 1.2, >,<");
    }
  }
  else if (temperatureup < degree) 
  {
    Serial.println("if 2, mért<beállított+0,25");
    if (temperatureup < (degree + 0.25)) {
      digitalWrite(heatmat, HIGH);
      statusfutes = (char)42;
      Serial.println("else if 2.1, <,<");
    }
    else {
      digitalWrite(heatmat, LOW);
      statusfutes = (char)46;
      Serial.println("else if 2.2, <,>");
    }
  }

  if (humidityup < 80)
  {
    digitalWrite(ventillator, LOW);
    statuspara = (char)42;
  }
  else
  { digitalWrite(ventillator, HIGH);
    statuspara = (char)46;
  }

  //Serial check
  Serial.print((float)temperatureup, 1);
  Serial.print(";");
  Serial.print(degree);
  Serial.print(";");
  Serial.println((float)humidityup, 1);
}

}
