#include <Wire.h>
#include <Adafruit_NeoPixel.h>

/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define LEDPIN 5          // data out pin
#define LENGTH 64         // length of the Neopixel strip

Adafruit_NeoPixel LED = Adafruit_NeoPixel(LENGTH, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin(0x55);             // join i2c bus with address #55
  Wire.onReceive(receiveEvent); // register event
  LED.begin();
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  while (0 < Wire.available()) {
    uint8_t sadr = Wire.read();   // read subaddress
    uint8_t data = Wire.read();   // read color value
    if (sadr == 0x81) blue = data * 16;
    if (sadr == 0x82) green = data * 16;
    if (sadr == 0x83) red = data * 16;
  }
  for (int i=0; i<LENGTH; i++) {
    LED.setPixelColor(i,red,green,blue);
  }
  LED.show();
}
