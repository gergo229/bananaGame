/*
 *	Header for input handling of banana game
 */

#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

/// Includes
	#include "../../../../joystickPosition.h"	//an external header, containing joystick's data
	#include <stdint.h>		//for precise (with given bits) integers
	#include "../touch_slider/touchSliderHandler.h"		//abstract handling of the touch slider input

/// Defines
	enum ButtonIsPressed {ISPRESSED, NOTPRESSED};		//type for describing the status of a button

	// Contains all inputs' values preprocessed to game logic
	struct AllProcessedInputs {
		JoystickPosition joystickPosition;	//position of the joystick
		enum ButtonIsPressed buttonState;	//state of the button
		TouchSliderValue touchSliderState;	//state of the touch slider
	};
		// Default/initilazation value of the AllPorcessedInputs struct
		#define ALL_PROCESSED_INPUTS_DEFAULT { \
			.joystickPosition = JOYSTICK_DEFAULT, \
			.buttonState = NOTPRESSED, \
			.touchSliderState = 0 \
		};

	// Stores IT flags of inputs, to show changes from ITs
	struct InputITFlags {
		uint8_t isJoystickChanged;	//shows, if the joystick was moved recently
		uint8_t isButtonChanged;	//shows, if the button was moved recently
		uint8_t isTouchSliderChanged;	//shows, if the touch slider was moved recently
	};

/// Functions

	// Checks, if a change occurred recently and process it if needed
	void checkInputsAndProcess(struct AllProcessedInputs* allProcessedInputs_p);

#endif /* INPUT_HANDLER_H_ */
