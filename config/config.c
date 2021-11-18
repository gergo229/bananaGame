/*
*	Configuration source file for banana game's program
*/

/// Includes

	#include "config.h"	 //own header

	// Input specific headers
		#include "segmentlcd.h"		//header for LCD
		#include "../touch_slider/touch.h"	//header for touch slider
		#include "em_cmu.h"
	#include "em_gpio.h"
#include "../joystick/joystickHandler.h"	//header for the joystick input

/// Defines
	#define SYSTICKDIVIDER 1000 //clock divider for system timer time

/// Utility functions' declarations

	void configGPIO(void);	//configure the GPIO peripheral
	void configTouchSlider(void);	//configure the touch slider

///Main functions

	// Configure all used peripherals of the project
	int configAll() {

		// Configure the eternal GPIO periphery
		configGPIO();

		// Configure the GPIO ports, used by the joystick input
		configJoystickGPIO();

		SegmentLCD_Init(false);		//configure the LCD
		configTouchSlider();
		SysTick_Config(SystemCoreClock/SYSTICKDIVIDER);		//configure the system timer

		return 0;
	}

/// Utility functions' definitions
	// Configure the GPIO peripheral
	void configGPIO(void) {

		// Add clock signal to it
		CMU_ClockEnable(cmuClock_GPIO, true);
	}

	// Configure the touch slider
	void configTouchSlider(void) {
		Touch_Init();
	}
