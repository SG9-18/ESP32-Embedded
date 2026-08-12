#include <Arduino.h>
#include <math.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include "WiFiClient.h"
#include "HTTPClient.h"
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#define BUZZER 5
#define PIN_WS2812B 16
#define NUM_PIXELS 2
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
const String ssid = "SG3";
const String password = "bwkq7234";
const char* serverName= "http://api.thingspeak.com/update";
const float alert_level = 4.9;
const float alert_z = -6.0;
float x_accel,y_accel,z_accel=0.0;
int response=0;
float roll_yz,roll_xz,roll_xy,pitch=0.0;
String apiKey= "SWKFLBR3DFPRI0ER";
Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_RGB + NEO_KHZ800);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
sensors_event_t a;
WiFiClient client;
HTTPClient http;

void buzz();
void setup()
{
  Serial.begin(115200);
  accel.begin();
  accel.setRange(ADXL345_RANGE_2_G);
  accel.setDataRate(ADXL345_DATARATE_1600_HZ);
  pinMode(BUZZER, OUTPUT);
  ws2812b.begin();
  ws2812b.clear();
  delay(3000);
  Serial.printf("Connecting to %s...\n", ssid);
  WiFi.begin(ssid, password);
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    attempt++;
    ws2812b.setPixelColor(1, ws2812b.Color(0, 0, 255));
    ws2812b.show();
    delay(10);
    ws2812b.setPixelColor(1, ws2812b.Color(0, 0, 0));
    ws2812b.show();
    delay(10);
    delay(250);
    if (attempt >= 80)
    {
      Serial.println("\nConnection Failed.");
      return;
    }
  }
    ws2812b.setPixelColor(1, ws2812b.Color(150, 150, 0));
    ws2812b.show();
    Serial.println("\nConnected to Wi-Fi!");
}

  void loop()
  {

    accel.getEvent(&a);

    Serial.printf("Acceleration X: ");
    Serial.print(a.acceleration.x);
    Serial.print(", Y: ");
    Serial.print(a.acceleration.y);
    Serial.print(", Z: ");
    Serial.print(a.acceleration.z);
    Serial.println(" m/s^2");

    uint8_t r = 0, g = 0, b = 0;

    if (a.acceleration.x >= alert_level)
    {
      g = 255;
    }
    else if (a.acceleration.y >= alert_level)
    {
      r = 255;
    }
    else if (a.acceleration.z >= alert_level)
    {
      b = 255;
    }
    ws2812b.setPixelColor(0, ws2812b.Color(b, r, g));
    ws2812b.show();
    if (a.acceleration.z <= alert_z)
    {
      buzz();
    }
    x_accel=a.acceleration.x;
    y_accel=a.acceleration.y;
    z_accel=a.acceleration.z;
    roll_yz= atan2(y_accel,z_accel)* 180.0 / PI;
    roll_xz= atan2(x_accel,z_accel)* 180.0 / PI;
    roll_xy= atan2(x_accel,y_accel)* 180.0 / PI;
    pitch= atan2(-x_accel, sqrt(y_accel*y_accel + z_accel*z_accel))* 180.0 / PI;
    Serial.print("Roll in y & z axiz :");
    Serial.println(roll_yz);
    Serial.print("Roll in x & z axiz :");
    Serial.println(roll_xz);
    Serial.print("Roll in x & y axiz :");
    Serial.println(roll_xy);
    Serial.print("Pitch ");
    Serial.println(pitch);
    if (WiFi.status() == WL_CONNECTED)
    {
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      String httpRequestData = "api_key="+ apiKey + "&field1=" + (String)x_accel +"&field2=" + (String)y_accel+"&field3=" + (String)z_accel +"&field4=" + (String)roll_yz +"&field5=" + (String)roll_xz+"&field6=" + (String)roll_xy+"&field7=" + (String)pitch;
      Serial.print("httpRequestData= ");
      Serial.println(httpRequestData);
      response=http.POST(httpRequestData);
      if(response==200)
      {
        Serial.println("Data sent succesfully");
      }
      else{
        Serial.println("Data sent failed");
      }
    }
    
    delay(100);
  }

  void buzz()
  {
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(BUZZER, HIGH);
      delay(100);
      digitalWrite(BUZZER, LOW);
      delay(200);
    }
  }
