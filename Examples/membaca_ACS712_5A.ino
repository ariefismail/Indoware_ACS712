#include <idwr_acs712.h>
#include <LiquidCrystal.h>


//tegangan referensi pada AVCC, harus diukur agar akurat
//jika power supply stabil biasanya 5V
const float tegangan_referensi=5.03;

//variabel pengali yang didapat dari datasheet ACS712 untuk mendapatkan 
//nilai arus berdasarkan tegangan
//untuk ACS712 5A = 185 mV/A -> 5.45A / V
//untuk ACS712 20A = 100 mV/A -> 10A / V
//untuk ACS712 30A = 66 mV/A -> 15.15A / V
const float pengali=5.4;

//import Class LiquidCrystal sebagai lcd
//rs -> sambungan pin RS LCD ke Arduino
//en  -> sambungan pin EN ke Arduino
//d4  -> sambungan pin D4 LCD ke Arduino
//d5  -> sambungan pin D5 LCD ke Arduino
//d6  -> sambungan pin D6 LCD ke Arduino
//d7  -> sambungan pin D7 LCD ke Arduino
//untuk menggunakannya -> LiquidCrystal lcd(pin RS, pin EN, pin D4, pin D5, pin D6, pin D7)
const int rs = 0, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

idwr_acs712 sensor_arus(5,tegangan_referensi);

void setup() {
  pinMode(3, OUTPUT); //letak backlight modul LCD ada di kaki 3 Arduino
  digitalWrite(3, HIGH); // harus high biar bisa menyala

  lcd.begin (16, 2); // inisialisasi LCD dengan ukuran 16x2

  lcd.home (); //letakkan kursor LCD pada posisi (0,0)
  lcd.print("Indo-Ware"); //tampilkan tulisan awal
  lcd.setCursor (0, 1);
  lcd.print("AmpereMeter");
  delay(1000);
  lcd.clear();
  sensor_arus.kalibrasi(0);
}

void loop() {
  
  lcd.clear();
  lcd.print(sensor_arus.rerata_arus_dc(10,0));
  lcd.setCursor(0,1);
  delay(500);
}

