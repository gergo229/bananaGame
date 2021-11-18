/*
*   Header file for BananaGameStateMachine C class
*/

#ifndef BANANA_GAME_STATE_MACHINE_H_
#define BANANA_GAME_STATE_MACHINE_H_

/// Types
    // Enum for the names of states in BananaGameStateMachine
    enum BananaGameStateMachine_StateName {SETUP, GAME, FINISH};

    // State structure for BananaGameStateMachine
    struct BananaGameStateMachine_State {
        void (*action)(void);   //the action to do when in the state
        void* data;     //the state's data
        //enum BananaGameStateMachine_StateName (*newState)(void);     //determines, to which state go (can be the same)
        int newState;
    };

    // The BananaGameStateMachine structure
    struct BananaGameStateMachine {

        // Data about states
            struct BananaGameStateMachine_State states[3];
            enum BananaGameStateMachine_StateName actualState;  
    };
    
//    struct SettingsStateData {
//    	uint8_t difficulty;
//    	uint8_t isMultiplayer;
//    };
//
//    struct GameplayData{
//    	uint8_t bucketPlayer1;
//    	uint8_t bucketPlayer2;
//    	uint8_t maxPoint;
//    	uint8_t currentPoints;
//    };

#endif /* BANANA_GAME_STATE_MACHINE_H_ */
