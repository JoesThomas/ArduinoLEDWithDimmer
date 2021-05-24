#include <Adafruit_NeoPixel.h>
#define LEDPIN 3
#define BUTTONPIN 4
#define POTENTPIN A0
int buttonState = 0;
int lastButtonState = 0;
int lights[3] = {0, 0, 0};
int i = 0;
int pot = 0;
int pMax = 255;
int pMin = 0;

// How many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(10, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  pixels.begin(); // This initializes the NeoPixel library.
  pinMode(BUTTONPIN, INPUT);
}

void loop()
{
  delay(2);
  pot = analogRead(POTENTPIN);
  buttonState = digitalRead(BUTTONPIN);
  pot = map(pot, 0, 1023, pMin, pMax);
  lights[i] = pot;
  pixels.setPixelColor(0, pixels.Color(lights[0], lights[1], lights[2]));
  pixels.show();

  if (buttonState != lastButtonState) {
    if (i != 2 && buttonState == HIGH) {
      i = i + 1;
      Serial.println(i);
      delay(50);
    }
    else if (buttonState == HIGH && i == 2) {
      i = 0;
      Serial.println(i);
      delay(500);
    }
  }
  lastButtonState = buttonState;
}
