/*
 *	Source file for setup state
 */

/// Includes
	#include "setupState.h"		//own header
	#include <stdbool.h>	//for boolean type
	#include "em_device.h"		//for device specific registers (here the SysTick is used)
	#include "../../input/touch_slider/touchSliderHandler.h"	//for accessing the input setter touch slider
	#include "../../display_data/displayData.h"		//for displaying output data
	#include <stdint.h>		//for precise sized (with give bits) integers
	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//for the whole state machine's functionality, data
	#include "../../input/button/buttonHandler.h"	//for handling the button (a button press starts the game)
	#include <stdint.h>		//for precise size (with given bits) integers

/// Utility functions' declarations

	// Get the pointer to the actual state's data structure
	struct BananaGameStateMachine_SetupState_Data* BananaGameStateMachine_SetupState_getDataStructure(
		struct BananaGameStateMachine* const actualBananaGameStateMachine_p
	);

/// Main functions

	// Action, done at stepping into the state
	void BananaGameStateMachine_SetupState_stepInAction(
		struct BananaGameStateMachine* const actualBananaGameStateMachine_p
	) {
		// Get the pointer to the actual state's data structure
		struct BananaGameStateMachine_SetupState_Data* const actualData_p =
			BananaGameStateMachine_SetupState_getDataStructure(actualBananaGameStateMachine_p);

		// Store the current system timer's (SysTickTimer) value
		actualData_p->timeAtStartOfState = SysTick->VAL;

		// Set the state data to default
		actualData_p->difficulty = DIFFICULTY_DEFAULT;
	}

	// Action function of the setup state
	void BananaGameStateMachine_SetupState_action(
		struct BananaGameStateMachine* const actualBananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p,
		struct DisplayData* const displayData_p
	) {

		// Get the pointer to the actual state's data structure
		struct BananaGameStateMachine_SetupState_Data* const actualData_p =
			BananaGameStateMachine_SetupState_getDataStructure(actualBananaGameStateMachine_p);

		// Set the difficulty according to the input (touch slider)
		float convertConstant = (float)DIFFICULTY_MAX / (float)TOUCH_SLIDER_MAX_LOGICAL_VALUE;
		if(inputData_p->touchSliderState != TOUCH_SLIDER_NOT_TOUCHED)	//if touch slider is active
			actualData_p->difficulty = (uint8_t)((float)inputData_p->touchSliderState * convertConstant);
				//map it into difficulty

		// Create the output display structure
		InitializeDisplayData(displayData_p);		//initialize it (with inactive fields)
		DisplayData_setDifficulty(
				displayData_p,
				(float)actualData_p->difficulty / (float)DIFFICULTY_MAX		//normalize the difficulty (to be able to display it generally)
		);	//and write the selected difficulty

	}

	// State switching function of the setup state
	void BananaGameStateMachine_SetupState_newState(
		struct BananaGameStateMachine* const bananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p
	) {
		// Check, if exit condition is met or not
		if (inputData_p->buttonState == BUTTON_ISPRESSED) {		//if the start game button is pressed

			// Calculate random seed of the game (from elapsed time in setup state)
				const enum BananaGameStateMachine_StateName actualState = bananaGameStateMachine_p->actualState;	//the actual state
				const struct BananaGameStateMachine_SetupState_Data* const actualData_p =
						(const struct BananaGameStateMachine_SetupState_Data*)bananaGameStateMachine_p->states[actualState].data;	 //actual state's data
				const uint32_t timeAtStartOfState = actualData_p->timeAtStartOfState;		//time at the start of the state (stored before)
				const uint32_t randomSeed = SysTick->VAL - timeAtStartOfState;		//difference is the elapsed time
//				(struct BananaGameStateMachine_GameState_Data)(bananaGameStateMachine_p->states[STATE_GAME].data)
//						->randomSeed = randomSeed;
				;	//set the game state's seed with the elapsed time (it can be taken as a random value)

			// Step into next (game) state
			bananaGameStateMachine_p->actualState = STATE_GAME;
		}
		else {		//if the exit condition doesn't met
			bananaGameStateMachine_p->actualState = STATE_GAME;		//stay in the setup state
		}
	}

	// Initialize SetupState_Data with default values
	void BananaGameStateMachine_SetupState_Data_initialize(
			struct BananaGameStateMachine_SetupState_Data* const bananaGameStateMachine_SetupState_Data_p
			){
		bananaGameStateMachine_SetupState_Data_p->difficulty = DIFFICULTY_DEFAULT;
	}
/// Utility functions' definitions

	// Get the pointer to the actual state's data structure
	struct BananaGameStateMachine_SetupState_Data* BananaGameStateMachine_SetupState_getDataStructure(
		struct BananaGameStateMachine* const actualBananaGameStateMachine_p
	) {
		// Get the actual state
		const enum BananaGameStateMachine_StateName actualState = actualBananaGameStateMachine_p->actualState;

		// Get the actual state's structure
		struct BananaGameStateMachine_State* const actualBananaGameStateMachine_SetupState_p =
				&actualBananaGameStateMachine_p->states[actualState];

		// Get the pointer to the actual state's data structure
		return (struct BananaGameStateMachine_SetupState_Data*)(actualBananaGameStateMachine_SetupState_p->data);
	};
