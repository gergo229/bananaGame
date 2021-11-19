/*
 *	This is the header for handling high level the touch slider input
 */

#ifndef TOUCH_SLIDER_HANDLER_H_
#define TOUCH_SLIDER_HANDLER_H_

/// Includes
	#include <stdint.h>		//for precise (bit sized) integer types

/// Types

	typedef uint8_t TouchSliderValue;		//own type for representing the touch slider's slide state

/// Functions

	// Reads the new touch slider position and processes it
	TouchSliderValue readAndCalculateNewTouchSliderPosition();

#endif /* TOUCH_SLIDER_HANDLER_H_ */
