/*
 * speaker.c
 *
 *  Created on: Feb 14, 2025
 *      Author: mortonip
 */

#include "speaker.h"
#include <stdlib.h>
#define NUMBEROFSONGS 2

int songID = 0;
static char nextnote=0;

static char insert_rest=1;

const uint16_t TwinkleTwinkleLittleStar[] = {NOTEG3, NOTEG3, NOTED4, NOTED4, NOTEE4, NOTEE4, NOTED4, RestNote,
                               NOTEC4, NOTEC4, NOTEB3, NOTEB3, NOTEA3, NOTEA3, NOTEG3, RestNote,
                               NOTED4, NOTED4, NOTEC4, NOTEC4, NOTEB3, NOTEB3, NOTEA3, RestNote,
                               NOTED4, NOTED4, NOTEC4, NOTEC4, NOTEB3, NOTEB3, NOTEA3, RestNote,
                               NOTEG3, NOTEG3, NOTED4, NOTED4, NOTEE4, NOTEE4, NOTED4, RestNote,
                               NOTEC4, NOTEC4, NOTEB3, NOTEB3, NOTEA3, NOTEA3, NOTEG3, RestNote,
                               RestNote, RestNote, RestNote, RestNote,
                               NULL};
const uint16_t TwinkleBeats[] = { 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1,
                                  1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2,
                                  1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1};

const uint16_t CurrentMusicNotes[] = {
                                      NOTEF4, NOTEA4, NOTEB4,
                                      NOTEF4, NOTEA4, NOTEB4,
                                      NOTEF4, NOTEA4, NOTEB4,NOTEE5,
                                      NOTED5,NOTEB4,NOTEC5,NOTEB4,NOTEG4,NOTEE4,
                                      NOTED4,NOTEE4,NOTEG4,NOTEE4,NULL};
const uint16_t CurrentMusicBeats[] = {4,4,2,
                                      4,4,2,
                                      4,4,4,4,
                                      2,4,4,4,4,1,
                                      2,4,4,1,NULL};

const uint16_t* Song[NUMBEROFSONGS] = {TwinkleTwinkleLittleStar, CurrentMusicNotes};
const uint16_t* SongBeats[NUMBEROFSONGS] = {TwinkleBeats, CurrentMusicBeats};
char *SongNames[] = {"Twinkle Twinkle", "Lost Woods Theme"};


void speaker_init(void)
{

    SpeakerPort->DIR |= Speaker;            // set P2.4 as output
    SpeakerPort->SEL0 |= Speaker;           // P2.4 set to TA0.1
    SpeakerPort->SEL1 &= ~Speaker;  // Option 0b01
//set Timer A0 CCR0 compare for period and CCR1 compare for duty cycle of a note
    TIMER_A0->CCTL[1] = 0x0060; //0b0000000001100000 set/reset
    TIMER_A0->CTL = 0x0294; // 0b0000001010010000 up mode, prescale 2, SMCLK
}

void PlayNote(unsigned int CurrentNote)
{
    TIMER_A0->CCR[0] = CurrentNote - 1;
    // Set high pulse-width in CCR1 register (determines duty cycle)
    TIMER_A0->CCR[1] = (CurrentNote / 2) - 1;
}

void StartSong()
{
    /* Configure Timer_A1 and CCRs */
    // Set initial period in CCR0 register. This assumes timer starts at 0
    //    TIMER_A1->CCR[0] = QUARTER_NOTE;
    TIMER_A1->CCR[0] = HALF_NOTE;
    // Configure CCR0 for Compare mode with interrupt enabled (no output mode - 0)
    TIMER_A1->CCTL[0] = 0x0010;
    // Configure Timer_A1 in UP Mode with source ACLK prescale 1:1 and no interrupt
    // configure Timer_A1: ACLK, UP mode, TACLR=1 bit 2, no interrupt
    TIMER_A1->CTL = 0b0000000100010100;  //0x0114
    lcd_puts(SongNames[songID]);
    // Enable TA1 TA1CCR0 compare interrupt
    NVIC->ISER[0] |= (1) << TA1_0_IRQn;
}

void StopSong(void)
{
    TIMER_A1->CCTL[0] = 0x0000;
    PlayNote(RestNote);
    nextnote = 0;
    insert_rest = 1;
}

void SongUp(void)
{
    songID = (songID + 1) % NUMBEROFSONGS;
    lcd_clear();
    lcd_puts(SongNames[songID]);
    nextnote = 0;
    insert_rest = 1;
}

void SongDown(void)
{
    songID = abs((songID - 1) % NUMBEROFSONGS);
    lcd_clear();
    lcd_puts(SongNames[songID]);
    nextnote = 0;
    insert_rest = 1;
}

void TA1_0_IRQHandler(void)
{


    if(TIMER_A1->CCTL[0] & TIMER_A_CCTLN_CCIFG)

         {
            TIMER_A1->R = 0;    //Clear Timer A1  count
             if(insert_rest==1) {
                 insert_rest=0;
                 TIMER_A1->CCR[0] = DELAY100MS;
                 SpeakerPort->DIR &= ~Speaker;            // set P2.4 as input
             }
             else {
                 insert_rest=1;
                 SpeakerPort->DIR |= Speaker;            // set P2.4 as output
                 if(Song[songID][nextnote]!=NULL)
                     nextnote=nextnote+1;
                 else
                     StopSong();
                 PlayNote(Song[songID][nextnote]);
                 switch ((int)SongBeats[songID][nextnote]) {
                     case 1:   TIMER_A1->CCR[0] = WHOLE_NOTE; break;          //Set full note
                     case 3:   TIMER_A1->CCR[0] = DOTTED_HALF; break;
                     case 2:   TIMER_A1->CCR[0] = HALF_NOTE;  break;    //Set half note
                     case 4:   TIMER_A1->CCR[0] = QUARTER_NOTE; break;
                     case 9:   TIMER_A1->CCR[0] = DOTTED_QUARTER; break;
                     case 8:   TIMER_A1->CCR[0] = EIGHTH_NOTE;   break;//Set eighth note
                     case 16:  TIMER_A1->CCR[0] = SIXTEENTH_NOTE; break;       //Set Sixteenth note
                     default:  TIMER_A1->CCR[0] = QUARTER_NOTE;   break;       //Set quarter note

         }

     }
             TIMER_A1->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;  //clear interrupt flag
    }

}      //end interrupt service



