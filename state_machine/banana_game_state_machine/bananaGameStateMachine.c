/*
 *  Source file for BananaGameStateMachine
 *  (implements its member functions)
 */

/// Includes
    // Own header
    #include "bananaGameStateMachine.h"

    // State specific headers
        #include "../setup_state/setupState.h"
        #include "../game_state/gameState.h"
        #include "../finish_state/finishState.h"
    
    // In-out data headers
        #include "../../display_data/displayData.h"    //the output data (this will be displayed later)
        #include "../../input/input_handler/inputHandler.h"      //the input data (this comes from physical inputs)

	#include <stdlib.h>

/// Main functions

    // Functions of BananaGameStateMachine
        // Constructor of the BananaGameStateMachine
        void BananaGameStateMachine_construct(struct BananaGameStateMachine* const newBananaGameStateMachine_p) {
            
            // Set the initial state
            newBananaGameStateMachine_p->currentState = STATE_SETUP;            //the initial state is Setup

            // Construct states' data (allocate memory for them)
            newBananaGameStateMachine_p->states[STATE_SETUP].data = malloc(sizeof(struct BananaGameStateMachine_SetupState_Data));
            newBananaGameStateMachine_p->states[STATE_GAME].data = malloc(sizeof(struct BananaGameStateMachine_GameState_Data));
            newBananaGameStateMachine_p->states[STATE_FINISH].data = malloc(sizeof(struct BananaGameStateMachine_FinishState_Data));

            // Initialize data of states (this initialization runs once, at the creation of the state machine)
            BananaGameStateMachine_SetupState_Data_initialize(newBananaGameStateMachine_p->states[STATE_SETUP].data);
            BananaGameStateMachine_GameState_Data_initialize(newBananaGameStateMachine_p->states[STATE_GAME].data);
            BananaGameStateMachine_FinishState_Data_initialize(newBananaGameStateMachine_p->states[STATE_FINISH].data);

            // Set the action function pointers (to functions defined before to the desired work)
            newBananaGameStateMachine_p->states[STATE_SETUP].action = BananaGameStateMachine_SetupState_action;
            newBananaGameStateMachine_p->states[STATE_GAME].action = BananaGameStateMachine_GameState_action;
            newBananaGameStateMachine_p->states[STATE_FINISH].action = BananaGameStateMachine_FinishState_action;

            // Set the step in action function pointers (to functions defined before to the desired work)
			newBananaGameStateMachine_p->states[STATE_SETUP].stepInAction = BananaGameStateMachine_SetupState_stepInAction;
			newBananaGameStateMachine_p->states[STATE_GAME].stepInAction = BananaGameStateMachine_GameState_stepInAction;
			newBananaGameStateMachine_p->states[STATE_FINISH].stepInAction = BananaGameStateMachine_FinishState_stepInAction;

            // Set the switching function pointers (to functions defined before to the desired work)
            newBananaGameStateMachine_p->states[STATE_SETUP].newState = BananaGameStateMachine_SetupState_newState;
            newBananaGameStateMachine_p->states[STATE_GAME].newState = BananaGameStateMachine_GameState_newState;
            newBananaGameStateMachine_p->states[STATE_FINISH].newState = BananaGameStateMachine_FinishState_newState;
        }

        // Destructor of the BananaGameStateMachine
        void BananaGameStateMachine_destruct(struct BananaGameStateMachine* const oldBananaGameStateMachine_p) {
            
            // Free states' data's memory space
            free(oldBananaGameStateMachine_p->states[STATE_SETUP].data);
            free(oldBananaGameStateMachine_p->states[STATE_GAME].data);
            free(oldBananaGameStateMachine_p->states[STATE_FINISH].data);
        }

        // State switching function of BananaGameStateMachine (performs the state switch)
        void BananaGameStateMachine_switchState(
        		struct BananaGameStateMachine* currentBananaGameStateMachine_p,
				const struct AllProcessedInputData* const allProcessedInputData_p
		) {
            
            // Call the current state' state switching function (and store the new state)
                enum BananaGameStateMachine_StateName currentState = currentBananaGameStateMachine_p->currentState;
                currentBananaGameStateMachine_p->states[currentState].newState(
                	(struct BananaGameStateMachine* const) currentBananaGameStateMachine_p,
					allProcessedInputData_p
                );
        }

        // Acting function of BananaGameStateMachine
        void BananaGameStateMachine_act(
                struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
                const struct AllProcessedInputData* const allProcessedInputData_p,
                struct DisplayData* const displayData_p
            ) {
            
            	//Call the current state's action function
                	enum BananaGameStateMachine_StateName currentState = currentBananaGameStateMachine_p->currentState;
                	currentBananaGameStateMachine_p->states[currentState].action(
                			currentBananaGameStateMachine_p,
							allProcessedInputData_p,
							displayData_p
                	);
        }

