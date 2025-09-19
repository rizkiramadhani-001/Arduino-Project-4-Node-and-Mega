#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

unsigned long lastRead = 0;       // waktu terakhir baca sensor
const unsigned long interval = 2000; // jeda 2 detik

void setup() {
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // cek apakah sudah lewat interval
  if (now - lastRead >= interval) {
    lastRead = now;

    float temp = dht.readTemperature();  // pakai float biar lebih akurat

    if (isnan(temp)) {
      Serial.println("Error reading sensor!");
    } else {
      Serial.print("Temperature: ");
      Serial.println(temp);
    }
  }
}
