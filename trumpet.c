#include "msp.h"
#include "trumpet.h"


uint16_t songID = 1;
const uint16_t numberOfSongs = 2;

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

//	NoteDurationConfiguration();

	lcd_SetLineNumber(FirstLine);
	lcd_puts(SongNames[songID]);
	ButtonInit();


	__enable_irq();

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
