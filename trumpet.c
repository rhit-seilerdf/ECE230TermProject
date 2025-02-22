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
	lcd_clear();
    lcd_SetLineNumber(FirstLine);
	lcd_home();
    lcd_puts(SongNames[songID]);

//	NoteDurationConfiguration();


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
