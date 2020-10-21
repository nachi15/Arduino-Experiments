#include <Wire.h>
#include <LiquidCrystal.h>
#include <DS3231.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
DS3231 rtc;


int val;
int inmin = 61;
int inhr = 25;
int insec = 61;
int led = 2;
void setup () {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(led, OUTPUT);
  lcd.setCursor(0, 0);
  lcd.print("CLOCK");
  delay(5000);
  lcd.clear();
  rtc.adjust(DateTime(2020, 10, 03, 12, 59, 41));
  //rtc.adjust(DateTime(F(_DATE), F(TIME_)));//auto update from computer time during upload
}
void loop () {
  DateTime now = rtc.now();
  if (inmin == 61 && inhr == 25 && insec == 61) {
    inmin = now.minute();
    inhr = now.hour();
    insec = now.second();
  }
  if ((now.hour() - inhr) == 0 && (now.minute() - inmin) == 1 &&
      (now.second() - insec) == 0) {
    digitalWrite(led, HIGH);
  }
  if ((now.hour() - inhr) == 1 && (now.second() - insec) == 0) {
    int big = now.minute();
    big = big + 60;
    if (big - inmin == 1) {
      digitalWrite(led, HIGH);
    }
  }
  if (now.hour() >= 12) {
    val = now.hour();
    val = val - 12;
    if (val == 0) val = now.hour();
    lcd.setCursor(0, 0);
    lcd.print("TIME:");
    if (val < 10)lcd.print("0");
    lcd.print(val);
    lcd.print(':');
    if (now.minute() < 10)lcd.print("0");
    lcd.print(now.minute());
    lcd.print(':');
    if (now.second() < 10)lcd.print("0");
    lcd.print(now.second());
    lcd.print("PM");
  }
  if (now.hour() < 12) {
    lcd.setCursor(0, 0);
    lcd.print("TIME:");
    if (now.hour() < 10)lcd.print("0");
    lcd.print(now.hour());
    lcd.print(':');
    if (now.minute() < 10)lcd.print("0");
    lcd.print(now.minute());
    lcd.print(':');
    if (now.second() < 10)lcd.print("0");
    lcd.print(now.second());
    lcd.print("AM");
  }
}
