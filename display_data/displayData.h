// Includes
#include <stdint.h>

// Defines
#define _isActive_ uint8_t isActive

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
		uint8_t bananaMatrix[BANANA_MATRIX_HEIGHT][BANANA_MATRIX_WIDTH];	//contains all the appearing bananas in a 2D matrix
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

void displayData(const struct DisplayData* const displayData);
