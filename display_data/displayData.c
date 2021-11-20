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
		SegmentLCD_ARing(displayData->difficulty.difficulty, 1);
	}

	if(displayData->gamePlay.isActive){
		SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[7];								//initialize variable --
		lowerCharSegments[displayData->gamePlay.bucketPosLower].BUCKET_POS_LOWER = 0;			//-- based on position of buckets --
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_LEFT_SEGMENT = 0;
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_RIGHT_SEGMENT = 0;
		for(int i = 0; i < BANANA_MATRIX_WIDTH; i++){											//-- and position of bananas
			if(displayData->gamePlay.bananaMatrix[0][i] == 1)
				lowerCharSegments[i].BANANA_POS_TOP = 0;
			if(displayData->gamePlay.bananaMatrix[1][i] == 1)
				lowerCharSegments[i].BANANA_POS_MIDDLE = 0;
			if(displayData->gamePlay.bananaMatrix[2][i] == 1)
				lowerCharSegments[i].BANANA_POS_BOTTOM = 0;
		}
		SegmentLCD_LowerSegments(&lowerCharSegments);			//update lower segments of lcd with the initialized variable
	}
}


