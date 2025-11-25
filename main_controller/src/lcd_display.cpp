#include "lcd_display.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "sensors.h"
#include "control.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupLCD() { //inicia a tela LCD
    lcd.init();
    lcd.backlight(); //liga a luz de fundo da tela LCD
}

void updateLCD() {
    //lcd.clear(); //apaga tudo da tela LCD
    lcd.setCursor(0, 0);// printa primeira linha
    lcd.print("T:");
    lcd.print(getTemperature(), 1);
    lcd.print("/");
    lcd.print(getTargetTemperature(), 1);
    lcd.print(" ");

    lcd.setCursor(0, 1);//printa segunda linha
    lcd.print("H:");
    lcd.print(getHumidity(), 1);
    lcd.print("/");
    lcd.print(getTargetHumidity(), 1);
    lcd.print(" ");
}
