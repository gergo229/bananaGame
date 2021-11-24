/*
 *	Source for handling the joystick input
 */

/// Includes
	#include "../input_handler/inputHandler.h"		//for the IT flag structure
	#include "joystickHandler.h"	//own header
	#include "../../../../joystickPosition.h"	//an external header, containing joystick's data

	#include "em_gpio.h"	//for abstract GPIO handling

	#include <stdbool.h>	//for boolean type
	#include <stdint.h>		//for precise (bit sized) integer types

/// Global variables
	extern struct InputITFlags inputITFlags;	//a global flag structure, which signs, if a change occurred in inputs

/// Constants

	// The pin's location, on which data active joystick signal is received
		const GPIO_Port_TypeDef JOYSTICK_ACTIVITY_GPIO_PORT = gpioPortD;
		const uint32_t JOYSTICK_ACTIVITY_GPIO_PIN = 0;
			//(PD0 is pin 4 on Expansion Header)

	// The pin's location, on which data is received from the joystick
		const GPIO_Port_TypeDef JOYSTICK_DATAIN_GPIO_PORT = gpioPortD;
		const uint32_t JOYSTICK_DATAIN_GPIO_PIN = 2;
			//(PD2 is pin 8 on Expansion Header)

	//(the 2 pins are set to even pins, to have the same IT route for them)


/// Main functions

	// Reads and calculates the new value of joystick's position
	// (this function is called, if an IT showed, that the joystick input is changed)
	JoystickPosition readAndCalculateNewJoystickPosition(void) {

		// Check, if the joystick is active (activity pin is in active state)
			if (GPIO_PinInGet(JOYSTICK_ACTIVITY_GPIO_PORT, JOYSTICK_ACTIVITY_GPIO_PIN) == JOYSTICK_ACTIVE) {

				// Check, that the active joystick is in left state
				if (GPIO_PinInGet(JOYSTICK_DATAIN_GPIO_PORT, JOYSTICK_DATAIN_GPIO_PIN) == JOYSTICK_LEFT)
					return JOYSTICK_LEFT;
				else 	//if it's not in left state, then it's in right state
					return JOYSTICK_RIGHT;
			}
			else 	//if the joystick is not active
				return JOYSTICK_DEFAULT;
	}

	// Configure the GPIO ports, used by the joystick to an input with edge triggered ITs
	void configJoystickGPIO(void) {

		// Set the used pins (see at Constants) as standard inputs
			GPIO_PinModeSet(JOYSTICK_ACTIVITY_GPIO_PORT, JOYSTICK_ACTIVITY_GPIO_PIN, gpioModeInput, false);
			GPIO_PinModeSet(JOYSTICK_DATAIN_GPIO_PORT, JOYSTICK_DATAIN_GPIO_PIN, gpioModeInput, false);

		// Set IT to come, as any of the joystick input pins changes
		//(so enable their IT, and set them to be sensitive to both rising and falling edges)
			GPIO_IntConfig(JOYSTICK_ACTIVITY_GPIO_PORT, JOYSTICK_ACTIVITY_GPIO_PIN, 1, 1, 1);
			GPIO_IntConfig(JOYSTICK_DATAIN_GPIO_PORT, JOYSTICK_DATAIN_GPIO_PIN, 1, 1, 1);
	}

	// Handle the IT, which comes, if any of the joystick input pins changes
	// (both of them are connected to even pins)
	void GPIO_EVEN_IRQHandler(void) {

		// Context saving is done automatically

		// Only the joystick input pins' ITs are enables,
		// so it's sure, that it gave it.

		// So then, set the IT flag for joystick
			inputITFlags.isJoystickChanged = true;

		// Clear the EXT IT flag
			uint32_t clearFlag = (1 << JOYSTICK_DATAIN_GPIO_PIN) | (1 << JOYSTICK_ACTIVITY_GPIO_PIN);
				//clear both sources' bits (flags are grouped from pins)
			GPIO_IntClear(clearFlag);
	}

