#include <Arduino.h>

void setup()
{
  Serial.begin(115200); 

  int a[] = {10, 20, 30, 40, 50};
  int len = sizeof(a) / sizeof(a[0]);

  for (int i = 0; i < len; i++)
  {
    Serial.println(a[i]); 
  }
} 
void loop(){}


