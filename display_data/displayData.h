// Includes
#include <stdint.h>
// Defines
#define _isActive_ uint8_t isActive

//The following struct contains data for lcd
struct DisplayData{
	struct Difficulty{
		_isActive_;
		uint8_t difficulty;
	} difficulty;
	struct GamePlay{
		_isActive_;
		uint8_t bananaTreePosition;
		uint8_t bananaPosition;
		uint8_t lowerBucketPosition;
		uint8_t upperBucketPosition;
	} gamePlay;
	struct Points {
		_isActive_;
		uint8_t max;
		uint8_t current;
	} points;
	struct Text{
		_isActive_;
		char text[7];
	} text;
};

void displayData(const struct DisplayData* const displayData);
