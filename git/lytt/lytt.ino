/*
  SerialPassthrough sketch

  Some boards, like the Arduino 101, the MKR1000, Zero, or the Micro, have one
  hardware serial port attached to Digital pins 0-1, and a separate USB serial
  port attached to the IDE Serial Monitor. This means that the "serial
  passthrough" which is possible with the Arduino UNO (commonly used to interact
  with devices/shields that require configuration via serial AT commands) will
  not work by default.

  This sketch allows you to emulate the serial passthrough behaviour. Any text
  you type in the IDE Serial monitor will be written out to the serial port on
  Digital pins 0 and 1, and vice-versa.

  On the 101, MKR1000, Zero, and Micro, "Serial" refers to the USB Serial port
  attached to the Serial Monitor, and "Serial1" refers to the hardware serial
  port attached to pins 0 and 1. This sketch will emulate Serial passthrough
  using those two Serial ports on the boards mentioned above, but you can change
  these names to connect any two serial ports on a board that has multiple ports.

  created 23 May 2016
  by Erik Nyquist
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

int Status=0; // reset or not
int Count=0; 
char serial_str; // store serial data

void setup() {
  Serial.begin(115200);
    lcd.begin(16, 2); // initialize 16x2 lccd
    lcd.print("Hello World");
}

void loop() {
  if (Serial.available()) {  // If anything comes in Serial (USB)
    if (Status==0) {
      lcd.print("                      ");
      Status=1;
      lcd.setCursor(0,1); // (column, row)
    }
    serial_str = Serial.read();   // read it and send it out Serial1 (pins 0 & 1)
    if((serial_str>=32 && serial_str <=126)) { // only print readable characters (space to ~) in ascii
      //Serial.write(serial_str);
      lcd.print(serial_str);
    }
 } else {
    lcd.setCursor(0, 1);
    Status=0;
 }
    delay(1);
}
 
