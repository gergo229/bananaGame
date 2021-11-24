/*
 *	Source for handling high level the touch slider input
 */

/// Includes
	#include "touchSliderHandler.h"		//own header, contains ToushSliderValue type
	#include "touch.h"		//utility touch handling source's header

	#include <stdint.h>		//for precise sized integers

/// Defines
	#define TOUCH_SLIDER_MAX_INPUT_VALUE 6	//the maximum integer value of the touch slider input
		//(it's fixed in the implementation of handling low-level the touch slider - see touch.c)

/// Main functions

	// Reads the new touch slider position and processes it, return values in range 0-TOUCH_SLIDER_MAX_LOGICAL_VALUE
	// (this function is called, if an IT showed, that the touch slider's state changed)
	TouchSliderValue readAndCalculateNewTouchSliderPosition(void) {

		// Read the new touch slider position
			 int newTouchSliderValue = Touch_GetCenterOfTouch(Touch_Read());
			 // (it gives the result in range [1 ; MAX_TOUCH_SLIDER_INPUT_VALUE], -1 if not touched)

		// Map the input value into the logical touch slider position, and return it
			 float mappingConstant = (float)TOUCH_SLIDER_LOGICAL_VALUE_MAX / (float)TOUCH_SLIDER_MAX_INPUT_VALUE;	//calculate it from upper limits

			 if (newTouchSliderValue == -1)		//if it's not pressed (value -1 shows that)
				 return TOUCH_SLIDER_NOT_TOUCHED;
			 else {

				 // Convert the input value to a range from 0, and invert it (because of touch slider's drawing)
				 uint8_t newTouchSliderValueConverted = TOUCH_SLIDER_MAX_INPUT_VALUE - (newTouchSliderValue - 1);

				 // And map it into logical its logical falue (and convert back to touch slider's value's type
				 return (TouchSliderValue)((float)newTouchSliderValueConverted * mappingConstant);
			 }
	}

