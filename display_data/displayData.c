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
	}															// convert max and current point into one 4 digit number and print to lcd
	if(displayData->difficulty.isActive){
		for(int i = 0; i < displayData->difficulty.difficulty; i++)
			SegmentLCD_ARing(i, 1);
	}

	if(displayData->gamePlay.isActive){
		SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[LOWER_SEGMENT_WIDTH];
		for(int i = 0; i < BANANA_MATRIX_WIDTH; i++){											//-- and position of bananas
			lowerCharSegments[i].raw = 0;
		}				//initialize variable --
		lowerCharSegments[displayData->gamePlay.bucketPosLower + 1].BUCKET_POS_LOWER = 1;			//-- based on position of buckets --
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_LEFT_SEGMENT = 1;
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_RIGHT_SEGMENT = 1;
		for(int i = 0; i < BANANA_MATRIX_WIDTH; i++){											//-- and position of bananas
			if(displayData->gamePlay.bananaMatrix[0][i] == 1)
				lowerCharSegments[i].BANANA_POS_TOP = 1;
			if(displayData->gamePlay.bananaMatrix[1][i] == 1)
				lowerCharSegments[i].BANANA_POS_MIDDLE = 1;
			if(displayData->gamePlay.bananaMatrix[2][i] == 1)
				lowerCharSegments[i].BANANA_POS_BOTTOM = 1;
		}
		SegmentLCD_LowerSegments(&lowerCharSegments);			//update lower segments of lcd with the initialized variable
	}
}

// Constructor for displayData. Calloc function is used, because the fields need to be initialized to 0
struct DisplayData* constructDisplayData(){
	struct DisplayData* displayData = calloc(1, sizeof(struct DisplayData));
	for(int i = 0; i < BANANA_MATRIX_HEIGHT; i++)
			for(int l = 0; l < BANANA_MATRIX_WIDTH; l++)
				displayData->gamePlay.bananaMatrix[i][l] = -1;
	return displayData;
	//displayData = malloc(sizeof(struct DisplayData));
//	displayData->difficulty.difficulty = 5;
//		displayData->difficulty.isActive = 1;
//	displayData->difficulty = calloc(1, sizeof(struct Difficulty));
//	displayData->gamePlay = calloc(1, sizeof(struct GamePlay));
//	displayData->points = calloc(1, sizeof(struct Points));
//	displayData->text = calloc(1, sizeof(struct Text));
}

// Destructor for displayData
void destructDisplayData(struct DisplayData* displayData){
//	free(displayData->difficulty);
//	free(displayData->gamePlay);
//	free(displayData->points);
//	free(displayData->text);
	free(displayData);
}

void initializeDisplayData(struct DisplayData* displayData){
	//displayData = malloc(sizeof(struct DisplayData));
	struct DisplayData d= {.difficulty.difficulty = 0,.difficulty.isActive = 0, .points.max = 0, .points.current = 0, .points.isActive = 0, \
			.text.text = "", .text.isActive = 0, .gamePlay.bucketPosLower = 0, .gamePlay.bucketPosUpper = 0,  .gamePlay.isActive = 0};
	for(int i = 0; i < BANANA_MATRIX_HEIGHT; i++)
		for(int l = 0; l < BANANA_MATRIX_WIDTH; l++)
			d.gamePlay.bananaMatrix[i][l] = 0;
	*displayData = d;
}

