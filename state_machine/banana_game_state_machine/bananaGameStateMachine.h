/*
*   Header file for BananaGameStateMachine
*/

#ifndef BANANA_GAME_STATE_MACHINE_H_
#define BANANA_GAME_STATE_MACHINE_H_

/// Includes
    // In-out data headers
        #include "../../display_data/displayData.h"    //the output data (this will be displayed later)
		#include "../../input/input_handler/inputHandler.h"      //the input data (this comes from physical inputs)

/// Types
    // Enum for the names of states in BananaGameStateMachine
    enum BananaGameStateMachine_StateName {SETUP, GAME, FINISH};

    // State structure for BananaGameStateMachine
    struct BananaGameStateMachine_State {
        
    	// The additional action to do when step in to the state
    	void (*stepInAction) (struct BananaGameStateMachine_State* const actualBananaGameStateMachine_State_p);

    	// The action to do when in the state
        void (*action)(
        		struct BananaGameStateMachine_State* const actualBananaGameStateMachine_State_p,
                const struct AllProcessedInputData* const inputData_p, 
                struct DisplayData* const displayData_p
        );
        
        // The state's data
        void* data;

        // Determines, to which state go (can be the same)
        enum BananaGameStateMachine_StateName (*newState)(
        		struct BananaGameStateMachine_State* const actualBananaGameStateMachine_State_p,
        		const struct AllProcessedInputData* const inputData_p
        );

    };

    // The BananaGameStateMachine structure
    struct BananaGameStateMachine {

        // Data about states
            struct BananaGameStateMachine_State states[3];
            enum BananaGameStateMachine_StateName actualState;  
    };

//  State specific headers should contain this
//
//    struct GameplayData{
//    	uint8_t bucketPlayer1;
//    	uint8_t bucketPlayer2;
//    	uint8_t maxPoint;
//    	uint8_t currentPoints;
//    };

/// Functions
    // Constructor of the BananaGameStateMachine
    void BananaGameStateMachine_construct(struct BananaGameStateMachine* const newBananaGameStateMachine_p);
    
    // Destructor of the BananaGameStateMachine
    void BananaGameStateMachine_destruct(struct BananaGameStateMachine* const oldBananaGameStateMachine_p);
    
    // State switching function of BananaGameStateMachine (performs the state switch)
    void BananaGameStateMachine_switchState(struct BananaGameStateMachine* const actualBananaGameStateMachine_p);

    // Acting function of BananaGameStateMachine
    void BananaGameStateMachine_act(
        struct BananaGameStateMachine* const actualBananaGameStateMachine_p,
        const struct AllProcessedInputData* const inputData_p,
        struct DisplayData* const displayData_p    
    );

#endif /* BANANA_GAME_STATE_MACHINE_H_ */
