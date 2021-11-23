/*
 *	Source for input handling of banana game
 */

/// Includes
	#include "../input_handler/inputHandler.h"	//own header

	#include "../../../../joystickPosition.h"	//an external header, containing joystick's data

	// Input specific handlers
		#include "../button/buttonHandler.h"		//button handling functions
		#include "../joystick/joystickHandler.h"		//joystick handling functions
		#include "../touch_slider/touchSliderHandler.h"		//touch slider handling functions

/// Global variables
	extern struct InputITFlags inputITFlags;		//a global flag structure, which signs, if a change occurred in inputs

/// Main functions

	// Checks, if a change occurred recently and process it if needed
	void checkInputsAndProcess(struct AllProcessedInputData* allProcessedInputs_p) {

		// Check through the inputs, and if needed call their calculation function
			// If joystick's position changed, then calculate the new value of it
			if (inputITFlags.isJoystickChanged)
				allProcessedInputs_p->joystickPosition = readAndCalculateNewJoystickPosition();

			// If button's state changed, then calculate the new value of it
			if (inputITFlags.isButtonChanged && allProcessedInputs_p->buttonState == BUTTON_NOTPRESSED)
				allProcessedInputs_p->buttonState = readAndCalculateNewButtonState();
			else
				allProcessedInputs_p->buttonState = BUTTON_NOTPRESSED;

			// If touch slider's state changed, then calculate the new value of it
			if (inputITFlags.isTouchSliderChanged)
				allProcessedInputs_p->touchSliderState = readAndCalculateNewTouchSliderPosition();
	}
