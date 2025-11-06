#include "lcd_display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "sensors.h"
#include "control.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupLCD() { //inicia a tela LCD
    lcd.init();
    lcd.backlight();
}

void updateLCD() {
    lcd.clear();
    lcd.setCursor(0, 0);// printa primeira linha
    lcd.print("T:");
    lcd.print(getTemperature());
    lcd.print("/");
    lcd.print(getTargetTemperature());

    lcd.setCursor(0, 1);//printa segunda linha
    lcd.print("H:");
    lcd.print(getHumidity());
    lcd.print("/");
    lcd.print(getTargetHumidity());
}
