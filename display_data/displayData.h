#ifndef DISPLAY_DATA_H_
#define DISPLAY_DATA_H_

// Includes
#include <stdint.h>
#include "../state_machine/game_state/gameLogic.h"		//for getting data from gameLogic

// Defines
#define _isActive_ uint8_t isActive

#define IS_NOT_SET -1
#define MAX_DIFFICULTY 7

// Defining lcd dimensions
#define LOWER_SEGMENT_WIDTH 7
#define LOWER_SEGMENT_HEIGHT 5

// Connecting lcd segment positions to gamelogic objects
#define BANANA_POS_TOP a
#define BANANA_POS_MIDDLE j
#define BANANA_POS_BOTTOM p
#define BUCKET_POS_LOWER d
#define BUCKET_POS_UPPER_LEFT_SEGMENT g
#define BUCKET_POS_UPPER_RIGHT_SEGMENT m

// Declaring types
struct Banana;		//defined in gameState.h, just needed here because of cross including
struct BananaGameStateMachine; 		//defined in bananaGameStateMahcine.h, just needed here because of cross including

// Defining the used part of lcd
#define BANANA_MATRIX_HEIGHT LOWER_SEGMENT_HEIGHT - 2
#define BANANA_MATRIX_WIDTH LOWER_SEGMENT_WIDTH

//The following struct contains data to display on lcd
//note the isActive variables: these define whether the game data should be displayed in a given gameState
struct DisplayData{
	struct Difficulty{
		_isActive_;
		uint8_t difficulty;
	} difficulty;
	struct GamePlay{
		_isActive_;
		struct BananaMatrix{
			uint8_t matrix[BANANA_MATRIX_HEIGHT][BANANA_MATRIX_WIDTH];
		}bananaMatrix;
		//uint8_t bananaMatrix[BANANA_MATRIX_HEIGHT][BANANA_MATRIX_WIDTH];	//contains all the appearing bananas in a 2D matrix
		uint8_t bucketPosLower;
		uint8_t bucketPosUpper;
	} gamePlay;
	struct Points {
		_isActive_;
		uint8_t max;
		uint8_t current;
	} points;
	struct Text{
		_isActive_;
		char text[LOWER_SEGMENT_WIDTH];
	} text;
};

void DisplayData_displayData(const struct DisplayData* const displayData);
void InitializeDisplayData(struct DisplayData* const displayData_p);

// Setter functions of DisplayData structure
void DisplayData_setDifficulty(struct DisplayData* const displayData_p, const float difficulty);
void DisplayData_setGamePlay(
	struct DisplayData* const displayData_p,
	const struct Banana* const bananas,
	const uint8_t bucketPosLower,
	const uint8_t bucketPosUpper
);
void DisplayData_setPoints(struct DisplayData* const displayData_p, const uint8_t max, const uint8_t current);
void DisplayData_setText(struct DisplayData* const displayData_p, const char* const text);

// Set all display structures inactive
void DisplayData_setAllInactive(struct DisplayData* const displayData_p);

#endif
