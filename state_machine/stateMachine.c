/*
 * ...
 */

/// Includes
#include <stdint.h>
#include "stateMachine.h"

struct SettingsStateData {
	uint8_t difficulty;
	uint8_t isMultiplayer;
};

struct GameplayData{
	uint8_t bucketPlayer1;
	uint8_t bucketPlayer2;
	uint8_t maxPoint;
	uint8_t currentPoints;
};

struct State {
	void (*action)(void);
	void* data;
};


struct BananaGameStateMachine {



	struct State states[3];

	struct SettingsStateData settingsStateData;


	enum StateName actualState;

};

//void constructBananaGameStateMachine()

//states[SETTING].data = &settingsStateData;
