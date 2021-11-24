/*
*   Main source file BananaCooperativeMultiplayerGame
*/

/// Includes
	#include "config/config.h"	//for eternal configuration
	#include "input/input_handler/inputHandler.h"   //for handling the physical inputs
    #include "state_machine/banana_game_state_machine/bananaGameStateMachine.h"         //for the state machine of the program
    #include "display_data/displayData.h"       //for displaying the output data

/// Global variables
	volatile struct InputITFlags inputITFlags;	//global structure, to indicate changes in input states
		//changed by ITs, so needs to be volatile

/// The main function

	int main (void) {

		// Configure every peripheral
			configAll();

		// Create the statemachine
			struct BananaGameStateMachine bananaGameStateMachine;
			BananaGameStateMachine_construct(&bananaGameStateMachine);

		// Create the input data structure
			struct AllProcessedInputData allProcessedInputData = ALL_PROCESSED_INPUT_DATA_DEFAULT;

		// Create the output (display) structure
			struct DisplayData displayData;

		// The superloop
			while (1) {

				// Read inputs
					checkInputsAndProcess(&allProcessedInputData);

				// State machine acting
					BananaGameStateMachine_act(
						&bananaGameStateMachine,
						(const struct AllProcessedInputData*) &allProcessedInputData,
						&displayData
					);

				// Display the output data
					DisplayData_displayData((const struct DisplayData*) &displayData);

				// State machine's state switching
					BananaGameStateMachine_switchState(
						&bananaGameStateMachine,
						(const struct AllProcessedInputData*) &allProcessedInputData
					);
			}

		// here the program won't come... - while(1) doen't let it

		// Destruction of the statemachine
		BananaGameStateMachine_destruct(&bananaGameStateMachine);

		return 0;
	}
