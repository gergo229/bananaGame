// Includes
#include <stdint.h>
#include "segmentlcd.h"
#include "displayData.h"
#include "../../segmentlcd/segmentlcd_individual.h"


void displayData(const struct DisplayData* const displayData){
	char LowerSegments[LOWER_SEGMENT_LENGTH];
	char UpperSegments[4];
	SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[7];
	SegmentLCD_AllOff();
	if(displayData->text.isActive){
		SegmentLCD_Write(displayData->text.text);
	}
	if(displayData->points.isActive){
		SegmentLCD_Symbol(LCD_SYMBOL_COL10, 1);
		SegmentLCD_Write((uint16_t) displayData->points.max * 100 + (uint16_t)displayData->points.current);
	}
	if(displayData->difficulty.isActive){
		SegmentLCD_ARing(displayData->difficulty.difficulty, 1);
	}

	if(displayData->gamePlay.isActive){
		lowerCharSegments[displayData->gamePlay.bucketPosLower].BUCKET_POS_LOWER = 0;
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_LEFT_SEGMENT = 0;
		lowerCharSegments[displayData->gamePlay.bucketPosUpper].BUCKET_POS_UPPER_RIGHT_SEGMENT = 0;
		for(int i = 0; i < LOWER_SEGMENT_LENGTH; i++){
			if(displayData->gamePlay.bananaMatrix[0][i] == 1)
				lowerCharSegments[i].BANANA_POS_TOP = 0;
			if(displayData->gamePlay.bananaMatrix[1][i] == 1)
				LowerCharSegments[i].BANANA_POS_MIDDLE = 0;
			if(displayData->gamePlay.bananaMatrix[2][i] == 1)
				lowerCharSegments[i].BANANA_POS_BOTTOM = 0;
		}
	}
}

void lowerBucketPositionToSegments(uint8_t position, const SegmentLCD_LowerCharSegments_TypeDef* charSegments){
	//charSegments[position]->d = 0;
}


