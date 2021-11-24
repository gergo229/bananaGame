/*
 *	Header file for handling the button input
 */

// Include guards
#ifndef BUTTON_HANDLER_H_
#define BUTTON_HANDLER_H_

/// Defines
	enum ButtonIsPressed {BUTTON_ISACTIVE, BUTTON_ISNOTACTIVE};		//type for describing the status of a button
		//the button considers to be active, at the moment of pressing it down

/// Functions

	// Configure the GPIO ports, used by the button to an input with edge triggered ITs
	void configButtonGPIO(void);

#endif /* BUTTON_HANDLER_H_ */
