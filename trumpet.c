#include "msp.h"
#include "trumpet.h"

void debounce(void)
{
    volatile uint32_t delay = 0;
    for (delay = 50000; delay > 0; delay--)
        ;
} //end debounce()

void SwitchConfiguration(void)
{
    SwitchPort->DIR &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
    SwitchPort->REN |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
    SwitchPort->OUT |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);

    JukeboxPort->DIR &= ~(PPbutton | SKIPbutton | SONGUP | SONGDOWN);
    JukeboxPort->REN |= (PPbutton | SKIPbutton | SONGUP | SONGDOWN);
    JukeboxPort->OUT |= (PPbutton | SKIPbutton | SONGUP | SONGDOWN);
}

/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer


	SwitchConfiguration();

	speaker_init();

	lcd8bits_init();

	NoteDurationConfiguration();

	PlayNote(NOTEA4);

	__enable_irq();

}
