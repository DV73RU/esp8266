/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Модули в составе проекта
 * ESP8266 NodeMCU V3 Lua WIFI (3.75) https://goo.gl/GFDYq0
 * NodeMCU Motor Shield Board L293D for ESP-12E (1.68 $) https://goo.gl/T0WwT6
 * DHT 11 (1.00 $) https://goo.gl/sCBn3d  Тут дешево но долго шло
 * DHT 11 (3.11 $) https://goo.gl/rBFbBD  Тут дороже но дойдет быстрее
*/
// Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
//#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> //Библиотека для работы с WIFI 
#include <DHT.h>
#include<DallasTemperature.h> 
#define ONE_WIRE_BUS 2 // DS18B20 подключаем на D4 на плате  
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
int temp_0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "WkfEGY3v1SejkZLfJO0dVhNgeT2z-hb4";
char ssid[] = "RT-10-2.4";
char pass[] = "1234567890";


#define DHTPIN D7          // What digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

#define GPIO1 D5
#define GPIO2 D6
bool rele1 = 1;
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  DS18B20.requestTemperatures(); 
  temp_0 = DS18B20.getTempCByIndex(0); // Sensor 0 показания для датчика 1 в цельсиях
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
 
  Blynk.virtualWrite(10, temp_0); //выврд данных на виртуальный пин V10
  Blynk.virtualWrite(1, 5); //выврд данных на виртуальный пин V10
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup(){
  Serial.begin(9600);
  pinMode(GPIO2, OUTPUT); 
  digitalWrite(GPIO2, rele1);
   

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  DS18B20.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);


}
  BLYNK_WRITE(V1) {rele1= param.asInt();digitalWrite(GPIO2, rele1); 
  
}

  // Debug console
 
  

void loop()
{
  Blynk.run();
  //timer.run();
}
