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

/// Main functions

    // Functions of BananaGameStateMachine
        // Constructor of the BananaGameStateMachine
        void BananaGameStateMachine_construct(struct BananaGameStateMachine* const newBananaGameStateMachine_p) {
            
            // Set the initial state
            newBananaGameStateMachine_p->actualState = STATE_SETUP;            //the initial state is Setup

            // Construct states' data (allocate memory for them, they will be initialized at state changes)
            newBananaGameStateMachine_p->states[STATE_SETUP].data = malloc(sizeof(struct BananaGameStateMachine_SetupState_Data));
            newBananaGameStateMachine_p->states[STATE_FINISH].data = malloc(sizeof(struct BananaGameStateMachine_GameState_Data));
            newBananaGameStateMachine_p->states[STATE_GAME].data = malloc(sizeof(struct BananaGameStateMachine_FinishState_Data));
        
            // Set the action function pointers (to functions defined before to the desired work)
            newBananaGameStateMachine_p->states[STATE_SETUP].action = BananaGameStateMachine_SetupState_Action;
            newBananaGameStateMachine_p->states[STATE_FINISH].action = BananaGameStateMachine_GameState_Action;
            newBananaGameStateMachine_p->states[STATE_GAME].action = BananaGameStateMachine_FinishState_Action;

            // Set the step in action function pointers (to functions defined before to the desired work)
			newBananaGameStateMachine_p->states[STATE_SETUP].stepInAction = BananaGameStateMachine_SetupState_StepInAction;
			newBananaGameStateMachine_p->states[STATE_FINISH].stepInAction = BananaGameStateMachine_GameState_StepInAction;
			newBananaGameStateMachine_p->states[STATE_GAME].stepInAction = BananaGameStateMachine_FinishState_StepInAction;

            // Set the switching function pointers (to functions defined before to the desired work)
            newBananaGameStateMachine_p->states[STATE_SETUP].newState = BananaGameStateMachine_SetupState_NewState;
            newBananaGameStateMachine_p->states[STATE_FINISH].newState = BananaGameStateMachine_GameState_NewState;
            newBananaGameStateMachine_p->states[STATE_GAME].newState = BananaGameStateMachine_FinishState_NewState;
        }

        // Destructor of the BananaGameStateMachine
        void BananaGameStateMachine_destruct(struct BananaGameStateMachine* const oldBananaGameStateMachine_p) {
            
            // Free states' data's memory space
            free(oldBananaGameStateMachine_p->states[STATE_SETUP].data);
            free(oldBananaGameStateMachine_p->states[STATE_SETUP].data);
            free(oldBananaGameStateMachine_p->states[STATE_SETUP].data);
        }

        // State switching function of BananaGameStateMachine (performs the state switch)
        void BananaGameStateMachine_switchState(
        		struct BananaGameStateMachine* actualBananaGameStateMachine_p,
				const struct AllProcessedInputData* const allProcessedInputData_p
		) {
            
            // Call the actual state' state switching function (and store the new state)
                enum BananaGameStateMachine_StateName actualState = actualBananaGameStateMachine_p->actualState;
                actualBananaGameStateMachine_p->actualState =
                	actualBananaGameStateMachine_p->states[actualState].newState(
                			actualBananaGameStateMachine_p,
							allProcessedInputData_p
                	);
        }

        // Acting function of BananaGameStateMachine
        void BananaGameStateMachine_act(
                struct BananaGameStateMachine* const actualBananaGameStateMachine_p,
                const struct AllProcessedInputData* const allProcessedInputData_p,
                struct DisplayData* const displayData_p
            ) {
            
            	//Call the actual state's action function
                	enum BananaGameStateMachine_StateName actualState = actualBananaGameStateMachine_p->actualState;
                	actualBananaGameStateMachine_p->states[actualState].action(
                			actualBananaGameStateMachine_p->states[actualState],
							allProcessedInputData_p,
							displayData_p
                	);
        }
