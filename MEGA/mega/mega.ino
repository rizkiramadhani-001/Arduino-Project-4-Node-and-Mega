#include <LCD-I2C.h>
#include <Wire.h>

int temp1, temp2, temp3, temp;

LCD_I2C lcd(0x27, 16, 2); // I2C address LCD, bisa berbeda

unsigned long lastRead = 0;
const unsigned long interval = 2000; // 2 detik

void setup() {
  Serial.begin(9600);   // Debug ke PC
  Serial1.begin(9600);  // Board 2 (TX1=18, RX1=19)
  Serial2.begin(9600);  // Board 3 (TX2=16, RX2=17)
  Serial3.begin(9600);  // Board 4 (TX3=14, RX3=15)

  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= interval) {
    lastRead = now;

    // baca respon dari masing-masing board
    temp  = bacaRespon(Serial,  "Board 1");
    temp1 = bacaRespon(Serial1, "Board 2");
    temp2 = bacaRespon(Serial2, "Board 3");
    temp3 = bacaRespon(Serial3, "Board 4");

    int temps[] = {temp, temp1, temp2, temp3};
    int total = temp + temp1 + temp2 + temp3;
    printDisplay(avg(total, 4), temps, 4);
  }
}

void printDisplay(int average, int temperature[], int size) {
  // Tampilkan suhu masing-masing node
  lcd.clear();
  lcd.print("Temp Node 1:");
  lcd.print(temperature[0]);
  delay(1000);

  lcd.clear();
  lcd.print("Temp Node 2:");
  lcd.print(temperature[1]);
  delay(1000);

  lcd.clear();
  lcd.print("Temp Node 3:");
  lcd.print(temperature[2]);
  delay(1000);

  lcd.clear();
  lcd.print("Temp Node 4:");
  lcd.print(temperature[3]);
  delay(1000);

  // Tampilkan rata-rata
  lcd.clear();
  lcd.print("Rata Rata:");
  lcd.print(average);
  delay(1000);
}

int avg(int total, int length) {
  return total / length;
}

int bacaRespon(HardwareSerial &ser, String nama) {
  if (ser.available()) {
    int val = ser.parseInt();   // ambil angka dari slave
    Serial.print(nama);
    Serial.print(" => ");
    Serial.println(val);
    return val;
  }
  return 0;
}
