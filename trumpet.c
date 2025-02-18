#include "msp.h"
#include "trumpet.h"


uint16_t songID = 1;
const uint16_t numberOfSongs = 2;

void debounce(void)
{
    volatile uint32_t delay = 0;
    for (delay = 50000; delay > 0; delay--);
} //end debounce()


/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer


	SwitchConfiguration();

	configHFXT();
//	configLFXT();

	speaker_init();

	lcd8bits_init();

	NoteDurationConfiguration();

	PlayNote(NOTEA3);

	__enable_irq();

	while (1) {}
}
