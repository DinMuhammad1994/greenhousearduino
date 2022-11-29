// LCD SDA = A4
// LCD SCL = A5
// DHT11 TEMPERATURE SENSOR = PIN 7
//LDR = PIN A2
//SOIL MOISTURRE = A0
//SOIL MOISTURRE = A1

// 4 RELAY = pin 2,3,4,5


#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#include "DHT.h"
#define DHTPIN 7  // what digital pin we're connected to
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int ldrPin = A2;
int ldrStatus = 0;
int MoisturePin1 = A0;  //
int MoisturePin2 = A1;  //

int fan = 3;
int fan2 = 5;
int light = 4;
int liquidpump = 2;

int MoistureStatus1;
int MoistureStatus2;

void setup() {

  Serial.begin(9600);
  dht.begin();
  pinMode(fan, OUTPUT); 
  pinMode(fan2, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(liquidpump, OUTPUT);

  digitalWrite(fan, HIGH);
   digitalWrite(fan2, HIGH);
  digitalWrite(light, HIGH);
  digitalWrite(liquidpump, HIGH);

  lcd.begin();

  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   GREEN   HOUSE    ");
  lcd.setCursor(0, 1);
  lcd.print("  MONITORING AND    ");
  lcd.setCursor(0, 2);
  lcd.print("  CONTROL SYSTEM    ");
  lcd.setCursor(0, 3);
  lcd.print(" FINAL YEAR PROJECT ");
  delay(1000);
  lcd.clear();
}

void loop() {

  int ldrStatus = analogRead(ldrPin);  //lDR
  ldrStatus = map(ldrStatus, 0, 1023, 100, 0);
  Serial.print("Light : ");
  Serial.print(ldrStatus);
  Serial.print(" %");
  Serial.println("");

  MoistureStatus1 = analogRead(MoisturePin1);  //lDR
  MoistureStatus1 = map(MoistureStatus1, 0, 1023, 99, 0);
  Serial.print("Soil Moisture1 : ");
  Serial.print(MoistureStatus1);
  Serial.print(" %");
  Serial.println("");
  MoistureStatus2 = analogRead(MoisturePin2);  //lDR
  MoistureStatus2 = map(MoistureStatus2, 0, 1023, 99, 0);
  Serial.print("Soil Moisture2 : ");
  Serial.print(MoistureStatus2);
  Serial.print(" %");
  Serial.println("");

  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.println("");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.println("");


  // PRINT ON LCD
  //1ST LINE
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP :");
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.setCursor(8, 0);
  lcd.print("*C");

  lcd.setCursor(11, 0);
  lcd.print("LIGHT:");
  lcd.setCursor(17, 0);
  lcd.print(ldrStatus);
  lcd.setCursor(19, 0);
  lcd.print("%");
   //2ND LINE
  lcd.setCursor(0, 1);
  lcd.print("HUMIDITY:");
  lcd.setCursor(10, 1);
  lcd.print(h);
  lcd.setCursor(13, 1);
  lcd.print("%");

  //3rd LINE
  lcd.setCursor(0, 2);
  lcd.print("SOIL MOISTURE1:");
  lcd.setCursor(15, 2);
  lcd.print(MoistureStatus1);
  lcd.setCursor(18, 2);
  lcd.print(" %");

  //4th LINE
  lcd.setCursor(0, 3);
  lcd.print("SOIL MOISTURE2:");
  lcd.setCursor(15, 3);
  lcd.print(MoistureStatus2);
  lcd.setCursor(18, 3);
  lcd.print(" %");
  delay(5000);


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WATER PUMP:");


  lcd.setCursor(0, 1);
  lcd.print("LAMP LIGHT:");


  lcd.setCursor(0, 2);
  lcd.print("EXHAUST FAN:");
  
  lcd.setCursor(0, 3);
  lcd.print("COOLING FAN:");


  // CHECKING THE CONDITION


  if (MoistureStatus1 > 70 && MoistureStatus2 > 70) 
  {
    digitalWrite(liquidpump, HIGH);
    Serial.println("motor off");
    lcd.setCursor(14, 0);
    lcd.print("OFF");
  }



  if (MoistureStatus1 < 30 || MoistureStatus2 < 30)
   {
      digitalWrite(liquidpump, LOW);
      Serial.println("motor ON");
      lcd.setCursor(14, 0);
      lcd.print("ON");
    }


  if (ldrStatus > 60) {
    digitalWrite(light, HIGH);
    Serial.println("lights off  ");
    lcd.setCursor(14, 1);
    lcd.print("OFF");
  }
  if (ldrStatus < 60) {
    digitalWrite(light, LOW);
    Serial.println("Lights ON");
    lcd.setCursor(14, 1);
    lcd.print("ON");
  }



  if (t < 25) {
    digitalWrite(fan, HIGH);  
    Serial.println("Fan off");
    lcd.setCursor(14, 2);
    lcd.print("OFF");
  }
  else if (t > 30) {
    digitalWrite(fan, LOW);  
    Serial.println("Fan ON");
    lcd.setCursor(14, 2);
    lcd.print("ON");
  }
  else
  {
    lcd.setCursor(14, 2);
    lcd.print("OFF");
  }
  



// cooling fan on when temperature rise greater than 32 degree
  if (t < 32 ) {
    digitalWrite(fan2, HIGH);  
    Serial.println("Fan off");
    lcd.setCursor(14, 3);
    lcd.print("OFF");
  }
  else
   {
    digitalWrite(fan2, LOW);  
    Serial.println("Fan ON");
    lcd.setCursor(14, 3);
    lcd.print("ON");
  }




  delay(5000);
}
