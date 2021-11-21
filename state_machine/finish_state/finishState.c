/*
 *	Source file for state finish
 */

/// Includes

	// State handling
		#include "finishState.h"	//own header
		#include "../game_state/gameState.h"	//for accessing game state
		#include "../setup_state/setupState.h"		//for accessing setup state
		#include "../banana_game_state_machine/bananaGameStateMachine.h"		//for the state machine

	// Standard libraries
		#include <stdint.h>		//header for precise integers
		#include <stdbool.h>		//for boolean type

	// In-output headers
		#include "../../display_data/displayData.h"		//to be able to display data
		#include "../../input/button/button_handler/buttonHandler.h"	//for accessing the button input


/// Utility functions' declarations

// Get the pointer to the current state's data structure
	struct BananaGameStateMachine_FinishState_Data* BananaGameStateMachine_FinishState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	);

/// Main functions

	// Action, done at stepping into finish state
	//(get the scores from the game state)
	void BananaGameStateMachine_FinishState_stepInAction(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {
		// Get the game state's data structure
		const struct BananaGameStateMachine_GameState_Data* const gameData =
			(const struct BananaGameStateMachine_GameState_Data*)
			currentBananaGameStateMachine_p->states[STATE_GAME].data;

		// Read the scores of the game state
			uint8_t resultScore = gameData->score.currentPoints;		//read out the result score
			uint8_t overallScore = gameData->score.maxPoints;			//read out the overall score

		//Store the scores inside
			(struct BananaGameStateMachine_FinishState_Data*)
				(currentBananaGameStateMachine_p->states[STATE_FINISH].data)
				->gameScore.resultScore = resultScore;		//store the result score
			(struct BananaGameStateMachine_FinishState_Data*)
				(currentBananaGameStateMachine_p->states[STATE_FINISH].data)
				->gameScore.overallScore = overallScore;		//store the overall score

	}

	// Action function of the finish state
	// (displays the result score and the end message)
	void BananaGameStateMachine_FinishState_action(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
			const struct AllProcessedInputData* const inputData_p,
			struct DisplayData* const displayData_p
	){
		// Display the game's score
		const struct BananaGameStateMachine_FinishState_Data* finishData =
				(const struct BananaGameStateMachine_FinishState_Data*)
				BananaGameStateMachine_FinishState_getDataStructure(currentBananaGameStateMachine_p);	//get the finish state's data structure
		DisplayData_setPoints(		//and make the display structure
			displayData_p,
			finishData->gameScore.overallScore,
			finishData->gameScore.resultScore
		);

		// Display the end game message
		const char* const endGameMessage = "End of game!";
		DisplayData_setText(
			displayData_p,
			endGameMessage
		);
	}

	// State switching function of the finish state
	void BananaGameStateMachine_FinishState_newState(
		struct BananaGameStateMachine* const bananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p
	){
		// If meet the exit condition
		if (inputData_p->buttonState == BUTTON_ISPRESSED) {		//if the restart button is pressed

			// Change to setup state

				//show, that this will be the first there
				((struct BananaGameStateMachine_SetupState_Data*)
					(bananaGameStateMachine_p->states[STATE_SETUP].data))
					->isFirstInThisState = true;

				//and change current state
				bananaGameStateMachine_p->currentState = STATE_SETUP;		//change to next (setup) state
		}
	}

	// Initialize setup state's data with default values (here it's unnecessary)
	void BananaGameStateMachine_FinishState_Data_initialize(
		struct BananaGameStateMachine_FinishState_Data* const bananaGameStateMachine_FinishState_Data_p
	){
		// Data will be initialized later in the setp in function
	}

/// Utility functions' definitions

	// Get the pointer to the current state's data structure
	struct BananaGameStateMachine_FinishState_Data* BananaGameStateMachine_FinishState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	) {
		// Get the current state
		const enum BananaGameStateMachine_StateName currentState = currentBananaGameStateMachine_p->currentState;

		// Get the current state's structure
		struct BananaGameStateMachine_State* const currentBananaGameStateMachine_FinishState_p =
				&currentBananaGameStateMachine_p->states[currentState];

		// Get the pointer to the current state's data structure
		return (struct BananaGameStateMachine_FinishState_Data*)(currentBananaGameStateMachine_FinishState_p->data);
	};
