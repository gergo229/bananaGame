
#include "config/config.h"
#include "display_data/displayData.h"
#include "string.h"
#include "segmentlcd.h"

#include "config/config.h"	//for eternal configuration
#include "input/input_handler/inputHandler.h"	//for handling the inputs

volatile struct InputITFlags inputITFlags;	//a global structure, to indicate changing in inputs

int main(void) {

	configAll();
	struct DisplayData data;

	strcpy(data.text.text, "alma");
	data.text.isActive = 1;
	displayData(&data);
	SegmentLCD_Number(6);
	while(1) {

	}

	return 0;
}
