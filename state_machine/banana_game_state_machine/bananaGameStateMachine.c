/*
 *  Source file for BananaGameStateMachine
 *  (implements its member functions)
 */

/// Includes
    // Own header
    #include "bananaGameStateMachine.h"

    // State specific headers
        #include "setup_state.h"
        #include "game_state.h"
        #include "finish_state.h"
    
    // In-out data headers
        #include "../../display_data/displayData.h"    //the output data (this will be displayed later)
        #include "../../input/inputHandler.h"      //the input data (this comes from physical inputs)

/// Main functions

    // Functions of BananaGameStateMachine
        // Constructor of the BananaGameStateMachine
        void BananaGameStateMachine_construct(struct BananaGameStateMachine* const newBananaGameStateMachine_p) {
            
            // Set the initial state
            newBananaGameStateMachine_p->actualState = SETUP;            //the initial state is Setup

            // Construct states' data (allocate memory for them, they will be initialized at state changes)
            newBananaGameStateMachine_p->states[SETUP].data = malloc(sizeof(struct BananaGameStateMachine_SetupStateData));
            newBananaGameStateMachine_p->states[FINISH].data = malloc(sizeof(struct BananaGameStateMachine_GameStateData));
            newBananaGameStateMachine_p->states[GAME].data = malloc(sizeof(struct BananaGameStateMachine_FinishStateData));
        
            // Set the action function pointers (to functions defined before to the desired work)
            newBananaGameStateMachine_p->states[SETUP].action = BananaGameStateMachine_SetupStateAction;
            newBananaGameStateMachine_p->states[FINISH].action = BananaGameStateMachine_GameStateAction;
            newBananaGameStateMachine_p->states[GAME].action = BananaGameStateMachine_FinishStateAction;

            // Set the switching function pointers (to functions defined before to the desired work)
            newBananaGameStateMachine_p->states[SETUP].newState = BananaGameStateMachine_SetupStateNewState;
            newBananaGameStateMachine_p->states[FINISH].newState = BananaGameStateMachine_GameStateNewState;
            newBananaGameStateMachine_p->states[GAME].newState = BananaGameStateMachine_FinishStateNewState;
        }

        // Destructor of the BananaGameStateMachine
        void BananaGameStateMachine_destruct(struct BananaGameStateMachine* const oldBananaGameStateMachine_p) {
            
            // Free states' data's memory space
            free(oldBananaGameStateMachine_p->states[SETUP].data);
            free(oldBananaGameStateMachine_p->states[SETUP].data);
            free(oldBananaGameStateMachine_p->states[SETUP].data);
        }

        // State switching function of BananaGameStateMachine (performs the state switch)
        void BananaGameStateMachine_switchState(struct BananaGameStateMachine* actualBananaGameStateMachine_p) {
            
            // Call the actual state' state switching function
                enum BananaGameStateMachine_StateName actualState = actualBananaGameStateMachine_p->actualState;
                actualBananaGameStateMachine_p->states[actualState].newState();
        }

        // Acting function of BananaGameStateMachine
        void BananaGameStateMachine_act(struct BananaGameStateMachine* actualBananaGameStateMachine_p) {
            
            //Call the actual state's action function
                enum BananaGameStateMachine_StateName actualState = actualBananaGameStateMachine_p->actualState;   
                actualBananaGameStateMachine_p->states[actualState].action();
        }
