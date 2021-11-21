// Includes
#include <stdint.h>
#include "segmentlcd.h"
#include "displayData.h"
#include "../../segmentlcd/segmentlcd_individual.h"
#include <stdbool.h>

// Update lcd based on data in displayData variable
void displayData(const struct DisplayData* const displayData){
	SegmentLCD_AllOff();										//turn off all segments before update
	if(displayData->text.isActive){								//update lcd with text if property is active
		SegmentLCD_Write(displayData->text.text);
	}

	if(displayData->points.isActive){
		SegmentLCD_Symbol(LCD_SYMBOL_COL10, 1);
		SegmentLCD_Number((uint16_t) (displayData->points.max) * 100 + (uint16_t)(displayData->points.current));
	}

	// convert max and current point into one 4 digit number and print to lcd
	if(displayData->difficulty.isActive){
		for(int i = 0; i < displayData->difficulty.difficulty; i++)
			SegmentLCD_ARing(i, 1);
	}

	if(displayData->gamePlay.isActive){
		SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[LOWER_SEGMENT_WIDTH];			//this variable stores the data to display
		for(int i = 0; i < BANANA_MATRIX_WIDTH; i++){											//initializing it's values to 0
			lowerCharSegments[i].raw = 0;
		}
		lowerCharSegments[displayData->gamePlay.bucketPosLower].BUCKET_POS_LOWER = 1;			//setting segment of bucket
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_LEFT_SEGMENT = 1;//setting segments of upper bucket
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_RIGHT_SEGMENT = 1;
		for(int i = 0; i < BANANA_MATRIX_WIDTH; i++){											//iterating through banana matrix
			if(displayData->gamePlay.bananaMatrix[0][i] == 1)
				lowerCharSegments[i].BANANA_POS_TOP = displayData->gamePlay.bananaMatrix[0][i];
			if(displayData->gamePlay.bananaMatrix[1][i] == 1)
				lowerCharSegments[i].BANANA_POS_MIDDLE = 1;
			if(displayData->gamePlay.bananaMatrix[2][i] == 1)
				lowerCharSegments[i].BANANA_POS_BOTTOM = 1;
		}
		SegmentLCD_LowerSegments(&lowerCharSegments);			//update lower segments of lcd with the initialized variable
	}
}

// Constructor is needed, if not all position data is set, only the active ones
struct DisplayData* constructDisplayData(){
	struct DisplayData* displayData = calloc(1, sizeof(struct DisplayData));
	displayData->gamePlay.bucketPosLower = IS_NOT_SET;
	displayData->gamePlay.bucketPosUpper = IS_NOT_SET;

	return displayData;
}

// Destructor for displayData
void destructDisplayData(struct DisplayData* displayData){
	free(displayData);
}

/// Setter functions of DisplayData structure

	// Set the difficulty of the DisplayData
	void DisplayData_setDifficulty(struct DisplayData* const displayData_p, const uint8_t difficulty) {

		// Sign the field as an active one
		displayData_p->difficulty.isActive = true;

		// Copy the data fields
		displayData_p->difficulty.difficulty = difficulty;
	}

	// Set the GamePlay of the DisplayData
	void DisplayData_setGamePlay(
		struct DisplayData* const displayData_p,
		const uint8_t* const bananaMatrix,
		const uint8_t bucketPosLower,
		const uint8_t bucketPosUpper
	) {

		// Sign the field as an active one
		displayData_p->gamePlay.isActive = true;

		// Copy the data fields
		for (uint8_t rowNumber = 0; rowNumber < BANANA_MATRIX_HEIGHT; rowNumber++)
			for (uint8_t coloumnNumber = 0; coloumnNumber < BANANA_MATRIX_WIDTH; coloumnNumber++)
				displayData_p->gamePlay.bananaMatrix[rowNumber][coloumnNumber] = bananaMatrix[rowNumber][coloumnNumber];
		displayData_p->gamePlay.bucketPosLower = bucketPosLower;
		displayData_p->gamePlay.bucketPosUpper = bucketPosUpper;
	}

	// Set the Points of the DisplayData
	void DisplayData_setPoints(struct DisplayData* const displayData_p, const uint8_t max, const uint8_t current) {

		// Sign the field as an active one
		displayData_p->points.isActive = true;

		// Copy the data fields
		displayData_p->points.current = current;
		displayData_p->points.max = max;
	}

	// Set the Text of the DisplayData
	void DisplayData_setText(struct DisplayData* const displayData_p, const char* const text) {

		// Sign the field as an active one
		displayData_p->text.isActive = true;

		// Copy the data fields
		for (uint8_t charNumber = 0; charNumber < LOWER_SEGMENT_WIDTH; charNumber++)
			displayData_p->text.text[charNumber] = text[charNumber];
	}
