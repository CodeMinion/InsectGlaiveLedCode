#include <Adafruit_NeoPixel.h>
#include "BlePropHelper.h"
#include "BlePropService.h"
#include <bluefruit.h>

// 1 - Include at the top of Arduino sketch under your other #include statements.
#include "Pattern_ELEMENT_FIRE.h"
#include "Pattern_ELEMENT_WATER.h"
#include "Pattern_ELEMENT_THUNDER.h"
#include "Pattern_ELEMENT_ICE.h"
#include "Pattern_ELEMENT_DRAGON.h"

#define LED_PIN    30
#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// 2 - Paste on top of setup() and under Adafruit NeoPixel declaration.
// Note: This assumes you named your pixel strip 'strip' as in the Adafruit sample
// from: https://learn.adafruit.com/adafruit-neopixel-uberguide?view=all#arduino-library-installation
// If you named it differently used that name here instead of 'strip'
GimpLedPattern * pattern_element_fire = new Pattern_ELEMENT_FIRE(strip);
GimpLedPattern * pattern_element_water = new Pattern_ELEMENT_WATER(strip);
GimpLedPattern * pattern_element_thunder = new Pattern_ELEMENT_THUNDER(strip);
GimpLedPattern * pattern_element_ice = new Pattern_ELEMENT_ICE(strip);
GimpLedPattern * pattern_element_dragon = new Pattern_ELEMENT_DRAGON(strip);

GimpLedPattern * activePattern = pattern_element_fire;


#define STATUS_LED (19)

const int LOW_BATTERY_THRESHOLD = 40;
int lastBatteryReading = 100; 

const char* DEVICENAME = "Insect Glaive";
const char* DEVICE_MODEL = "Crystal";
const char* DEVICE_MANUFACTURER = "Rounin Labs";


const int UUID16_SVC_PROP = 0x5300;
const int UUID16_CHR_PROP_PATTERN = 0x5A38;
char * SERVICE_DESCRIPTION = "LED Pattern [0-6]";

void connect_callback(uint16_t conn_handle);
void disconnect_callback(uint16_t conn_handle, uint8_t reason);
void characteristic_write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len);


// Setup the service.
BlePropService propPatternService = BlePropService(UUID16_SVC_PROP, UUID16_CHR_PROP_PATTERN, SERVICE_DESCRIPTION,  characteristic_write_callback);

// Setup the device information. This will appear when querying the device over BT.
BlePropHelper propHelper = BlePropHelper(DEVICENAME, DEVICE_MODEL, DEVICE_MANUFACTURER, connect_callback, disconnect_callback); 

BlePropService propServices[] = {propPatternService};

// Power Reduction: https://github.com/adafruit/Adafruit_nRF52_Arduino/issues/165
// Serial seems to increase consumption by 500uA https://github.com/adafruit/Adafruit_nRF52_Arduino/issues/51#issuecomment-368289198
#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x)  Serial.print(x)
#define DEBUG_PRINTLN(x)  Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif


void setup() {      

#ifdef DEBUG
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb
#endif
  // put your setup code here, to run once:
  // Setup Neopixels
  // Reduce brigthness 0-255
  int propServiceCount = sizeof(propServices)/sizeof(BlePropService);
  propHelper.setup(propServices, propServiceCount);
  
  strip.setBrightness(40);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
}


void connect_callback(uint16_t conn_handle)
{
  char central_name[32] = { 0 };
  Bluefruit.Connection(conn_handle)->getPeerName(central_name, sizeof(central_name));

  DEBUG_PRINT("Connected to ");
  DEBUG_PRINTLN(central_name);
  // Disable the BT connection LED to save battery.
  digitalWrite(STATUS_LED, LOW);
  
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  DEBUG_PRINTLN("Disconnected");
}

void characteristic_write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len)
{
  // TODO Check if characteristice is pattern char and run the proper pattern.

    DEBUG_PRINTLN("Write Received!");

  if (chr->uuid == propPatternService.getPropCharacteristic().uuid)
  {
      // Handle Ammo Pattern.
      uint8_t pattern = data[0];
      
      if( pattern == 0)
      {
        // Turn off LEDs
        turnOffPattern();
      } 
      else if (pattern == 1)
      {
        DEBUG_PRINTLN("Fired!");
    
        activatePattern(pattern_element_fire);
      }
      else if (pattern == 2)
      {
        activatePattern(pattern_element_water);
      }
      else if (pattern == 3)
      {
        activatePattern(pattern_element_thunder);
      }
      else if (pattern == 4)
      {
        activatePattern(pattern_element_ice);
      }
      else if (pattern == 5)
      {
        activatePattern(pattern_element_dragon);
      }
  }
}


void turnOffPattern()
{
  if(activePattern != NULL)
  {
    activePattern->stopPattern();
  }

  strip.clear();
  strip.show();

  activePattern = NULL;
  
}

void activatePattern(GimpLedPattern * pattern)
{
    if(activePattern != NULL)
    {
      activePattern->stopPattern();
    }

    activePattern = pattern;
}



void loop() {
  
  // 3 - Paste inside loop() to run the pattern.
  if(activePattern != NULL)
  {
    activePattern->playPattern();
  }
  // 4 - Optional: Use this to stop the pattern while it is in the middle of running.
  //pattern_ammopattern_watermoss->stopPattern();

  int batt = propHelper.readBatteryLevel();

  // Notify battery level once we are low so we don't constantly notify the app.
  if(batt < LOW_BATTERY_THRESHOLD && batt != lastBatteryReading)
  {
    propHelper.notifyBatteryLevel(batt);
    lastBatteryReading = batt; 
  }
  

}
