/*
 *	This is the header for handling high level the touch slider input
 */

#ifndef TOUCH_SLIDER_HANDLER_H_
#define TOUCH_SLIDER_HANDLER_H_

/// Includes
	#include <stdint.h>		//for precise (bit sized) integer types

/// Constants
	#define TOUCH_SLIDER_MAX_LOGICAL_VALUE 6 	//the maximum integer value of the logical touch slider position
												//(it's fixed from the game)

/// Types

	// Type for representing the touch slider's slide state
	typedef int8_t TouchSliderValue;
		#define TOUCH_SLIDER_NOT_TOUCHED -1		//-1 shows it isn't pressed
		//values from 0 to MAX_TOUCH_SLIDER_LOGICAL_VALUE
	    //- see define in touchSliderHandler.c)

/// Functions

	// Reads the new touch slider position and processes it
	TouchSliderValue readAndCalculateNewTouchSliderPosition();

#endif /* TOUCH_SLIDER_HANDLER_H_ */
