// C++ code
//
/*
  Sweep

  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <LiquidCrystal_I2C.h>                //Librería LCD controlador I2C

#include <Servo.h>
LiquidCrystal_I2C lcd_1(0x27, 16, 2);           // Dirección 0x3F, 16 x 2

int cm = 0;
int inches = 0;
int i = 0;
int pos = 0;


long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_9;

void setup()
{
  lcd_1.init();
  lcd_1.begin(16, 2);
  servo_9.attach(9, 500, 2500);
}

void loop()
{
  lcd_1.setCursor(0, 0);
  lcd_1.setBacklight(1);
  
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  inches = (cm / 2.54);
  if (inches < 5) {
    lcd_1.setCursor(0, 0);
    lcd_1.print("cerca");
    lcd_1.setCursor(0, 1);
    lcd_1.print(cm);
    lcd_1.setCursor(4, 1);
    lcd_1.print("cm");
    servo_9.write(90);
  } else {
    lcd_1.setCursor(0, 0);
    lcd_1.print("lejos");
    lcd_1.setCursor(0, 1);
    lcd_1.print(cm);
    lcd_1.setCursor(4, 1);
    lcd_1.print("cm");
    servo_9.write(0);
  }
  delay(10); // Delay a little bit to improve simulation performance
}