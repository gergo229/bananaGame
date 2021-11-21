/*
 *	Header file for state game
 */

//Include guards
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

/// Includes
	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//for the eternal state machine
	#include <stdint.h>		//for precise sized integers

/// Types

	// Game state's data structure
		struct BananaGameStateMachine_GameState_Data {

		};

/// Functions

	// Action, done at stepping into game state
	void BananaGameStateMachine_GameState_stepInAction(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	);

	// Action function of the game state
	void BananaGameStateMachine_GameState_action(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
			const struct AllProcessedInputData* const inputData_p,
			struct DisplayData* const displayData_p
	);

	// State switching function of the game state
	void BananaGameStateMachine_GameState_newState(
		struct BananaGameStateMachine* const bananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p
	);

	// Initialize game state's data with default values
	void BananaGameStateMachine_GameState_Data_initialize(
		struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
	);

	// Get the pointer to the game state's data structure
	struct BananaGameStateMachine_GameState_Data* BananaGameStateMachine_GameState_getDataStructure(
		struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	);

#endif /* GAME_STATE_H_*/
