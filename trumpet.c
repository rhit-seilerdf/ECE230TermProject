/**
 *
 * trumpet.c
 *
 *  Created on: Feb 14, 2025
 *      Author: mortonip, seilerdf
 *
 *      Contains main code.
 *
 *      - Initialize LCD, buttons, speaker, clocks
 *      - Allow interrupts to handle active behavior
 *      - Print button presses, for debugging.
 */

#include "msp.h"
#include "trumpet.h"

enum Status {NO, YES};
extern char NewNotePressed;
extern char FoundNote;
extern char NewButtonPressed;
extern char FoundButton;




/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer



	configHFXT();
	configLFXT();


	speaker_init();

	lcd8bits_init();
    lcd_SetLineNumber(FirstLine);
    lcd_puts(SongNames[songID]);

//	NoteDurationConfiguration();


	ButtonInit();


	__enable_irq();

	/**
	 * Allow interrupts to handle behavior. Print found note/jukebox button presses.
	 */
	while (1) {
	    if(NewNotePressed==YES) {
	                NewNotePressed=NO;
	                printf("Note Found: %d \r\n", FoundNote);
	            }

	    if(NewButtonPressed==YES) {
	                        NewButtonPressed=NO;
	                        printf("Button Found: %d \r\n", FoundButton);
	                    }
	}
}
