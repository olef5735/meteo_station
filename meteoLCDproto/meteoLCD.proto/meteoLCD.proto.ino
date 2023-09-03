#include <LiquidCrystal_I2C.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTPIN 2     // Digital pin connected to the DHT sensor 

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


LiquidCrystal_I2C lcd(0x27, 20, 4);  // адрес, столбцов, строк/

byte customChar[] = {
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00100,
  B00100
};

void setup() {

  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar);
  lcd.home();
  lcd.setCursor(17, 0);
  lcd.write(0);
  lcd.setCursor(3, 0);
  //lcd.blink();
  lcd.print("Meteo Station");

  //lcd.setCursor(0, 1);
 // lcd.print("Temperature :");
  //lcd.setCursor(14, 1);
  //lcd.print(event.temperature);
  //lcd.setCursor(0, 2);
  //lcd.print("Humidity :");
  //lcd.setCursor(12, 2);
 // lcd.print(event.relative_humidity);
 
  //  for(int i=0; i<21; i++){
  //    lcd.print(i*2);
  //    delay(2000);
  //    lcd.setCursor(i, 0);
  //    lcd.blink();
  //  }
  //  lcd.setCursor(1, 0);
  //  lcd.print("Hello, Aris!");
  //  lcd.setCursor(4, 1);  // столбец 4 строка 1
  //  lcd.print("46");
  //  lcd.blink();
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));

  lcd.setCursor(0, 1);
  lcd.print("Temperature :");
  lcd.setCursor(14, 1);
  lcd.print(event.temperature);
  
  
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));

    lcd.setCursor(0, 2);
  lcd.print("Humidity :");
  lcd.setCursor(12, 2);
  lcd.print(event.relative_humidity);
  }


  
}
/*

*/
