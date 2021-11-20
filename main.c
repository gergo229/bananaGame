#include "config/config.h"	//for eternal configuration
#include "input/input_handler/inputHandler.h"	//for handling the inputs
#include "segmentlcd.h"
#include "display_data/displayData.h"

volatile struct InputITFlags inputITFlags;	//a global structure, to indicate changing in inputs

int main(void) {

	configAll();

	SegmentLCD_Init(false);
	struct DisplayData displaydata;

	initializeDisplayData(&displayData);
	displaydata.difficulty.difficulty = 5;
	displaydata.difficulty.isActive = 1;
	displaydata.points.current = 10;
	displaydata.points.max = 11;
	displaydata.points.isActive = 1;
	char alma[7] = "alamspi";
	strcpy(displaydata.text.text, alma);
	displaydata.text.isActive = 0;
	displaydata.gamePlay.bucketPosUpper = 1;
	displaydata.gamePlay.bananaMatrix[1][3]=1;
	displaydata.gamePlay.isActive = 1;

	displayData(&displaydata);

	while(1) {


	}

	return 0;
}
