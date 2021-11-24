// Includes
#include <stdint.h>
#include "segmentlcd.h"
#include "displayData.h"
#include "../../segmentlcd/segmentlcd_individual.h"
#include <stdbool.h>
#include "../state_machine/game_state/gameLogic.h"		//for getting data from gameLogic
#include "em_core.h"

// Update lcd based on data in displayData variable
void DisplayData_displayData(const struct DisplayData* const displayData){


	if(displayData->text.isActive){								//update lcd with text if property is active
		SegmentLCD_Write(displayData->text.text);
	}

	if(displayData->points.isActive){
		SegmentLCD_Symbol(LCD_SYMBOL_COL10, 1);
		SegmentLCD_Number((uint16_t) (displayData->points.current) * 100 + (uint16_t)(displayData->points.max));
	}
	else {
		SegmentLCD_Symbol(LCD_SYMBOL_COL10, 0);
		SegmentLCD_NumberOff();
	}

	// convert max and current point into one 4 digit number and print to lcd
	if(displayData->difficulty.isActive){
		int i;
		for(i = 0; i < displayData->difficulty.difficulty + 1; i++)
			SegmentLCD_ARing(i, 1);
		for(i = displayData->difficulty.difficulty + 1; i < MAX_DIFFICULTY + 1; i++)
			SegmentLCD_ARing(i, 0);
	}
	else {
		for(int i = 0; i < MAX_DIFFICULTY + 1; i++)
			SegmentLCD_ARing(i, 0);
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
				lowerCharSegments[i].BANANA_POS_TOP = displayData->gamePlay.bananaMatrix.matrix[2][i];
				lowerCharSegments[i].BANANA_POS_MIDDLE = displayData->gamePlay.bananaMatrix.matrix[1][i];
				lowerCharSegments[i].BANANA_POS_BOTTOM = displayData->gamePlay.bananaMatrix.matrix[0][i];
		}
		SegmentLCD_LowerSegments((SegmentLCD_LowerCharSegments_TypeDef*) &lowerCharSegments);			//update lower segments of lcd with the initialized variable
	}

	if (displayData->gamePlay.isActive && displayData->text.isActive){
		SegmentLCD_Write("");
	}
}

// Initialize displayData with nonset values
void InitializeDisplayData(struct DisplayData* const displayData_p){
	struct DisplayData displayData = {.gamePlay.bucketPosLower = IS_NOT_SET, .gamePlay.bucketPosLower = IS_NOT_SET, \
			.difficulty.isActive = 0, .gamePlay.isActive = 0, .points.isActive = 0, .text.isActive = 0};
	*displayData_p = displayData;
}


/// Setter functions of DisplayData structure

	// Set the difficulty of the DisplayData
	void DisplayData_setDifficulty(struct DisplayData* const displayData_p, const float difficulty) {

		// Sign the field as an active one
		displayData_p->difficulty.isActive = true;

		// Copy the data fields
		displayData_p->difficulty.difficulty = (uint8_t)((difficulty * MAX_DIFFICULTY));
	}

	// Set the GamePlay of the DisplayData
	void DisplayData_setGamePlay(
		struct DisplayData* const displayData_p,
		const struct Banana* const bananas,
		const uint8_t bucketPosLower,
		const uint8_t bucketPosUpper
	) {

		// Sign the field as an active one
			displayData_p->gamePlay.isActive = true;

		// Generate the banana fields

			// Go through all elements of the banana matrix, and null them
			// (later only not null elements will be updated)
				for (unsigned int rowIndex = 0; rowIndex < BANANA_MATRIX_HEIGHT; rowIndex++)
					for (unsigned int coloumnIndex = 0; coloumnIndex < BANANA_MATRIX_WIDTH; coloumnIndex++)
						displayData_p->gamePlay.bananaMatrix.matrix[rowIndex][coloumnIndex] = 0;

			for (unsigned int bananaIndex = 0; bananaIndex < NUMBER_OF_BANANAS; bananaIndex++) {	//go through all bananas

				if (bananas[bananaIndex].state != NONEXISTENT) {	//if the banana should be on display (so not in nonexistent state)
					displayData_p->gamePlay.bananaMatrix.matrix
						[bananas[bananaIndex].position.y][bananas[bananaIndex].position.x] = 1;		//set the appropriate bit
				}
			}

		// Copy bucket fields
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

	// Set the Text of the DisplayData (passed parameter "text" needs to consist of 7 char-s)
	void DisplayData_setText(struct DisplayData* const displayData_p, const char* const text) {

		// Sign the field as an active one
		displayData_p->text.isActive = true;

		// Copy the data fields
		for (uint8_t charNumber = 0; charNumber < LOWER_SEGMENT_WIDTH; charNumber++)
			displayData_p->text.text[charNumber] = text[charNumber];
	}

	// Set all display structures inactive
	void DisplayData_setAllInactive(struct DisplayData* const displayData_p){
		displayData_p->difficulty.isActive = false;
		displayData_p->gamePlay.isActive = false;
		displayData_p->points.isActive = false;
		displayData_p->text.isActive = false;
	}
