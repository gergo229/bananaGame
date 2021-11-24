/*
 *	Header for handling the touch slider at low level
 *	This file is from here: https://github.com/hans-jorg/efm32gg-stk3700-gcc-cmsis
 */

// Include guards
#ifndef TOUCH_H
#define TOUCH_H

/// Functions
	int         Touch_Init(void);
	unsigned    Touch_Read(void);
	unsigned    Touch_ReadChannel(int ch);
	int         Touch_GetCenterOfTouch(unsigned v);
	unsigned    Touch_Interpolate(unsigned v);

	/* Must be called periodically */
	void        Touch_PeriodicProcess(void);

/// Constants
	#define TOUCH_N 4

#endif  /* TOUCH_H */

