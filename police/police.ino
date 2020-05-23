#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6
const int buttonPin = 2;
int buttonState = 0;         // статус кнопки - нажата или отпущена


// All of this stuff below is from the example
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(11, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  strip.begin();
  strip.show();
  Serial.begin(9600);
pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  /*
   * For strip.Color(R, G, B), use 0-255 to set intensity
   * for each color (R)ed, (G)reen, (B)lue
   *
   * The last number is a delay 0-255 range.
   */

  buttonState = digitalRead(buttonPin);
if (buttonState == LOW) {
    // включаем светодиод
    WigWag2(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 100); // Blue and Red
  ClearLights();
 
  } else {
    // иначе выключаем светодиод
  }

}


//  WigWag2(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 100); // Blue and Red
//  ClearLights();
//  delay(1000);
void WigWag2(uint32_t c, uint32_t c2, uint8_t wait) {
  for (int j = 0; j < 5; j++) { // The j<# determines how many cycles
    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);

    for (int i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0);
    }
    for (int i = (strip.numPixels() / 2); i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, c2);
    }
    strip.show();
    delay(wait);
  }
}

void ClearLights() {
  for (int i = 0; i < strip.numPixels(); i = i + 1) {
    strip.setPixelColor(i, 0);    //turn every pixel off
  }
  strip.show();
}
