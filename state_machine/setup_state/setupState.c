/*
 *	Source file for setup state
 */

/// Includes
	#include "setupState.h"		//own header
	#include <stdbool.h>	//for boolean type
	#include "em_device.h"		//for device specific registers (here the SysTick is used)
#include "../../input/touch_slider/touchSliderHandler.h"	//for accessing the input setter touch slider

/// Constants
	#define DIFFICULTY_MAX 100	//the maximum difficulty level
	#define DIFFICULTY_DEFAULT 30	//the default difficulty level

/// Utility functions' declarations



/// Main functions

	// Action, done at stepping into the state
	void BananaGameStateMachine_SetupState_SetpInAction(
		struct BananaGameStateMachine_State* const actualBananaGameStateMachine_SetupState_p
	) {

		// Get the pointer to the actual state's data structure
		struct BananaGameStateMachine_SetupState_Data* const actualData_p =
				(struct BananaGameStateMachine_SetupState_Data*)(actualBananaGameStateMachine_SetupState_p->data);

		// Store the current system timer's (SysTickTimer) value
		actualData_p->timeInThisState = SysTick->VAL;

		// Set the state data to default
		actualData_p->difficulty = DIFFICULTY_DEFAULT;
	}

	// Action function of the setup state
	void BananaGameStateMachine_SetupState_Action(
		struct BananaGameStateMachine_State* const actualBananaGameStateMachine_SetupState_p,
		const struct AllProcessedInputData* const inputData_p,
		struct DisplayData* const displayData_p
	) {

		// Get the pointer to the actual state's data structure
		struct BananaGameStateMachine_SetupState_Data* const actualData_p =
				(struct BananaGameStateMachine_SetupState_Data*)(actualBananaGameStateMachine_SetupState_p->data);

		// Set the difficulty according to the input (touch slider)
		actualData_p->difficulty = inputData_p->touchSliderState * DIFFICULTY_MAX / TOUCH_SLIDER_MAX_LOGICAL_VALUE;
			//map it in

		// Create the output display structure
	}

	// State switching function of the setup state
	enum BananaGameStateMachine_StateName BananaGameStateMachine_SetupStateNewState(
		const struct AllProcessedInputData* const inputData_p
	) {

	}

/// Utility functions' definitions
