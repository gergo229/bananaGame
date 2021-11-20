/*
 *	Header file for setup state
 */

#ifndef SETUP_STATE_H_
#define SETUP_STATE_H_

/// Includes
	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//for the eternal state machine

/// Types

	// Setup state's data structure
	struct BananaGameStateMachine_SetupState_Data {
		uint8_t timeInThisState;	//counted time in this state (used as the seed of later random generation)
		uint8_t difficulty;		//the chosen difficulty of the game (with touch slider, from 0 to DIFFICULTY_MAX
	};

/// Functions

	// Action, done at stepping into the state
	void BananaGameStateMachine_SetupState_StepInAction(void);

	// Action function of the setup state
	void BananaGameStateMachine_SetupState_Action(
		const struct AllProcessedInputData* const inputData_p,
		struct DisplayData* const displayData_p
	);

	// State switching function of the setup state
	enum BananaGameStateMachine_StateName BananaGameStateMachine_SetupState_NewState(
		const struct AllProcessedInputData* const inputData_p
	);

#endif 	/* SETUP_STATE_H_ */
