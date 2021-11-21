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

/// Utility functions' declarations

	// Get the pointer to the current state's data structure
	struct BananaGameStateMachine_SetupState_Data* BananaGameStateMachine_SetupState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	);

/// Main functions

	// Action, done at stepping into the state
	void BananaGameStateMachine_SetupState_stepInAction(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {
		// Get the pointer to the current state's data structure
		struct BananaGameStateMachine_SetupState_Data* const currentData_p =
			BananaGameStateMachine_SetupState_getDataStructure(currentBananaGameStateMachine_p);

		// Store the current system timer's (SysTickTimer) value
		currentData_p->timeAtThisState = SysTick->VAL;

		// Set the state data to default
		currentData_p->difficulty = DIFFICULTY_DEFAULT;
	}

	// Action function of the setup state
	void BananaGameStateMachine_SetupState_action(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p,
		struct DisplayData* const displayData_p
	) {

		// Get the pointer to the current state's data structure
		struct BananaGameStateMachine_SetupState_Data* const currentData_p =
			BananaGameStateMachine_SetupState_getDataStructure(currentBananaGameStateMachine_p);

		// Call the step in function, if needed (in first cycle)
			const enum BananaGameStateMachine_StateName currentState =
				currentBananaGameStateMachine_p->currentState;	//get the current state
			if (currentData_p->isFirstInThisState)	//if in first cycle
				currentBananaGameStateMachine_p->states[currentState].stepInAction();		//call the current's step in function


		// Set the difficulty according to the input (touch slider)
		float convertConstant = (float)DIFFICULTY_MAX / (float)TOUCH_SLIDER_MAX_LOGICAL_VALUE;
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
				const enum BananaGameStateMachine_StateName currentState = bananaGameStateMachine_p->currentState;	//the current state
				const struct BananaGameStateMachine_SetupState_Data* const currentData_p =
						(const struct BananaGameStateMachine_SetupState_Data*)bananaGameStateMachine_p->states[currentState].data;	 //current state's data
				const uint32_t startTimeAtThisState = currentData_p->timeAtThisState;		//time at the start of the state (stored before)
				currentData_p->timeAtThisState = SysTick->VAL - startTimeAtThisState;		//difference is the elapsed timem, store it

			// Step into next (game) state
				((struct BananaGameStateMachine_StateGame_Data*)
					(bananaGameStateMachine_p->states[STATE_GAME].data))
					->isFirstInThisState = true;		//sign that this will be a step in to this state
				bananaGameStateMachine_p->currentState = STATE_GAME;
		}
		else {		//if the exit condition doesn't met
			bananaGameStateMachine_p->currentState = STATE_SETUP;		//stay in the setup state
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

/// Utility functions' definitions

	// Get the pointer to the current state's data structure
	struct BananaGameStateMachine_SetupState_Data* BananaGameStateMachine_SetupState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {
		// Get the current state
		const enum BananaGameStateMachine_StateName currentState = currentBananaGameStateMachine_p->currentState;

		// Get the current state's structure
		struct BananaGameStateMachine_State* const currentBananaGameStateMachine_SetupState_p =
				&currentBananaGameStateMachine_p->states[currentState];

		// Get the pointer to the current state's data structure
		return (struct BananaGameStateMachine_SetupState_Data*)(currentBananaGameStateMachine_SetupState_p->data);
	};
