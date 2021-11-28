
/****
 * Pattern file Generated from a Gimp Image file using the Gimp LEDs plug-in.
 * Gimp LEDs Plug-in Download: https://bit.ly/GimpLeds
 * Gimp Download: https://www.gimp.org
 ****/ 
 
#ifndef ELEMENT_FIRE_H
#define ELEMENT_FIRE_H
#include <avr/pgmspace.h>
#include <Adafruit_NeoPixel.h>
#include "GimpLedPattern.h"

#define ELEMENT_FIRE_DELAY 200

#define ELEMENT_FIRE_TOTAL_LEDS 8

namespace NS_ELEMENT_FIRE {

	const uint32_t BACKGROUND_COPY[] PROGMEM = { 
	0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000, 0xff0000
	};

	const uint32_t BACKGROUND_COPY_5[] PROGMEM = { 
	0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000
	};

	const uint32_t BACKGROUND_COPY_3[] PROGMEM = { 
	0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000
	};

	const uint32_t LAYER[] PROGMEM = { 
	0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
	};

	const uint32_t BACKGROUND_COPY_4[] PROGMEM = { 
	0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000, 0x3f0000
	};

	const uint32_t BACKGROUND_COPY_2[] PROGMEM = { 
	0x7f0000, 0x7f0000, 0x7f0000, 0x7f0000, 0x7f0000, 0x7f0000, 0x7f0000, 0x7f0000
	};

	const uint32_t BACKGROUND_COPY_1[] PROGMEM = { 
	0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000, 0xbf0000
	};

	const uint32_t *const ELEMENT_FIRE[] PROGMEM = { 
	BACKGROUND_COPY,
	BACKGROUND_COPY_5,
	BACKGROUND_COPY_3,
	LAYER,
	BACKGROUND_COPY_4,
	BACKGROUND_COPY_2,
	BACKGROUND_COPY_1,
	};

	const uint32_t ELEMENT_FIRE_SIZES[] PROGMEM = { 
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	};

}

using namespace NS_ELEMENT_FIRE;

		
class Pattern_ELEMENT_FIRE : public GimpLedPattern 
{

  public:
    Pattern_ELEMENT_FIRE(Adafruit_NeoPixel& strip): GimpLedPattern(strip){}

    ~Pattern_ELEMENT_FIRE(){}

    void playPattern() 
    {
      int totalFrames = sizeof(ELEMENT_FIRE) / sizeof(uint32_t*);
      for (int framePos = 0; framePos < totalFrames; framePos ++)
      {
        int frameTotalLeds = pgm_read_dword(&(ELEMENT_FIRE_SIZES[framePos]));
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
          uint32_t ledColor = pgm_read_dword(&(ELEMENT_FIRE[framePos][ledPos]));
          int blue = ledColor & 0x00FF;
          int green = (ledColor >> 8) & 0x00FF;
          int red = (ledColor >>  16) & 0x00FF;
          mStrip.setPixelColor(ledPos + ledOffset, red, green, blue);

        }
        mStrip.show();
        delay(ELEMENT_FIRE_DELAY);
      }
    }

    
    void stopPattern() 
    {
      mInterrupt = true;
    }
};
		
#endif //ELEMENT_FIRE_H

