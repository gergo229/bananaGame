/*
 *	Source for handling high level the touch slider input
 */

/// Includes
	#include "touchSliderHandler.h"		//own header, contains ToushSliderValue type
	#include "touch.h"		//utility touch handling source's header

/// Defines
	#define MAX_TOUCH_SLIDER_INPUT_VALUE 7	//the maximum integer value of the touch slider input
	#define MAX_TOUCH_SLIDER_LOGICAL_VALUE 7 //the maximum integer value of the logical touch slider position
											//(it's fixed from the game)

/// Global variables
	extern struct InputITFlags inputITFlags;		//a global flag structure, which signs, if a change occurred in inputs

/// Main functions

	// Reads the new touch slider position and processes it
	// (this function is called, if an IT showed, that the touch slider's state changed)
	TouchSliderValue readAndCalculateNewTouchSliderPosition(void) {

		 // Read the new touch slider position
			 unsigned int newTouchSliderValue = Touch_Interpolate(Touch_Read());
			 // (it contains 1 bit of 7, indicating where the center of touch is)

		 // Map the input value into the logical touch slider position, and return it
			 float mappingConstant = (float)MAX_TOUCH_SLIDER_LOGICAL_VALUE / (float)MAX_TOUCH_SLIDER_INPUT_VALUE;	//calculate it from upper limits
			 return (TouchSliderValue)((float)newTouchSliderValue * mappingConstant);
	}
