/*
 *	Header for game logic
 */

#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

/// Constants

	// Object numbers
		#define NUMBER_OF_BANANAS 50
		#define NUMBER_OF_CONTROLLERS 2

		#define BANANA_DISPLAY_MAX 14

	#define DEFAULT_BUCKET_POSITION 3

	// Timings (1 unit means 0.07ms)
		#define RIPING_BANANA_TIMER 3000
		#define FALLING_BANANA_TIMER 1000
		#define BUCKET_POSITION_TIMER 100


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
	void ConvertBanana(struct Banana* const banana_p, enum State state, uint32_t nonExistTime);

	// Calculate difficulty
	uint32_t calculateNonExsistTime(const uint8_t difficulty);

#endif /* GAME_LOGIC_H_ */
