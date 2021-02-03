#include <WiFi.h>

void setup()
{
    Serial.begin(9600);
    Serial.print("ESP Board MAC Address:  ");
    Serial.println(WiFi.macAddress());
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  delay(5000);
}
