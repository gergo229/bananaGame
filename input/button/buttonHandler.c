/*
 *	Source file for handling the button input
 */

/// Includes
	#include "buttonHandler.h"	//own header (contains the ButtonIsPressed type)
	#include "em_gpio.h"		//for handling GPIO with EmLib
	#include <stdbool.h>		//for boolean type
	#include "../input_handler/inputHandler.h"	//general input handler (contains the inputITFlags type)

/// Constants

	// Defining the button's GPIO pin
		const GPIO_Port_TypeDef BUTTON_GPIO_PORT = gpioPortB;	//on port B
		const unsigned int BUTTON_GPIO_PIN  = 9;		//on pin 9
		//PB9 is connected to UIF_PB0 on STK3700 board (with pull-up resistor)
		//and it's grouped to odd IT group

/// Main functions

	// Reads the new state of a button, and processes it
	// (it called after an IT showed, that it's changed)
	enum ButtonIsPressed readAndCalculateNewButtonState(void) {

		// Clear the IT flag
		inputITFlags.isButtonChanged = false;

		// Return with the read input
		return GPIO_PinInGet(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN);		//the enum is aligned with the input value (see definition's comment)
	}

	// Configure the GPIO ports, used by the button to an input with edge triggered ITs
	void configButtonGPIO(void) {

		// Set the used pins (see at Constants) as standard inputs
		GPIO_PinModeSet(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN, gpioModeInput, 0);

		// Set IT to come, as the button input pin changes
		//(so enable its IT, and set them to be sensitive to both rising and falling edges)
		GPIO_IntConfig(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN, 1, 1, 1);

	}

	// Handles the IT, which comes in case of a button state change
	//(only this input is an odd GPIO pin, so this IT handler is restricted to this functionality)
	void GPIO_ODD_IRQHandler(void) {

		//Context saving/switching is automatic

		// Sign that the change occurred with an IT flag
		inputITFlags.isButtonChanged = true;

		// Clear the EXT IT flag
		GPIO_IntClear(BUTTON_GPIO_PIN);		//flags are grouped from pins
	}
