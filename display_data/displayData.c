// Includes
#include <stdint.h>
#include "segmentlcd.h"
#include "displayData.h"


void displayData(struct DisplayData* displayData){
	if(displayData->difficulty.isActive){
	}
	if(displayData->text.isActive){
		SegmentLCD_Write(displayData->text.text);
	}
}

