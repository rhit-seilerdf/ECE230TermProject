/*
 * speaker.c
 *
 *  Created on: Feb 18, 2025
 *      Author: seilerdf
 */

#include "buttons.h"
enum Status
{
    NO, YES
};
char NewNotePressed = NO;
char FoundNote;

char NewButtonPressed = NO;
JukeBoxButton FoundButton;
PlayerStatus Player = STOP;

const char NoteBits = (Button1 | Button2 | Button3 | PitchLOW | PitchMID
        | PitchHIGH );
const char Notes[24] =
        { Note1, Note2, Note3, Note4, Note5, Note6, Note7, Note8,
        Note9,
          Note10, Note11, Note12, Note13, Note14, Note15, Note16,
          Note17,
          Note18, Note19, Note20, Note21, Note22, Note23, Note24 };
const char ButtonBits = (PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
const char JukeboxPresses[4] = { PPbuttonPressed, StopPressed, SongUpPressed,
SongDownPressed };
void ButtonInit()
{
    SwitchPort->DIR &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID
            | PitchHIGH );
    SwitchPort->REN |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID
            | PitchHIGH );
    SwitchPort->OUT |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID
            | PitchHIGH );
    SwitchPort->IES |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID
            | PitchHIGH );
    SwitchPort->IE |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID
            | PitchHIGH );
    SwitchPort->IFG &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID
            | PitchHIGH );
    NVIC->ISER[1] |= (1) << (PORT6_IRQn - 32);

    JukeboxPort->DIR &= ~(PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
    JukeboxPort->REN |= (PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
    JukeboxPort->OUT |= (PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
    JukeboxPort->IES |= (PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
    JukeboxPort->IE |= (PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
    JukeboxPort->IFG &= ~(PPbutton | STOPbutton | SONGUPbutton | SONGDOWNbutton );
    NVIC->ISER[1] |= (1) << (PORT3_IRQn - 32);
}

void playTrumpetNote(char FoundNote)
{
    unsigned int noteToPlay;
    switch (FoundNote)
    {
    case 1:
        noteToPlay = NOTEC4;
        break;
    case 2:
        noteToPlay = NOTEG4;
        break;
    case 3:
        noteToPlay = NOTEC5;
        break;
    case 4:
        noteToPlay = NOTEA3;
        break;
    case 5:
        noteToPlay = NOTEE4;
        break;
    case 6:
        noteToPlay = NOTEA4;
        break;
    case 7:
        noteToPlay = NOTEB3;
        break;
    case 8:
        noteToPlay = NOTEF4s;
        break;
    case 9:
        noteToPlay = NOTEB4;
        break;
    case 10:
        noteToPlay = NOTEA3f;
        break;
    case 11:
        noteToPlay = NOTEG4s;
        break;
    case 12:
        noteToPlay = NOTEA4f;
        break;
    case 13:
        noteToPlay = NOTEB3f;
        break;
    case 14:
        noteToPlay = NOTEF4;
        break;
    case 15:
        noteToPlay = NOTEB4f;
        break;
    case 16:
        noteToPlay = NOTEG3;
        break;
    case 17:
        noteToPlay = NOTED4;
        break;
    case 18:
        noteToPlay = NOTEB4;
        break;
    case 19:
        noteToPlay = NOTEA3;
        break;
    case 20:
        noteToPlay = NOTEE4;
        break;
    case 21:
        noteToPlay = NOTEA4;
        break;
    case 22:
        noteToPlay = NOTEE5;
        break;
    case 23:
        noteToPlay = NOTEF5;
        break;
    case 24:
        noteToPlay = NOTEG5;
        break;
    default:
        noteToPlay = RestNote;
        break;
    }
    PlayNote(noteToPlay);
}

void playJukebox(JukeBoxButton FoundButton)
{

    if (FoundButton == PLAYPAUSE)
    {
        if (Player == START) // pause
        { /*
         * TIMER_A0->CTL&=~0b0000000000110000;  //bits 5-4=0b00
         *  TIMER_A1->CTL&=~0b0000000000110000;  //bits 5-4=0b00
         */
            PlayNote(RestNote);
            TIMER_A1->CTL &= ~0b0000000000110000;  //bits 5-4=0b00

            Player = PAUSE;
        }
        else if (Player == PAUSE) // resume
        {
            /*
             * Here is one way to start both timers:
             * TIMER_A0->CTL |=0b0000000000010000;  //bits 5-4=0b01
             * TIMER_A1->CTL |=0b0000000000010000;  //bits 5-4=0b01
             */
            TIMER_A0->CTL |= 0b0000000000010000;  //bits 5-4=0b01
            TIMER_A1->CTL |= 0b0000000000010000;  //bits 5-4=0b01
            Player = START;
        }
        else if (Player == STOP)
        {
            StartSong(songID);
            Player = START;
        }

    }
    else if (FoundButton == STOPSONG)
    {
        StopSong();
        Player = STOP;
    }
    else if (FoundButton == SONGUP)
    {
        SongUp();
    }
    else if (FoundButton == SONGDOWN)
    {
        SongDown();
    }
}

#define DEBOUNCETIME 5000
void debounce(void)
{
    uint16_t delayloop;
    for (delayloop = 0; delayloop < DEBOUNCETIME; delayloop++)
        ; //debounce the key
}

/*
 * Finds note pressed
 */

char FindNote(const char Notes[])
{
    char i;
    char NoteNumber;
    char PortValue;
    for (i = 0; i <= 23; i++)
    {
//output key pattern
        PortValue = SwitchPort->IN;
        if ((PortValue & NoteBits) == (Notes[i] & NoteBits))
        {   //check note press
            debounce();
            if ((PortValue & NoteBits) == (Notes[i] & NoteBits))
            {   //still pressed
                NoteNumber = i + 1;
                playTrumpetNote(NoteNumber);
                while ((PortValue & NoteBits) == (Notes[i] & NoteBits))
                    PortValue = SwitchPort->IN; //wait for release
                PlayNote(RestNote);
                break;
            }
            debounce();
        }
    }
    return NoteNumber;
}

JukeBoxButton FindButton(const char JukeBoxPresses[])
{
    char i;
    JukeBoxButton ButtonNumber;
    char PortValue;
    for (i = 0; i <= 3; i++)
    {
//output key pattern
        PortValue = JukeboxPort->IN;
        if ((PortValue & ButtonBits) == (JukeBoxPresses[i] & ButtonBits))
        {   //check button press
            debounce();
            if ((PortValue & ButtonBits) == (JukeBoxPresses[i] & ButtonBits))
            {   //still pressed
                ButtonNumber = i + 1;
                while ((PortValue & ButtonBits) == (Notes[i] & ButtonBits))
                    PortValue = JukeboxPort->IN; //wait for release
                break;
            }
            debounce();
        }
    }
    return ButtonNumber;
}

/*
 * Interrupt for notes and pitch
 */
void PORT6_IRQHandler(void)

{
    uint32_t status;
    if (Player == START){
        StopSong();
        Player = STOP;
    }
    FoundNote = FindNote(Notes);
    if (FoundNote != 0)
    {
        NewNotePressed = YES;
    }
    else
        NewNotePressed = NO;
    status = SwitchPort->IFG;
    SwitchPort->IFG &= ~status;

}

/*
 * Interrupt for jukebox buttons
 */
void PORT3_IRQHandler(void)

{
    uint32_t status;
    FoundButton = FindButton(JukeboxPresses);

    if (FoundButton != 0)
    {
        NewButtonPressed = YES;
        playJukebox(FoundButton);
    }
    else
        NewButtonPressed = NO;
    status = JukeboxPort->IFG;
    JukeboxPort->IFG &= ~status;

}

