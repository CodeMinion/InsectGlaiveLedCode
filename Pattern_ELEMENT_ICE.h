
/****
 * Pattern file Generated from a Gimp Image file using the Gimp LEDs plug-in.
 * Gimp LEDs Plug-in Download: https://bit.ly/GimpLeds
 * Gimp Download: https://www.gimp.org
 ****/ 
 
#ifndef ELEMENT_ICE_H
#define ELEMENT_ICE_H
#include <avr/pgmspace.h>
#include <Adafruit_NeoPixel.h>
#include "GimpLedPattern.h"

#define ELEMENT_ICE_DELAY 200

#define ELEMENT_ICE_TOTAL_LEDS 8

namespace NS_ELEMENT_ICE {

	const uint32_t BACKGROUND_COPY[] PROGMEM = { 
	0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0
	};

	const uint32_t BACKGROUND[] PROGMEM = { 
	0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0, 0x00cee0
	};

	const uint32_t LAYER[] PROGMEM = { 
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
	};

	const uint32_t *const ELEMENT_ICE[] PROGMEM = { 
	BACKGROUND_COPY,
	BACKGROUND,
	LAYER,
	};

	const uint32_t ELEMENT_ICE_SIZES[] PROGMEM = { 
	8,
	8,
	8,
	};

}

using namespace NS_ELEMENT_ICE;

		
class Pattern_ELEMENT_ICE : public GimpLedPattern 
{

  public:
    Pattern_ELEMENT_ICE(Adafruit_NeoPixel& strip): GimpLedPattern(strip){}

    ~Pattern_ELEMENT_ICE(){}

    void playPattern() 
    {
      int totalFrames = sizeof(ELEMENT_ICE) / sizeof(uint32_t*);
      for (int framePos = 0; framePos < totalFrames; framePos ++)
      {
        int frameTotalLeds = pgm_read_dword(&(ELEMENT_ICE_SIZES[framePos]));
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
          uint32_t ledColor = pgm_read_dword(&(ELEMENT_ICE[framePos][ledPos]));
          int blue = ledColor & 0x00FF;
          int green = (ledColor >> 8) & 0x00FF;
          int red = (ledColor >>  16) & 0x00FF;
          mStrip.setPixelColor(ledPos + ledOffset, red, green, blue);

        }
        mStrip.show();
        delay(ELEMENT_ICE_DELAY);
      }
    }

    
    void stopPattern() 
    {
      mInterrupt = true;
    }
};
		
#endif //ELEMENT_ICE_H

