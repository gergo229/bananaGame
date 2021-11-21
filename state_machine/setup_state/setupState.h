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
		uint32_t timeAtStartOfState;	//initial time in this state (needed to the seed of later random generation)
		uint8_t difficulty;		//the chosen difficulty of the game (with touch slider, from 0 to DIFFICULTY_MAX
	};

/// Functions

	// Action, done at stepping into the state
	void BananaGameStateMachine_SetupState_StepInAction(
			struct BananaGameStateMachine_State* const actualBananaGameStateMachine_SetupState_p
	);

	// Action function of the setup state
	void BananaGameStateMachine_SetupState_Action(
			struct BananaGameStateMachine_State* const actualBananaGameStateMachine_SetupState_p,
			const struct AllProcessedInputData* const inputData_p,
			struct DisplayData* const displayData_p
	);

	// State switching function of the setup state
	enum BananaGameStateMachine_StateName BananaGameStateMachine_SetupState_NewState(
		struct BananaGameStateMachine* const bananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p
	);

	// Initialize SetupState_Data with default values
	void BananaGameStateMachine_SetupState_Data_initialize(
			struct BananaGameStateMachine_SetupState_Data* const bananaGameStateMachine_SetupState_Data_p
			);

#endif 	/* SETUP_STATE_H_ */
