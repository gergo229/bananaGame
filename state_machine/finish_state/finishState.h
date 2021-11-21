/*
 *	Header file for state finish
 */

//Include guards
#ifndef FINISH_STATE_H_
#define FINISH_STATE_H_

/// Includes
	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//for the eternal state machine
	#include <stdint.h>		//for precise sized integers

/// Types

	// Finish state's data structure
		struct BananaGameStateMachine_FinishState_Data {

			// Scores of the previous game
			struct {
				uint8_t resultScore;	//the score of the user in the previous game
				uint8_t overallScore;		//the overall score in the previous game
			}gameScore;
		};

/// Functions

	// Action, done at stepping into finish state
	void BananaGameStateMachine_FinishState_stepInAction(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p
	);

	// Action function of the finish state
	void BananaGameStateMachine_FinishState_action(
			struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
			const struct AllProcessedInputData* const inputData_p,
			struct DisplayData* const displayData_p
	);

	// State switching function of the finish state
	void BananaGameStateMachine_FinishState_newState(
		struct BananaGameStateMachine* const bananaGameStateMachine_p,
		const struct AllProcessedInputData* const inputData_p
	);

	// Initialize finish state's data with default values
	void BananaGameStateMachine_FinishState_Data_initialize(
		struct BananaGameStateMachine_FinishState_Data* const bananaGameStateMachine_FinishState_Data_p
	);

#endif /* FINISH_STATE_H_*/
