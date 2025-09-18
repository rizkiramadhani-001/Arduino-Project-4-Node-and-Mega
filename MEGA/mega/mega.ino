#include <LCD-I2C.h>
#include <Wire.h>



int temp1, temp2, temp3, temp;



LCD_I2C lcd(0x27, 16, 2); // Default address of most PCF8574 modules, change according


void setup() {
  Serial.begin(9600);   // Debug ke PC
  Serial1.begin(9600);  // TX1=18, RX1=19
  Serial2.begin(9600);  // TX2=16, RX2=17
  Serial3.begin(9600);  // TX3=14, RX3=15

  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();


}

void loop() {

  // kirim perintah GET ke semua board
  Serial.println("GET");
  Serial1.println("GET");
  Serial2.println("GET");
  Serial3.println("GET");


  delay(1000); // tunggu respon
  temp = bacaRespon(Serial, "Board 1");
  temp1 = bacaRespon(Serial1, "Board 2");
  temp2 = bacaRespon(Serial2, "Board 3");
  temp3 = bacaRespon(Serial3, "Board 4");

  int temps[] = {temp, temp1, temp2, temp3};

  int total = temp + temp1 + temp2 + temp3; //todo: tambahin temp yang index 0 kalo udah pake display atau act
  printDisplay(avg(total, 4), temps, 4);

}

void printDisplay(int average, int temperature[], int size) {

    //Display Temp Masing2 Node
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
    lcd.clear();



    //Display Rata Rata
    lcd.print("Rata Rata: ");
    lcd.print(average);
    delay(1000);
    lcd.clear();


}

int avg(int total, int length){
  int avg = total/length; // todo: ganti ke 4 kalo udah pake display atau act
  return avg;
}

int bacaRespon(HardwareSerial &ser, String nama) {
  if (ser.available()) {
    int val = ser.parseInt();   // langsung ambil angka
    Serial.print(nama);
    Serial.print(" => ");
    Serial.println(val);
    return val;
  }
  return 0;
}
