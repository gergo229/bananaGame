/*
 *	Header file for handling the button input
 */

// Include guards
#ifndef BUTTON_HANDLER_H_
#define BUTTON_HANDLER_H_

/// Defines
	enum ButtonIsPressed {ISPRESSED = 0, NOTPRESSED = 1};		//type for describing the status of a button
																//it's a pulled-up input, so in unpressed state the input level is 1
/// Functions

	// Reads the new state of a button, and processes it
	enum ButtonIsPressed readAndCalculateNewButtonState(void);

	// Configure the GPIO ports, used by the button to an input with edge triggered ITs
	void configButtonGPIO(void);

#endif /* BUTTON_HANDLER_H_ */
