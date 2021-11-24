/*
 *	Header file for state game
 */

//Include guards
#ifndef GAME_STATE_H_
#define GAME_STATE_H_

/// Includes
	#include "gameLogic.h"		//for logic operation of the game

	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//for the eternal state machine

	#include <stdint.h>		//for precise sized integers
	#include <stdbool.h>	//for boolean type

/// Types

	// Declaration of BananaGameStateMachine (because of cross including)
	struct BananaGameStateMachine;
	struct DisplayData;

	// Game state's data structure
		struct BananaGameStateMachine_GameState_Data {

			// Bananas of the game
				struct Banana{
					enum State{RIPING, FALLING, NONEXISTENT} state;
					int32_t timer;
					struct Position{
						uint8_t x;
						int8_t y;
					}position;
				}banana[NUMBER_OF_BANANAS];

			// Bucket of the game
				struct Bucket{
					int32_t timer;
					uint8_t x;
					int8_t previousInput;
				}bucket[NUMBER_OF_CONTROLLERS];

			// Score of the game
				struct Score {
					uint8_t maxPoints;
					uint8_t currentPoints;
				}score;

			// Difficulty settings of the game
				uint8_t difficulty;
				uint32_t nonExistTime;

			// First cycle showing flag of the state
			bool isFirstInThisState;
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
