/*
 *	Source, which defines common IRQ handler functions
 */

/// Includes
	#include "input/touch_slider/touch.h"

/// Defines
	#define TOUCH_PERIOD 10 //frequency divider for reading the touchslider input

///Main functions

	// IT handler function for system timer
	// 1. to time the readings of the touch slider
	void SysTick_Handler(void){

		// Touch slider's timing
		static int touchCounter = TOUCH_PERIOD;		//counter for the division
		if(touchCounter > 0){		//if not reached the "tick"
			touchCounter--;		//decrease the counter
		}
		else {	//if reached the "tick"
			touchCounter = TOUCH_PERIOD;	//restart the counter
			Touch_PeriodicProcess();	//call the touch slider's reading function
		}
	}


