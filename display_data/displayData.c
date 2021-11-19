// Includes
#include <stdint.h>
#include "segmentlcd.h"
#include "displayData.h"
#include "../../segmentlcd/segmentlcd_individual.h"


void displayData(const struct DisplayData* const displayData){
	char LowerSegments[7];
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
		lowerCharSegments[displayData->gamePlay.bucketPositionPlayer1].d = 0;
		lowerCharSegments[displayData->gamePlay.bucketPositionPlayer2].g = 0;
		lowerCharSegments[displayData->gamePlay.bucketPositionPlayer2].m = 0;
		lowerCharSegments[displayData->gamePlay.bananaTreePosition].a = 0;
	}
}

void lowerBucketPositionToSegments(uint8_t position, const SegmentLCD_LowerCharSegments_TypeDef* charSegments){
	//charSegments[position]->d = 0;
}


