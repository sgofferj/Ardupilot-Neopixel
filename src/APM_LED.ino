#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define LEDPIN 5
#define LENGTH 64

Adafruit_NeoPixel LED = Adafruit_NeoPixel(LENGTH, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Wire.begin(0x55);                // join i2c bus with address #8
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
  while (0 < Wire.available()) { // loop through all but the last
    uint8_t sadr = Wire.read(); // receive byte as a character
    uint8_t data = Wire.read(); // receive byte as a character
    if (sadr == 0x81) blue = data * 16;
    if (sadr == 0x82) green = data * 16;
    if (sadr == 0x83) red = data * 16;
  }
  for (int i=0; i<LENGTH; i++) {
    LED.setPixelColor(i,red,green,blue);
  }
  LED.show();

}
