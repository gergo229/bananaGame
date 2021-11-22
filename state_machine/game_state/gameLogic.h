/*
 *	Header for game logic
 */

#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

/// Constants

	// Object numbers
		#define NUMBER_OF_BANANAS 14
		#define NUMBER_OF_CONTROLLERS 2
		#define BANANA_DISPLAY_MAX 10

	#define DEFAULT_BUCKET_POSITION 3

	// Timings
		#define RIPING_BANANA_TIMER 100000
		#define FALLING_BANANA_TIMER 30000
		#define BUCKET_POSITION_TIMER 1000


/// Includes
	#include <stdint.h>		//for precise integers
	#include "../../input/input_handler/inputHandler.h"		//for general input handling
	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//the eternal state machine
	#include "../game_state/gameState.h"	//for state game
	#include "../setup_state/setupState.h"

/// Types
	enum BucketType {SLIDER = 0, JOYSTICK = 1};
	enum DataType {BUCKET, BANANA};

	struct BananaGameStateMachine_GameState_Data; 	//declare before use
	enum State;
	struct Banana;

/// Functions

	// Decrement timers of objects (banana, bucket)
	void Scheduler(
			const struct AllProcessedInputData* const inputData_p,
			struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
	);

	// Evaluate object positions
	void EvaluatePositions(
		const struct AllProcessedInputData* const inputData_p,
		struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
	);

	// Generate a banana structure
	void GenerateBanana(struct Banana* const banana_p, enum State state,
		struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p);

	// Calculate difficulty
	uint8_t calculateNonExsistTime(const struct BananaGameStateMachine_SetupState_Data* const currentSetupDataStructure_p);

#endif /* GAME_LOGIC_H_ */
