/*
 *	Source file for handling the button input
 */

/// Includes

	#include "../input_handler/inputHandler.h"	//general input handler (contains the inputITFlags type)
	#include "buttonHandler.h"	//own header (contains the ButtonIsPressed type)

	#include "em_gpio.h"		//for handling GPIO with EmLib

	#include <stdint.h>		//for precise (bit sized) integer types
	#include <stdbool.h>		//for boolean type

/// Constants

	// Defining the button's GPIO pin
		const GPIO_Port_TypeDef BUTTON_GPIO_PORT = gpioPortB;	//on port B
		const uint32_t BUTTON_GPIO_PIN  = 9;		//on pin 9
			//PB9 is connected to UIF_PB0 on STK3700 board (with pull-up resistor)
			//and it's grouped to odd IT group

/// Global variables
	extern struct InputITFlags inputITFlags;	//global structure, to indicate changes in input states

/// Main functions

	// Configure the GPIO ports, used by the button to an input with edge triggered ITs
	void configButtonGPIO(void) {

		// Set the used pins (see at Constants) as standard inputs
		GPIO_PinModeSet(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN, gpioModeInput, 0);

		// Set IT to come, as the button input pin changes
		//(so enable its IT, and set them to be sensitive to rising edges)
		GPIO_IntConfig(BUTTON_GPIO_PORT, BUTTON_GPIO_PIN, 1, 0, 1);

	}

	uint32_t volatile cntr = 0;

	// Handles the IT, which comes in case of a button state change
	//(only this input is an odd GPIO pin, so this IT handler is restricted to this functionality)
	void GPIO_ODD_IRQHandler(void) {

		cntr ++;

		//Context saving/switching is automatic

		// Sign that the change occurred with an IT flag
		inputITFlags.isButtonChanged = true;

		// Clear the EXT IT flag
		GPIO_IntClear(1 << BUTTON_GPIO_PIN);		//flags are grouped from pins
	}
