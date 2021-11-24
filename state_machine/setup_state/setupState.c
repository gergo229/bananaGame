/*
 *	Source file for setup state
 */

/// Includes

	// State handling
		#include "setupState.h"		//own header
		#include "../game_state/gameState.h"	//for accessing game state
		#include "../banana_game_state_machine/bananaGameStateMachine.h"	//for the whole state machine's functionality, data

	// In-output handling
		#include "../../input/touch_slider/touchSliderHandler.h"	//for accessing the input setter touch slider
		#include "../../display_data/displayData.h"		//for displaying output data
		#include "../../input/button/buttonHandler.h"	//for handling the button (a button press starts the game)

	// Standard C libraries
		#include <stdint.h>		//for precise sized (with give bits) integers
		#include <stdbool.h>	//for boolean type

	// Device headers
		#include "em_device.h"		//for device specific registers (here the SysTick is used)

/// Main functions

	// Action, done at stepping into the state
	void BananaGameStateMachine_SetupState_stepInAction(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {
		// Get the pointer to the current (setup) state's data structure
		struct BananaGameStateMachine_SetupState_Data* const currentData_p =
			BananaGameStateMachine_SetupState_getDataStructure(currentBananaGameStateMachine_p);

		// Store the current system timer's (SysTickTimer) value
		currentData_p->timeAtThisState = SysTick->VAL;

		// Set the state data to default
		currentData_p->difficulty = DIFFICULTY_DEFAULT;

		// Set variable to tell setupstate whether this is the first time in this state
		currentData_p->isFirstInThisState = false;
	}

	// Action function of the setup state
	void BananaGameStateMachine_SetupState_action(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p,
		struct DisplayData* const displayData_p
	) {

		// Get the pointer to the current (setup) state's data structure
		struct BananaGameStateMachine_SetupState_Data* const currentData_p =
			BananaGameStateMachine_SetupState_getDataStructure(currentBananaGameStateMachine_p);

		// Call the step in function, if needed (in first cycle)
			if (currentData_p->isFirstInThisState)	//if in first cycle
				currentBananaGameStateMachine_p->states[STATE_SETUP].stepInAction(
					currentBananaGameStateMachine_p
				);		//call the current's step in function


		// Set the difficulty according to the input (touch slider)
		float convertConstant = (float)DIFFICULTY_MAX / (float)TOUCH_SLIDER_LOGICAL_VALUE_MAX;
		if(inputData_p->touchSliderState != TOUCH_SLIDER_NOT_TOUCHED)	//if touch slider is active
			currentData_p->difficulty = (uint8_t)((float)inputData_p->touchSliderState * convertConstant);
				//map it into difficulty

		// Create the output display structure
		InitializeDisplayData(displayData_p);		//initialize it (with inactive fields)
		DisplayData_setDifficulty(
				displayData_p,
				(float)currentData_p->difficulty / (float)DIFFICULTY_MAX		//normalize the difficulty (to be able to display it generally)
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
				struct BananaGameStateMachine_SetupState_Data* const currentSetupData_p =
						(struct BananaGameStateMachine_SetupState_Data*)bananaGameStateMachine_p->states[STATE_SETUP].data;	 //current state's data
				const uint32_t startTimeAtThisState = currentSetupData_p->timeAtThisState;		//time at the start of the state (stored before)
				currentSetupData_p->timeAtThisState = SysTick->VAL - startTimeAtThisState;		//difference is the elapsed timem, store it

			// Step into next (game) state
				((struct BananaGameStateMachine_GameState_Data*)
					(bananaGameStateMachine_p->states[STATE_GAME].data))
					->isFirstInThisState = true;		//sign that this will be a step in to this state
				bananaGameStateMachine_p->currentState = STATE_GAME;
		}
	}

	// Initialize SetupState_Data with default values
	void BananaGameStateMachine_SetupState_Data_initialize(
			struct BananaGameStateMachine_SetupState_Data* const bananaGameStateMachine_SetupState_Data_p
			){
		// Set the difficulty to default
		bananaGameStateMachine_SetupState_Data_p->difficulty = DIFFICULTY_DEFAULT;

		// Sign, that this will be a first cycle in the state
		bananaGameStateMachine_SetupState_Data_p->isFirstInThisState = true;
	}

	// Get the pointer to the setup state's data structure
	struct BananaGameStateMachine_SetupState_Data* BananaGameStateMachine_SetupState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {

		// Get the current state's structure
		struct BananaGameStateMachine_State* const currentBananaGameStateMachine_SetupState_p =
				&currentBananaGameStateMachine_p->states[STATE_SETUP];

		// Get the pointer to the current state's data structure
		return (struct BananaGameStateMachine_SetupState_Data*)(currentBananaGameStateMachine_SetupState_p->data);
	};
