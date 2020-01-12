#include <Adafruit_WS2801.h>
#include <Renard.h>

//yellow
#define DATAPIN 9

//green
#define CLOCKPIN 4

#define LIGHTS 5

//Yellow
#define PARROT_MOUTH 5

//Green
#define PARROT_BODY 6

Adafruit_WS2801 strip = Adafruit_WS2801(LIGHTS, DATAPIN, CLOCKPIN);
Renard renard(Serial, (LIGHTS * 3) + 2);

// Create a 24 bit color value from R,G,B
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
void setup() {
  Serial.begin(57600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinMode(PARROT_MOUTH, OUTPUT);
  pinMode(PARROT_BODY, OUTPUT);
  
}

void loop() {
  while (!renard.processInput())
      ;

  for (int light = 0; light < LIGHTS; ++light) {
    int r = renard.channelValue(light * 3 + 1);
    int g = renard.channelValue(light * 3 + 2);
    int b = renard.channelValue(light * 3 + 3);
    strip.setPixelColor(light, Color(r, g, b));
  }
  
  strip.show();


  //parrot
  if(renard.channelValue((LIGHTS * 3) + 1) > 127){
      digitalWrite(PARROT_MOUTH, HIGH);
  }
  else {
    digitalWrite(PARROT_MOUTH, LOW);
  }

  if(renard.channelValue((LIGHTS * 3) + 2) > 127){
      digitalWrite(PARROT_BODY, HIGH);
  }
  else {
    digitalWrite(PARROT_BODY, LOW);
  }
}
