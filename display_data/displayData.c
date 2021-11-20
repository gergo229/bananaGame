// Includes
#include <stdint.h>
#include "segmentlcd.h"
#include "displayData.h"
#include "../../segmentlcd/segmentlcd_individual.h"

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
	struct DisplayData* displayData = malloc(sizeof(struct DisplayData));
	for(int i = 0; i < BANANA_MATRIX_HEIGHT; i++)				//going through position data
			for(int l = 0; l < BANANA_MATRIX_WIDTH; l++)
				displayData->gamePlay.bananaMatrix[i][l] = -1;	//initialize position data to -1
	displayData->gamePlay.bucketPosLower = -1;
	displayData->gamePlay.bucketPosUpper = -1;

	return displayData;
}

// Destructor for displayData
void destructDisplayData(struct DisplayData* displayData){
	free(displayData);
}


