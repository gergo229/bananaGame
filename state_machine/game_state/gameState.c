/*
 *	Source file for state game
 */

/// Includes

	// State handling
		#include "gameState.h"	//own header
		#include "../game_state/gameState.h"	//for accessing game state
		#include "../setup_state/setupState.h"		//for accessing setup state
		#include "../banana_game_state_machine/bananaGameStateMachine.h"		//for the state machine

	// Standard libraries
		#include <stdint.h>		//header for precise integers
		#include <stdbool.h>		//for boolean type
		#include <stdlib.h>		//for random functions

	// In-output headers
		#include "../../display_data/displayData.h"		//to be able to display data
		#include "../../input/button/buttonHandler.h"	//for accessing the button input
		#include "../../../../joystickPosition.h"		//for joystick's input types
		#include "../../input/touch_slider/touchSliderHandler.h"		//for touch slider's access

		#include "gameLogic.h"		//for logic operation of the game

/// Constants

	#define SCORE_MAX 25	//the maximum number of falling bananas (so the score)

/// Main functions

	// Action, done at stepping into game state
	void BananaGameStateMachine_GameState_stepInAction(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {
		// Seed the random generator with prepared value (from setup state's user input)

			// Get the seeding number from setup state
				const struct BananaGameStateMachine_SetupState_Data* const currentSetupDataStructure_p =
					BananaGameStateMachine_SetupState_getDataStructure(currentBananaGameStateMachine_p);	//get the appropriate data structure
				uint32_t seedNumber = currentSetupDataStructure_p->timeAtThisState;	//and get the seed number (which is from elapsed time in setup state)

			// Seed the random generator
			srand(seedNumber);

		// Get game state's data structure
			struct BananaGameStateMachine_GameState_Data* const currentGameData_p =
				BananaGameStateMachine_GameState_getDataStructure(currentBananaGameStateMachine_p);

		// Setting game state's data to defaults
			struct BananaGameStateMachine_GameState_Data bananaGameStateMachine_GameState_Data = {
						.score.maxPoints = 0,
						.score.currentPoints = 0,
						.bucket[SLIDER].timer = BUCKET_POSITION_TIMER,
						.bucket[JOYSTICK].timer = BUCKET_POSITION_TIMER,
						.bucket[SLIDER].x = DEFAULT_BUCKET_POSITION,
						.bucket[JOYSTICK].x = DEFAULT_BUCKET_POSITION,
						.bucket[SLIDER].previousInput = DEFAULT_BUCKET_POSITION,
						.bucket[JOYSTICK].previousInput = DEFAULT_BUCKET_POSITION,
						.difficulty = currentSetupDataStructure_p->difficulty,
						.nonExsistTime = calculateNonExsistTime(currentSetupDataStructure_p)
			};
			*currentGameData_p = bananaGameStateMachine_GameState_Data;

		// Generate bananas with nonexistent state
			for(int columns = 0; columns < NUMBER_OF_BANANAS; columns++)
				GenerateBanana(&(currentGameData_p->banana[columns]), NONEXISTENT, currentGameData_p);
	}

	// Action function of the game state
	void BananaGameStateMachine_GameState_action(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
			const struct AllProcessedInputData* const inputData_p,
			struct DisplayData* const displayData_p
	){

		// Call step in action, if needed (in first cycle)
			const struct BananaGameStateMachine_GameState_Data* const
				currentGameDataStructure_p =
				BananaGameStateMachine_GameState_getDataStructure(currentBananaGameStateMachine_p);	//get the current data structure
			if (currentGameDataStructure_p->isFirstInThisState) {	 	//if this is the first cycle
				currentBananaGameStateMachine_p->states[STATE_GAME].stepInAction(
					currentBananaGameStateMachine_p
				);	//then call it's step in action
			}

		// Get game stat's data structure
			struct BananaGameStateMachine_GameState_Data* const currentGameData_p =
				BananaGameStateMachine_GameState_getDataStructure(currentBananaGameStateMachine_p);

		// Decrement timers of objects (banana, bucket)
		Scheduler(inputData_p, currentGameData_p);

		// Evaluate object positions
		EvaluatePositions(inputData_p, currentGameData_p);

	}

	// State switching function of the game state
	void BananaGameStateMachine_GameState_newState(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p
	){

		// Get the current (game) data structure
		const struct BananaGameStateMachine_GameState_Data* const
			currentGameDataStructure_p =
			BananaGameStateMachine_GameState_getDataStructure(currentBananaGameStateMachine_p);

		// Check, if any of the exit conditions are met
		if (
			//inputData_p->buttonState == BUTTON_ISPRESSED ||		//if restart button is pressed
			currentGameDataStructure_p->score.maxPoints == SCORE_MAX	//or reached the end of game (so the maximum possible points)
		) {

			// Change to setup state

				//show, that this will be the first there
				((struct BananaGameStateMachine_SetupState_Data*)
					(currentBananaGameStateMachine_p->states[STATE_FINISH].data))
					->isFirstInThisState = true;

				//and change current state
				currentBananaGameStateMachine_p->currentState = STATE_FINISH;		//change to next (finish) state
		}

	}

	// Initialize setup state's data with default values
	void BananaGameStateMachine_GameState_Data_initialize(
		struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
	){
		// Set the first time showing flag
		bananaGameStateMachine_GameState_Data_p->isFirstInThisState = true;
	}

	// Get the pointer to the current state's data structure
	struct BananaGameStateMachine_GameState_Data* BananaGameStateMachine_GameState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {

		// Get the state's structure
		struct BananaGameStateMachine_State* const currentBananaGameStateMachine_GameState_p =
				&currentBananaGameStateMachine_p->states[STATE_GAME];

		// Get the pointer to the current state's data structure
		return (struct BananaGameStateMachine_GameState_Data*)(currentBananaGameStateMachine_GameState_p->data);
	};

/// Utility functions' definitions

