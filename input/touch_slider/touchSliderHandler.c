/*
 *	Source for handling high level the touch slider input
 */

/// Includes
	#include "touchSliderHandler.h"		//own header, contains ToushSliderValue type
	#include "touch.h"		//utility touch handling source's header

/// Defines
	#define TOUCH_SLIDER_MAX_INPUT_VALUE 7	//the maximum integer value of the touch slider input
											//(it's fixed in the implementation of hadnling low-level the touch slider - ses touch.c)

/// Main functions

	// Reads the new touch slider position and processes it
	// (this function is called, if an IT showed, that the touch slider's state changed)
	TouchSliderValue readAndCalculateNewTouchSliderPosition(void) {

		 // Read the new touch slider position
			 int newTouchSliderValue = Touch_GetCenterOfTouch(Touch_Read());
			 // (it gives the result in range 0-MAX_TOUCH_SLIDER_INPUT_VALUE, -1 if not touched)

		 // Map the input value into the logical touch slider position, and return it
			 float mappingConstant = (float)TOUCH_SLIDER_MAX_LOGICAL_VALUE / (float)TOUCH_SLIDER_MAX_INPUT_VALUE;	//calculate it from upper limits
			 if (newTouchSliderValue == -1)		//if it's not pressed (value -1 shows that)
				 return TOUCH_SLIDER_NOT_TOUCHED;
			 else
				 return (TouchSliderValue)((float)newTouchSliderValue * mappingConstant);
	}
