/*
 *	Source file for game logic
 */

/// Includes
	#include "gameLogic.h"	//own header

	#include "../banana_game_state_machine/bananaGameStateMachine.h"	//the eternal state machine
	#include "gameState.h"		//game state's header

	#include "../../input/joystick/joystickHandler.h"		//for accessing joystick's definitions
	#include "../../input/touch_slider/touchSliderHandler.h"	//for accessing slider's definitions

	#include "../../display_data/displayData.h"		//contains constants about displaying

	#include <stdlib.h>	 //for random functions

/// Type declarations
	struct DisplayData;		//defined in displayData.h, needed here for cross including

/// Utility functions' declarations

	// Evaluate positions

		//Evaluate bananas's positions
		void EvaluateBananaPositions(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p);

		//Evaluate bucket's positions
		void EvaluateBucketPositions(
				const struct AllProcessedInputData* const inputData_p,
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
		);

	// Banana actions

		// Action of a non existing banana
		void BananaNonExsistentAction(
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p,
				struct Banana* const banana_p
		);

		// Action of a falling banana
		void BananaFallingAction(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p,
				struct Banana* banana_p);

		// Update the scores
		void UpdateScore(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p, uint8_t isBananaCaught);

		// Generate a banana structure
		void GenerateBanana(struct Banana* const banana_p, enum State state,
						struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p);

	// Input data manipulation

		// Convert joystick's input value compatible with touch slider's value
		uint8_t ConvertJoystick(JoystickPosition inPosition);

		// Read the input (both from joystik and touch slier)
		uint8_t GetCurrentInputValue(const struct AllProcessedInputData* const inputData_p, enum BucketType inputType);

	// Schedulers of game objects

		// Schedule bananas
		void BananaScheduler(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p);

		// Schedule buckets
		void BucketScheduler(
				const struct AllProcessedInputData* const inputData_p,
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
		);

		// Set timers of objects
		void SetTimer(void* const dataObject, enum DataType type, uint8_t difficulty, enum State state,
						struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p);

/// Main functions

	// Evaluate object positions
	void EvaluatePositions(
		const struct AllProcessedInputData* const inputData_p,
		struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
	) {
		EvaluateBananaPositions(bananaGameStateMachine_GameState_Data_p);
		EvaluateBucketPositions(inputData_p, bananaGameStateMachine_GameState_Data_p);
	}

	// Schedule objects
	void Scheduler(
			const struct AllProcessedInputData* const inputData_p,
			struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
	){
		BananaScheduler(bananaGameStateMachine_GameState_Data_p);
		BucketScheduler(inputData_p, bananaGameStateMachine_GameState_Data_p);
	}

	// Calculate difficulty
	uint8_t calculateNonExsistTime(const uint8_t difficulty) {

		const uint8_t BANANA_DISPLAYED_NUMBER = (uint8_t)((float)BANANA_DISPLAY_MAX * ((float)difficulty / (float)DIFFICULTY_MAX));

		uint8_t temp = RIPING_BANANA_TIMER + FALLING_BANANA_TIMER * (BANANA_MATRIX_HEIGHT - 1);
		return temp*(NUMBER_OF_BANANAS - BANANA_DISPLAYED_NUMBER) / BANANA_DISPLAYED_NUMBER;

		/*
		 *	NUMBER_OF_BANANAS - NONEXSISTANT / (RIPING + FALLING*(BANANAMATRIX_HEIGHT-1) + NONEXSISTANT) * NUMBER_OF_BANANAS = DISPLAYED_BANANAS
		 */
	}

