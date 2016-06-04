#include "LPD8806.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
  #include <avr/power.h>
#endif
#include <ros.h>
#include <std_msgs/Bool.h>

// Number of RGB LEDs in strand:
int nLEDs = 32;

// Chose 2 pins for output; can be any valid output pins:
int dataPin  = 2;
int clockPin = 3;

// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

ros::NodeHandle nh;

boolean blinkcolors = false;

char *message = "blink";

void messageCb( const std_msgs::Bool& toggle_msg){
  blinkcolors = toggle_msg.data;
}

ros::Subscriber<std_msgs::Bool> sub("/lights", &messageCb );

void setup()
{
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif

  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  colorWipe(strip.Color(127, 0, 0), 0);
  if (blinkcolors) {
    delay(100);
    colorWipe(strip.Color(0, 0, 0), 0);  // Red
  }
  delay(1);
}

void colorWipe(uint32_t c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
