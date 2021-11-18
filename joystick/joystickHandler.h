/*
 *	Header for handling the joystick input
 */

#ifndef JOYSTICK_HANDLER_H_
#define JOYSTICK_HANDLER_H_

/// Includes
	#include "../../../joystickPosition.h"	//an external header, containing joystick's data

/// Functions

	// Reads and calculates the new value of joystick's position
	JoystickPosition readAndCalculateNewJoystickPosition(void);

	// Configure the GPIO ports, used by the joystick input
	void configJoystickGPIO(void);

#endif /* JOYSTICK_HANDLER_H_ */
