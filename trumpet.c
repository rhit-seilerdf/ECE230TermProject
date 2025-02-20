#include "msp.h"
#include "trumpet.h"


uint16_t songID = 1;
const uint16_t numberOfSongs = 2;

enum Status {NO, YES};
extern char NewNotePressed;
extern char FoundNote;
extern char NewButtonPressed;
extern char FoundButton;

void playTrumpetNote(char FoundNote)
{
    unsigned int noteToPlay;
    switch (FoundNote) {
        case 1: noteToPlay = NOTEC4;
                        break;
        case 2: noteToPlay = NOTEG4;
                        break;
        case 3: noteToPlay = NOTEC5;
                        break;
        case 4: noteToPlay = NOTEA3;
                        break;
        case 5: noteToPlay = NOTEE4;
                        break;
        case 6: noteToPlay = NOTEA4;
                        break;
        case 7: noteToPlay = NOTEB3;
                        break;
        case 8: noteToPlay = NOTEF4s;
                        break;
        case 9: noteToPlay = NOTEB4;
                        break;
        case 10: noteToPlay = NOTEA4f;
                        break;
        case 11: noteToPlay = NOTEG4s;
                        break;
        case 12: noteToPlay = NOTEA4f;
                        break;
        case 13: noteToPlay = NOTEB3f;
                        break;
        case 14: noteToPlay = NOTEF4;
                        break;
        case 15: noteToPlay = NOTEB4f;
                        break;
        case 16: noteToPlay = NOTEG3;
                        break;
        case 17: noteToPlay = NOTED4;
                        break;
        case 18: noteToPlay = NOTED5;
                        break;
        case 19: noteToPlay = NOTEA3;
                        break;
        case 20: noteToPlay = NOTEE4;
                        break;
        case 21: noteToPlay = NOTEA4;
                        break;
        case 22: noteToPlay = NOTEE5;
                        break;
        case 23: noteToPlay = NOTEF5;
                    break;
        case 24: noteToPlay = NOTEG5;
                    break;
        default: noteToPlay = RestNote;
            break;
    }
    PlayNote(noteToPlay);
}


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
	                playTrumpetNote(FoundNote);
	            }

	    if(NewButtonPressed==YES) {
	                        NewButtonPressed=NO;
	                        printf("Button Found: %d \r\n", FoundButton);
	                    }
	}
}
