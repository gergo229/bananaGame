/*
*   Header file for BananaGameStateMachine
*/

#ifndef BANANA_GAME_STATE_MACHINE_H_
#define BANANA_GAME_STATE_MACHINE_H_

/// Includes
    // In-out data headers
        #include "../../display_data/displayData.h"    //the output data (this will be displayed later)
		#include "../../input/input_handler/inputHandler.h"      //the input data (this comes from physical inputs)

	// Standard C headers
		#include <stdint.h>		//for precise sized (with given bits) integers

/// Constants
	// State's constants (used over more states)
		#define DIFFICULTY_MAX 100 		//the maximum difficulty level
		#define DIFFICULTY_DEFAULT 30	//the default difficulty level

/// Types

	// Declaration of DisplayData structure (defined in DisplayData.h, just needed here because of cross including)
	struct DisplayData;

	// Enumeration for the names of states in BananaGameStateMachine
    enum BananaGameStateMachine_StateName {STATE_SETUP, STATE_GAME, STATE_FINISH};

    // Declaration of BananaGameStatmachine structure
    // (BananaGameStatmachine_State uses this as a field type)
    struct BananaGameStateMachine;

    // State structure for BananaGameStateMachine
    struct BananaGameStateMachine_State {
        
    	// The additional action to do when step in to the state
    	void (*stepInAction) (struct BananaGameStateMachine* const currentBananaGameStateMachine_p);

    	// The action to do when in the state
        void (*action)(
        		struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
                const struct AllProcessedInputData* const inputData_p, 
                struct DisplayData* const displayData_p
        );
        
        // The state's data
        void* data;

        // Determines, to which state go and does it
        void (*newState)(
        		struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
        		const struct AllProcessedInputData* const inputData_p
        );

    };

    // The BananaGameStateMachine structure
    struct BananaGameStateMachine {

        // Data about states
            struct BananaGameStateMachine_State states[3];
            enum BananaGameStateMachine_StateName currentState;
    };

/// Functions
    // Constructor of the BananaGameStateMachine
    void BananaGameStateMachine_construct(struct BananaGameStateMachine* const newBananaGameStateMachine_p);
    
    // Destructor of the BananaGameStateMachine
    void BananaGameStateMachine_destruct(struct BananaGameStateMachine* const oldBananaGameStateMachine_p);
    
    // State switching function of BananaGameStateMachine (performs the state switch)
    void BananaGameStateMachine_switchState(
    		struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
			const struct AllProcessedInputData* const allProcessedInputData_p
	);

    // Acting function of BananaGameStateMachine
    void BananaGameStateMachine_act(
        struct BananaGameStateMachine* const currentBananaGameStateMachine_p,
        const struct AllProcessedInputData* const allProcessedInputData_p,
        struct DisplayData* const displayData_p    
    );

#endif /* BANANA_GAME_STATE_MACHINE_H_ */
