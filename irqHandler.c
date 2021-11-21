/*
 *	Source, which defines common IRQ handler functions
 */

/// Includes
	#include "input/touch_slider/touch.h"	//low level handling of the touch slider
	#include <stdbool.h>	//for boolean type
	#include "input/input_handler/inputHandler.h"	//general handling of inputs (for InputITFlags type)

/// Defines

	// Timing periods (if they are powers of 2, then the calculation is faster)
	#define TOUCH_SLIDER_READ_PERIOD 8 	//frequency divider for reading the touchslider input
	#define TOUCH_SLIDER_PROCESS_PERIOD	2	//frequency divider for processing the touchslider input

/// Global variables
	extern struct InputITFlags inputITFlags;		//a global flag structure, which signs, if a change occurred in inputs

///Main functions

	// IT handler function for system timer
	// 1. to time the readings of the touch slider
	// 2. to time the processes of the touch slider input (this calculates the logical value of it)
	void SysTick_Handler(void){

		// Overall counter of systicks
		static uint32_t sysTickCounter = 0;		//initialize it with 0

		// Touch slider's reading timing
		if (sysTickCounter % TOUCH_SLIDER_READ_PERIOD == 0)	//if reached the "tick"
			Touch_PeriodicProcess();	//call the touch slider's reading function

		// Touch slider's processing timing
		if (sysTickCounter % TOUCH_SLIDER_PROCESS_PERIOD == 0)	//if reach the "tick"
			inputITFlags.isTouchSliderChanged = true;		//sign the changed flag (we can't ensure,
														//it truly, changed, but we suppose it could)

		// Step the overall counter
		sysTickCounter++;	//it may overflow, but that's fine

	} /* SysTick_Handler() */


