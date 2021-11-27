
/****
 * Pattern file Generated from a Gimp Image file using the Gimp LEDs plug-in.
 * Gimp LEDs Plug-in Download: https://bit.ly/GimpLeds
 * Gimp Download: https://www.gimp.org
 ****/ 
 
#ifndef ELEMENT_WATER_H
#define ELEMENT_WATER_H
#include <avr/pgmspace.h>
#include <Adafruit_NeoPixel.h>
#include "GimpLedPattern.h"

#define ELEMENT_WATER_DELAY 200

#define ELEMENT_WATER_TOTAL_LEDS 8

namespace NS_ELEMENT_WATER {

	const uint32_t BACKGROUND_COPY[] PROGMEM = { 
	0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb
	};

	const uint32_t BACKGROUND[] PROGMEM = { 
	0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb, 0x006cfb
	};

	const uint32_t LAYER[] PROGMEM = { 
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
	};

	const uint32_t *const ELEMENT_WATER[] PROGMEM = { 
	BACKGROUND_COPY,
	BACKGROUND,
	LAYER,
	};

	const uint32_t ELEMENT_WATER_SIZES[] PROGMEM = { 
	8,
	8,
	8,
	};

}

using namespace NS_ELEMENT_WATER;

		
class Pattern_ELEMENT_WATER : public GimpLedPattern 
{

  public:
    Pattern_ELEMENT_WATER(Adafruit_NeoPixel& strip): GimpLedPattern(strip){}

    ~Pattern_ELEMENT_WATER(){}

    void playPattern() 
    {
      int totalFrames = sizeof(ELEMENT_WATER) / sizeof(uint32_t*);
      for (int framePos = 0; framePos < totalFrames; framePos ++)
      {
        int frameTotalLeds = pgm_read_dword(&(ELEMENT_WATER_SIZES[framePos]));
		int ledOffset = 0;
        for (int ledPos = 0; ledPos < frameTotalLeds; ledPos++)
        {
          if(mInterrupt)
          {
            // If we are interrupted stop the pattern. "Clean" LED pattern.
            mStrip.clear();
            mStrip.show();
            mInterrupt = false;
            return;
          }
          uint32_t ledColor = pgm_read_dword(&(ELEMENT_WATER[framePos][ledPos]));
          int blue = ledColor & 0x00FF;
          int green = (ledColor >> 8) & 0x00FF;
          int red = (ledColor >>  16) & 0x00FF;
          mStrip.setPixelColor(ledPos + ledOffset, red, green, blue);

        }
        mStrip.show();
        delay(ELEMENT_WATER_DELAY);
      }
    }

    
    void stopPattern() 
    {
      mInterrupt = true;
    }
};
		
#endif //ELEMENT_WATER_H

