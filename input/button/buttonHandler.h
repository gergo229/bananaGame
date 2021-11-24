/*
 *	Header file for handling the button input
 */

// Include guards
#ifndef BUTTON_HANDLER_H_
#define BUTTON_HANDLER_H_

/// Defines
	enum ButtonIsPressed {BUTTON_ISPRESSED = 0, BUTTON_NOTPRESSED = 1};		//type for describing the status of a button
		//it's a pulled up input, so in pressed state it's logical value is 0
		//(and this is represented in the enumeration as well)

/// Functions

	// Reads the new state of a button, and processes it
	enum ButtonIsPressed readAndCalculateNewButtonState(void);

	// Configure the GPIO ports, used by the button to an input with edge triggered ITs
	void configButtonGPIO(void);

#endif /* BUTTON_HANDLER_H_ */
