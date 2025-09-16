#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  // cek apakah ada perintah masuk
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n'); // baca sampai enter
    cmd.trim();  // hapus spasi/enter

    if (cmd == "GET") {
      int temp = dht.readTemperature();

      if (isnan(temp)) {
        Serial.println("Error reading sensor!");
      } else {
        Serial.print("Temperature: ");
        Serial.println(temp);
      }
    } else {
      Serial.println("Unknown command");
    }
  }
}
