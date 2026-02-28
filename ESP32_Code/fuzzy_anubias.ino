// ===================================
// ESP32 Fuzzy Control - Anubias Emersed
// Author: Sintya
// ===================================

#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {

  float suhu = dht.readTemperature();
  float kelembapan = dht.readHumidity();

  Serial.print("Suhu: ");
  Serial.println(suhu);

  Serial.print("Kelembapan: ");
  Serial.println(kelembapan);

  delay(2000);
}
