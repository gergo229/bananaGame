// Configuration file for banana_cooperative_multiplayer_game

// Includes

	//Own header
	#include "config.h"

	//Headers for LCD
	#include "segmentlcd.h"

	//EM headers
	#include "em_cmu.h"
	#include "em_usart.h"
	#include "em_gpio.h"

	//Touch slider's header
	#include "../touch_slider/touch.h"

// Defines
#define SYSTICKDIVIDER 1000 //clock divider for system timer time

// Configure the GPIO peripheral
void configGpio() {

	// Add clock signal
	CMU_ClockEnable(cmuClock_GPIO, true);
}

// Configure the UART peripheral
// UART1 is connected to Expansion Headers,
// that is used.
void configUART() {

	// Add clock signaL
	CMU_ClockEnable(cmuClock_UART1, true);

	// Set the parameters of the UART communication (with defaults)
	USART_InitAsync_TypeDef UART1_init = USART_INITASYNC_DEFAULT;
	USART_InitAsync(UART1, &UART1_init);

	// Configure the UART1 RX pin
	// locate it to PD1, to the ExpansionHeader pin 6 (top row, 3rd from bottom)
	GPIO_PinModeSet(gpioPortD, 1, gpioModeInput, 0);	//0: with no glitch filtering
	UART1->ROUTE |= UART_ROUTE_LOCATION_LOC1;	//set the RX pin to Location 1 (so PD1)
	UART1->ROUTE |= UART_ROUTE_RXPEN;		//enable the RX port
}

// Configure the touch slider
void configTouchSlider(void) {
	Touch_Init();
}

// Configure all used peripherals of the project
int configAll() {

	configGpio();
	configUART();
	SegmentLCD_Init(false);		//configure the LCD
	configTouchSlider();
	SysTick_Config(SystemCoreClock/SYSTICKDIVIDER);		//configure the system timer

	return 0;
}
