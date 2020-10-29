#include<Wire.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
DS3231 rtc(SDA, SCL);
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
void setup() {
rtc.begin();
lcd.begin(16,2);
lcd.backlight();
rtc.setTime(1, 32, 00); // Set the time to 12:00:00 (24hr format)
rtc.setDate(27, 10, 20); // Day, Month, Year
}
 
void loop() { 

lcd.setCursor(0,1);
lcd.print("Temp:");
lcd.print(rtc.getTemp());
lcd.print("C");
lcd.print(" Tues");
delay(3000);
 
lcd.setCursor(0,0);
lcd.print("");
lcd.print(rtc.getDateStr());
delay(1000);

lcd.setCursor(11,0);
lcd.print("");
lcd.print(rtc.getTimeStr());
delay(1000);
}
