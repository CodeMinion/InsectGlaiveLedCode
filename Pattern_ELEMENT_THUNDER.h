
/****
 * Pattern file Generated from a Gimp Image file using the Gimp LEDs plug-in.
 * Gimp LEDs Plug-in Download: https://bit.ly/GimpLeds
 * Gimp Download: https://www.gimp.org
 ****/ 
 
#ifndef ELEMENT_THUNDER_H
#define ELEMENT_THUNDER_H
#include <avr/pgmspace.h>
#include <Adafruit_NeoPixel.h>
#include "GimpLedPattern.h"

#define ELEMENT_THUNDER_DELAY 200

#define ELEMENT_THUNDER_TOTAL_LEDS 8

namespace NS_ELEMENT_THUNDER {

	const uint32_t BACKGROUND_COPY_7[] PROGMEM = { 
	0xffe600, 0xffe600, 0xffe600, 0xffe600, 0xffe600, 0xffe600, 0xffe600, 0xffe600
	};

	const uint32_t BACKGROUND_COPY_6[] PROGMEM = { 
	0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00
	};

	const uint32_t BACKGROUND_COPY_5[] PROGMEM = { 
	0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200
	};

	const uint32_t BACKGROUND_COPY_4[] PROGMEM = { 
	0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800
	};

	const uint32_t BACKGROUND_COPY_3[] PROGMEM = { 
	0x262200, 0x262200, 0x262200, 0x262200, 0x262200, 0x262200, 0x262200, 0x262200
	};

	const uint32_t BACKGROUND_COPY_2[] PROGMEM = { 
	0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800, 0x3f3800
	};

	const uint32_t BACKGROUND_COPY_1[] PROGMEM = { 
	0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200, 0x7f7200
	};

	const uint32_t BACKGROUND_COPY[] PROGMEM = { 
	0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00, 0xbfac00
	};

	const uint32_t *const ELEMENT_THUNDER[] PROGMEM = { 
	BACKGROUND_COPY_7,
	BACKGROUND_COPY_6,
	BACKGROUND_COPY_5,
	BACKGROUND_COPY_4,
	BACKGROUND_COPY_3,
	BACKGROUND_COPY_2,
	BACKGROUND_COPY_1,
	BACKGROUND_COPY,
	};

	const uint32_t ELEMENT_THUNDER_SIZES[] PROGMEM = { 
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	};

}

using namespace NS_ELEMENT_THUNDER;

		
class Pattern_ELEMENT_THUNDER : public GimpLedPattern 
{

  public:
    Pattern_ELEMENT_THUNDER(Adafruit_NeoPixel& strip): GimpLedPattern(strip){}

    ~Pattern_ELEMENT_THUNDER(){}

    void playPattern() 
    {
      int totalFrames = sizeof(ELEMENT_THUNDER) / sizeof(uint32_t*);
      for (int framePos = 0; framePos < totalFrames; framePos ++)
      {
        int frameTotalLeds = pgm_read_dword(&(ELEMENT_THUNDER_SIZES[framePos]));
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
          uint32_t ledColor = pgm_read_dword(&(ELEMENT_THUNDER[framePos][ledPos]));
          int blue = ledColor & 0x00FF;
          int green = (ledColor >> 8) & 0x00FF;
          int red = (ledColor >>  16) & 0x00FF;
          mStrip.setPixelColor(ledPos + ledOffset, red, green, blue);

        }
        mStrip.show();
        delay(ELEMENT_THUNDER_DELAY);
      }
    }

    
    void stopPattern() 
    {
      mInterrupt = true;
    }
};
		
#endif //ELEMENT_THUNDER_H

