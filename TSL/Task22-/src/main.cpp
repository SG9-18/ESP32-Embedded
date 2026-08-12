#include <Arduino.h>
#include <ESP32Servo.h>
#include "HX711.h"

#define SERVO_PIN 13
#define LED_RED 26
#define LED_GREEN 25
#define BUZZER 27
#define TRIG1 5       // Left ultrasonic sensor
#define ECHO1 18
#define TRIG2 19      // Right ultrasonic sensor
#define ECHO2 21
#define SOUND_SPEED 343

#define DOUT 32       // HX711 data pin
#define CLK 33        // HX711 clock pin

Servo servo1;
HX711 scale;

int pos = 0;
const int mid_val = 45;
const float start_val = 3;
float duration;
float distance1 = 0;
float distance2 = 0;
const float NEAR_THRESHOLD = 2.0;
const float CLEAR_THRESHOLD = 3.0;
const float weightThreshold = 50.0;  // grams

void buzz()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
  }
}

float getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  float dist = (duration * SOUND_SPEED) / 2000000.0;
  return dist;
}

void setup()
{
  Serial.begin(115200);
  servo1.attach(SERVO_PIN);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  scale.begin(DOUT, CLK);
  scale.set_scale(); // Use calibration factor if known
  scale.tare();      // Reset scale to 0



  for (int i = 0; i <= 90; i++) {
    servo1.write(i);
    Serial.printf("Setup test: Servo moving to %d\n", i);
    delay(20);
  }
  for (int i = 90; i >= 0; i--) {
    servo1.write(i);
    Serial.printf("Setup test: Servo moving to %d\n", i);
    delay(20);
  }
}

void loop()
{
  distance1 = getDistance(TRIG1, ECHO1);
  distance2 = getDistance(TRIG2, ECHO2);
  float weight = scale.get_units();

  Serial.printf("Left: %.2f m, Right: %.2f m, Weight: %.2f g\r\n", distance1, distance2, weight);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);

  if ((distance1 <= NEAR_THRESHOLD || distance2 <= NEAR_THRESHOLD) && weight >= weightThreshold)
  {
    buzz();
    for (pos = 0; pos <= 90; pos++)
    {
      servo1.write(pos);
      Serial.println(pos);
      if (pos >= mid_val)
      {
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
      }
      else
      {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
      }
      delay(50);
    }

    // Wait for load to disappear before closing
    while (scale.get_units() > 10.0)
    {
      delay(100);
    }

    for (pos = 90; pos >= 0; pos--)
    {
      servo1.write(pos);
      Serial.println(pos);
      if (pos >= mid_val)
      {
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
      }
      else
      {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
      }
      delay(50);
    }
  }
}
