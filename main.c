#include "config/config.h"	//for eternal configuration
#include "input/input_handler/inputHandler.h"	//for handling the inputs
#include "segmentlcd.h"
#include "display_data/displayData.h"

volatile struct InputITFlags inputITFlags;	//a global structure, to indicate changing in inputs

int main(void) {

	configAll();

	struct DisplayData displaydata;
	InitializeDisplayData(&displaydata);
	//initializie displaydata with values
	DisplayData_setDifficulty(&displaydata, 1);

//	displaydata.difficulty.difficulty = 5;
//	displaydata.difficulty.isActive = 1;
//	SegmentLCD_Number(displaydata.difficulty.difficulty);

	DisplayData_setPoints(&displaydata, 3, 5);
//	displaydata.points.current = 10;
//	displaydata.points.max = 11;
//	displaydata.points.isActive = 1;

	//DisplayData_setText(&displaydata, "alma");

//	char alma[7] = "alamspi";
//	strcpy(displaydata.text.text, alma);
//	displaydata.text.isActive = 0;
	struct BananaMatrix bananaMatrix;
	for(int rows = 0; rows<BANANA_MATRIX_HEIGHT; rows++)
		for(int columns = 0; columns < BANANA_MATRIX_HEIGHT; columns++)
			bananaMatrix.matrix[rows][columns]= 0;
	bananaMatrix.matrix[1][3] = 1;
	DisplayData_setGamePlay(&displaydata, &bananaMatrix, 2, 4);
//	displaydata.gamePlay.bucketPosUpper = 1;
//	displaydata.gamePlay.bananaMatrix[1][3]=1;
//	displaydata.gamePlay.isActive = 1;

	displayData(&displaydata);

	while(1) {


	}

	return 0;
}
