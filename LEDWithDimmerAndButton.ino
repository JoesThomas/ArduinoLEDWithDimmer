#include <Adafruit_NeoPixel.h>
#define LEDPIN 3
#define BUTTONPIN 4
#define POTPIN A0
int stateButton = 0;
int lastButtonState = 0;
int lights[3] = {0, 0, 0};
int i = 0;
int pot = 0;
int potMax = 255;
int potMin = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(10, LEDPIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200); //115200 baud
  pixels.begin(); // Initialize NeoPixel library.
  pinMode(BUTTONPIN, INPUT);  //set button as input on designated pin
}

void loop()
{
  delay(2);
  pot = analogRead(POTPIN); //read pot value
  pot = map(pot, 0, 1023, potMin, potMax);
  lights[i] = pot;
  pixels.setPixelColor(0, pixels.Color(lights[0], lights[1], lights[2]));
  pixels.show();
  
  if(digitalRead(BUTTONPIN)==HIGH)
  {
    delay(10);  //10ms wait for swtich debounce
    
    if(i<2)
    {
      i++;  //increment RGB position
    }else{
      i=0; //reset RGB position
    }
    
    Serial.println(i);  //debug print
    while(digitalRead(BUTTONPIN)==HIGH);  //stay in whilst button held
  }
}
