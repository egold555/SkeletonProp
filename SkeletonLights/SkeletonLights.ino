//OLD BOOTLOADER

#include <Adafruit_WS2801.h>
#include <Renard.h>

//data pin - yellow
//clock pin - green
#define LIGHTS_SINGER_DATAPIN 9
#define LIGHTS_SINGER_CLOCKPIN 4
#define LIGHTS_SINGER_COUNT 5

//data pin - yellow
//clock pin - green
#define LIGHTS_GUITAR_DATAPIN 3
#define LIGHTS_GUITAR_CLOCKPIN 2
#define LIGHTS_GUITAR_COUNT 1

//data pin - yellow
//clock pin - green
#define LIGHTS_DRUMMER_DATAPIN 7
#define LIGHTS_DRUMMER_CLOCKPIN 8
#define LIGHTS_DRUMMER_COUNT 1

//Mouth - Yellow
//Body - Green
#define PARROT_MOUTH 5
#define PARROT_BODY 6
#define PARROT_CHANNELS 2

Adafruit_WS2801 strip_skeleton = Adafruit_WS2801(LIGHTS_SINGER_COUNT, LIGHTS_SINGER_DATAPIN, LIGHTS_SINGER_CLOCKPIN);
Adafruit_WS2801 strip_guitar = Adafruit_WS2801(LIGHTS_GUITAR_COUNT + 1, LIGHTS_GUITAR_DATAPIN, LIGHTS_GUITAR_CLOCKPIN);
Adafruit_WS2801 strip_drummer = Adafruit_WS2801(LIGHTS_DRUMMER_COUNT, LIGHTS_DRUMMER_DATAPIN, LIGHTS_DRUMMER_CLOCKPIN);

Renard renard(Serial, (LIGHTS_SINGER_COUNT * 3) + PARROT_CHANNELS + (LIGHTS_GUITAR_COUNT * 3) + (LIGHTS_DRUMMER_COUNT * 3));

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
void setup()
{
  Serial.begin(57600);
  strip_skeleton.begin();
  strip_skeleton.show(); // Initialize all pixels to 'off'

  pinMode(PARROT_MOUTH, OUTPUT);
  pinMode(PARROT_BODY, OUTPUT);

  strip_guitar.begin();
  strip_guitar.show(); // Initialize all pixels to 'off'

  strip_drummer.begin();
  strip_drummer.show(); // Initialize all pixels to 'off'
}

void loop()
{
  while (!renard.processInput())
    ;

  int r = 0;
  int g = 0;
  int b = 0;
  for (int light = 0; light < LIGHTS_SINGER_COUNT; ++light)
  {
    r = renard.channelValue(light * 3 + 1);
    g = renard.channelValue(light * 3 + 2);
    b = renard.channelValue(light * 3 + 3);
    strip_skeleton.setPixelColor(light, Color(r, g, b));
  }

  //parrot
  if (renard.channelValue((LIGHTS_SINGER_COUNT * 3) + 1) > 127)
  {
    digitalWrite(PARROT_MOUTH, HIGH);
  }
  else
  {
    digitalWrite(PARROT_MOUTH, LOW);
  }

  if (renard.channelValue((LIGHTS_SINGER_COUNT * 3) + 2) > 127)
  {
    digitalWrite(PARROT_BODY, HIGH);
  }
  else
  {
    digitalWrite(PARROT_BODY, LOW);
  }

  const int offsetGuitar = PARROT_CHANNELS + (LIGHTS_SINGER_COUNT * 3);
  r = renard.channelValue(1 + offsetGuitar);
  g = renard.channelValue(2 + offsetGuitar);
  b = renard.channelValue(3 + offsetGuitar);
  strip_guitar.setPixelColor(0, Color(r, g, b));
  strip_guitar.setPixelColor(1, Color(r, g, b));

  const int offsetDrummer = offsetGuitar + (LIGHTS_GUITAR_COUNT * 3);

  r = renard.channelValue(1 + offsetDrummer);
  g = renard.channelValue(2 + offsetDrummer);
  b = renard.channelValue(3 + offsetDrummer);
  strip_drummer.setPixelColor(0, Color(r, g, b));

  strip_skeleton.show();
  strip_guitar.show();
  strip_drummer.show();
}
