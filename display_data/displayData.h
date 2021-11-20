// Includes
#include <stdint.h>
// Defines
#define _isActive_ uint8_t isActive

// Defining used lcd dimensions
#define LOWER_SEGMENT_LENGTH 7
#define LOWER_SEGMENT_HEIGHT 5

// Connecting lcd segment positions to gamelogic objects
#define BANANA_POS_TOP a
#define BANANA_POS_MIDDLE
#define BANANA_POS_BOTTOM
#define BUCKET_POS_LOWER d
#define BUCKET_POS_UPPER_LEFT_SEGMENT g
#define BUCKET_POS_UPPER_RIGHT_SEGMENT m

#define BANANA_MATRIX_HEIGHT LOWER_SEGMENT_LENGTH - 2

//The following struct contains data for lcd
struct DisplayData{
	struct Difficulty{
		_isActive_;
		uint8_t difficulty;
	} difficulty;
	struct GamePlay{
		_isActive_;
		uint8_t bananaMatrix[BANANA_MATRIX_HEIGHT][LOWER_SEGMENT_LENGTH];
		struct BananaPosMatrix{
			uint8_t bananaPosTop[LOWER_SEGMENT_LENGTH];
			uint8_t bananaPosMiddle[LOWER_SEGMENT_LENGTH];
			uint8_t bananaPosBottom[LOWER_SEGMENT_LENGTH];
		} bananaPosMatrix;
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
		char text[LOWER_SEGMENT_LENGTH];
	} text;
};

void displayData(const struct DisplayData* const displayData);
