/*
*   Main source file BananaCooperativeMultiplayerGame
*/

/// Includes
    #include "input/input_handler/inputHandler.h"   //for handling the physical inputs
    #include "state_machine/banana_game_state_machine/bananaGameStateMachine.h"         //for the state machine of the program
    #include "display_data/displayData.h"       //for displayment of the output data

/// The main function

int main (void) {

    // Create the statemachine
        struct BananaGameStateMachine bananagameStateMachine;
        BananaGameStateMachine_construct(&bananagameStateMachine);

    // Create the input data structure
    struct AllProcessedInputData allProcessedInputData = ALL_PROCESSED_INPUT_DATA_DEFAULT;

    // Create the output (display) structure
    struct DisplayData displayData;

    // The superloop
    while (1) {

        // Read inputs
        checkInputsAndProcess(&allProcessedInputData);

        // State machine cycle
            BananaGameStateMachine_act(
                &bananagameStateMachine,
                (const struct AllProcessedInputData*) &allProcessedInputData,
                &displayData
            );
            BananaGameStateMachine_switchState(&bananagameStateMachine);

        // Display the output data
        displayData((const struct DisplayData*) &displayData);
    }
    
    // here the program won't come... - while(1)

    // Destruct the statemachine
    BananaGameStateMachine_destruct(&bananagameStateMachine);

    return 0;
}
