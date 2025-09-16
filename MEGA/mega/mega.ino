int temp1, temp2, temp3, temp;


void setup() {
  Serial.begin(9600);   // Debug ke PC
  Serial1.begin(9600);  // TX1=18, RX1=19
  Serial2.begin(9600);  // TX2=16, RX2=17
  Serial3.begin(9600);  // TX3=14, RX3=15
}

void loop() {
  // kirim perintah GET ke semua board
  Serial.println("GET");
  Serial1.println("GET");
  Serial2.println("GET");
  Serial3.println("GET");


  delay(1000); // tunggu respon
  //temp = bacaRespon(Serial, "Board 1"); nanti kalo udah pake display atau act di un comment
  temp1 = bacaRespon(Serial1, "Board 2");
  temp2 = bacaRespon(Serial2, "Board 3");
  temp3 = bacaRespon(Serial3, "Board 4");
  Serial.println("TEMP");
  //Serial.println(temp); nanti kalo udah pake display di un comment
  Serial.println(temp1);
  Serial.println(temp2);
  Serial.println(temp3);


  int total = temp1 + temp2 + temp3; //todo: tambahin temp yang index 0 kalo udah pake display atau act
  Serial.println("AVG");
  Serial.println(avg(total, 3)); // ganti ke 4 


}

void doSomething()
{
  //dosomething 
}

int avg(int total, int length){
  int avg = total/3; // todo: ganti ke 4 kalo udah pake display atau act
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

