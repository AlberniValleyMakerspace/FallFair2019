#include "Arduino.h"
#include "FastLED.h"

#define LED_PIN     7
#define NUM_LEDS    80
#define BRIGHTNESS  125  //max 255
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define FillColour  CRGB::Green
#define LedOne  CRGB::Red
#define LedTwo CRGB::Red
#define LedThree  CRGB::White
#define LedFour  CRGB::Red
#define LedFive  CRGB::Red
#define DelayBetweenSteps	15

int StopSmash,GoSmash,StopGo=0;

CRGB leds[NUM_LEDS];



void setup()
{
	FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
	FastLED.setBrightness(BRIGHTNESS);
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);
	Serial.begin(9600);
}


void loop()
{
	turnTheWheel();

}


void turnTheWheel()
{
		for (int LED = 0; LED < NUM_LEDS; ++ LED)
		{
			StopSmash = digitalRead(2);
			GoSmash = digitalRead(3);
			if (!StopSmash)
			{
				StopGo = LOW;
			}
			else if (!GoSmash && StopSmash)
			{
				StopGo = HIGH;
			}
			if (StopGo==HIGH)
			{
				fill_solid(leds, NUM_LEDS, FillColour);

				if (LED==NUM_LEDS-4)
				{
					leds[LED] = LedOne;
					leds[LED+1] = LedTwo;
					leds[LED+2] = LedThree;
					leds[LED+3] = LedFour;
					leds[0] = LedFive;
				}
				else if (LED==NUM_LEDS-3)
				{
					leds[LED] = LedOne;
					leds[LED+1] = LedTwo;
					leds[LED+2] = LedThree;
					leds[0] = LedFour;
					leds[1] = LedFive;
				}
				else if (LED==NUM_LEDS-2)
				{
					leds[LED] = LedOne;
					leds[LED+1] = LedTwo;
					leds[0] = LedThree;
					leds[1] = LedFour;
					leds[2] = LedFive;
				}
				else if (LED==NUM_LEDS-1)
				{
					leds[LED] = LedOne;
					leds[0] = LedTwo;
					leds[1] = LedThree;
					leds[2] = LedFour;
					leds[3] = LedFive;
				}
				else
				{
					leds[LED] = LedOne;
					leds[LED+1] = LedTwo;
					leds[LED+2] = LedThree;
					leds[LED+3] = LedFour;
					leds[LED+4] = LedFive;
				}
				FastLED.show();
				delay(DelayBetweenSteps);
			}
			Serial.print(StopGo);
			Serial.print(GoSmash);
			Serial.println(StopSmash);
		}
}

