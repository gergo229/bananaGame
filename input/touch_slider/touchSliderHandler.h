/*
 *	Header for handling high level the touch slider input
 */

#ifndef TOUCH_SLIDER_HANDLER_H_
#define TOUCH_SLIDER_HANDLER_H_

/// Includes
	#include <stdint.h>		//for precise (bit sized) integer types

/// Constants
	#define TOUCH_SLIDER_LOGICAL_VALUE_MAX 6 	//the maximum integer value of the logical touch slider position
		//(it's fixed from the game; values starts from 0)

/// Types

	// Type for representing the touch slider's slide state
		typedef int8_t TouchSliderValue;
		#define TOUCH_SLIDER_NOT_TOUCHED -1		//-1 shows it isn't pressed
			//values from 0 to TOUCH_SLIDER_LOGICAL_VALUE_MAX are real ones

/// Functions

	// Reads the new touch slider position and processes it
	TouchSliderValue readAndCalculateNewTouchSliderPosition();

#endif /* TOUCH_SLIDER_HANDLER_H_ */