/// Utility functions' definitions

	// Evaluate positions

		//Evaluate bananas's positions
		void EvaluateBananaPositions(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p){
			for(int i = 0; i < NUMBER_OF_BANANAS; i++){
				struct Banana* const banana_p = &bananaGameStateMachine_GameState_Data_p->banana[i];

				if(banana_p->timer == 0){
					switch (banana_p->state){
					case RIPING: BananaFallingAction(bananaGameStateMachine_GameState_Data_p, banana_p); break;
					case FALLING: BananaFallingAction(bananaGameStateMachine_GameState_Data_p, banana_p); break;
					case NONEXISTENT: BananaNonExsistentAction(bananaGameStateMachine_GameState_Data_p, banana_p);
					}
				}
			}
		}

		//Evaluate bucket's positions
		void EvaluateBucketPositions(
				const struct AllProcessedInputData* const inputData_p,
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
		){
			for (uint8_t i = 0; i < NUMBER_OF_CONTROLLERS; i++) {
				struct Bucket* bucket = &bananaGameStateMachine_GameState_Data_p->bucket[i];

				if(bucket->timer == 0){
					SetTimer(bucket, BUCKET, bananaGameStateMachine_GameState_Data_p->difficulty, FALLING, bananaGameStateMachine_GameState_Data_p);

					uint8_t currentInputValue;
					if (i == JOYSTICK)
						currentInputValue = ConvertJoystick(inputData_p->joystickPosition);
					else
						currentInputValue = inputData_p->touchSliderState;

					if (bucket->x < currentInputValue)
						bucket->x++;
					else if (bucket->x > currentInputValue)
						bucket->x--;
				}
			}
		}

	// Banana actions

		// Action of a non existing banana
		void BananaNonExsistentAction(
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p,
				struct Banana* const banana_p
		){
			GenerateBanana(banana_p, FALLING, bananaGameStateMachine_GameState_Data_p);
		}

		// Action of a falling banana
		void BananaFallingAction(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p,
				struct Banana* banana_p){
			(banana_p->position.y)--;
			for(int i = SLIDER; i < NUMBER_OF_CONTROLLERS; i++)
				if(bananaGameStateMachine_GameState_Data_p->bucket[i].x == banana_p->position.x &&
						banana_p->position.y == i){
					UpdateScore(bananaGameStateMachine_GameState_Data_p, 1);
					GenerateBanana(banana_p, NONEXISTENT, bananaGameStateMachine_GameState_Data_p);
				}
				else{
					if(banana_p->position.y < 0){
						UpdateScore(bananaGameStateMachine_GameState_Data_p, 0);
						GenerateBanana(banana_p, NONEXISTENT, bananaGameStateMachine_GameState_Data_p);
					}
					else{
						SetTimer(banana_p, BANANA, bananaGameStateMachine_GameState_Data_p->difficulty, FALLING, bananaGameStateMachine_GameState_Data_p);
					}
				}
		}

		// Update the scores
		void UpdateScore(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p, uint8_t isBananaCaught){
			if(isBananaCaught){
				(bananaGameStateMachine_GameState_Data_p->score.maxPoints) += 1;
				(bananaGameStateMachine_GameState_Data_p->score.currentPoints) += 1;
			}
			else
			{
				(bananaGameStateMachine_GameState_Data_p->score.maxPoints) += 1;
				(bananaGameStateMachine_GameState_Data_p->score.currentPoints) += 0;
			}
		}

		// Generate a banana structure
		void GenerateBanana(struct Banana* const banana_p, enum State state,
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p){
			//	uint16_t timer;
			//	switch (state){
			//	case RIPING: timer = RIPING_BANANA_CONSTANT; break;
			//	case FALLING: timer = FALLING_BANANA_CONSTANT; break;
			//	case NONEXISTENT: timer = rand() % nonExsistTime * difficulty;
			//	}
			uint16_t rndPos = rand() % (BANANA_MATRIX_WIDTH);
			struct Banana banana = {
					.state = state,
					.position = {rndPos, BANANA_MATRIX_HEIGHT}	//put it to the randomized horizontal position, and to the top of the gameplay
					//.timer = timer
			};
			*banana_p = banana;
			SetTimer(banana_p, BANANA, bananaGameStateMachine_GameState_Data_p->difficulty, state, bananaGameStateMachine_GameState_Data_p);
		}

	// Input data manipulation

		// Convert joystick's input value compatible with touch slider's value
		uint8_t ConvertJoystick(JoystickPosition inPosition) {
				if (inPosition == JOYSTICK_LEFT)
					return 0;
				else if (inPosition == JOYSTICK_RIGHT)
					return TOUCH_SLIDER_LOGICAL_VALUE_MAX;
				else
					return TOUCH_SLIDER_NOT_TOUCHED;
			}

		// Read the input (both from joystick and touch slier)
		uint8_t GetCurrentInputValue(const struct AllProcessedInputData* const inputData_p, enum BucketType inputType) {
			if (inputType == JOYSTICK)
				return ConvertJoystick(inputData_p->joystickPosition);
			else
				return inputData_p->touchSliderState;
		}

	// Schedulers of game objects

		// Schedule bananas
		void BananaScheduler(struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p){
			for(int i = 0; i < NUMBER_OF_BANANAS; i++) {
				bananaGameStateMachine_GameState_Data_p->banana[i].timer--;
			}
		}

		// Schedule buckets
		void BucketScheduler(
				const struct AllProcessedInputData* const inputData_p,
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p
		){
			for(enum BucketType bucketType = 0; bucketType < NUMBER_OF_CONTROLLERS; bucketType++){
				struct Bucket* const bucket_p = &bananaGameStateMachine_GameState_Data_p->bucket[bucketType];

				int8_t convertedInputValue = GetCurrentInputValue(inputData_p, (enum BucketType)bucketType);

				bool inputIsBigger = (bucket_p->previousInput >= bucket_p->x) && (convertedInputValue > bucket_p->x);
				bool inputIsLower = (bucket_p->previousInput <= bucket_p->x) && (convertedInputValue < bucket_p->x);
				bool inputIsActive = convertedInputValue != TOUCH_SLIDER_NOT_TOUCHED;

				// If the input of the bucket is active
				if (inputIsActive && (inputIsBigger || inputIsLower)) {
						bucket_p->timer--;
				}
				else {
					bucket_p->timer = BUCKET_POSITION_TIMER;
				}

				// Set the previous value to the current one after changes
				bucket_p->previousInput = convertedInputValue;
			}
		}

		// Set timers of objects
		void SetTimer(void* const dataObject, enum DataType type, uint8_t difficulty, enum State state,
				struct BananaGameStateMachine_GameState_Data* const bananaGameStateMachine_GameState_Data_p){
			struct Banana* banana = ((struct Banana*) dataObject);
			switch(type){
			case BUCKET: ((struct Bucket*) dataObject)->timer = BUCKET_POSITION_TIMER; break;
			case BANANA:
				switch (state){
					case RIPING: banana->timer = RIPING_BANANA_TIMER; break;
					case FALLING: banana->timer = FALLING_BANANA_TIMER; break;
					case NONEXISTENT: banana->timer = rand() % (2 * bananaGameStateMachine_GameState_Data_p->nonExsistTime);
					}
			}
		}
