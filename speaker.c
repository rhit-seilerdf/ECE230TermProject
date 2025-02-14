/*
 * speaker.c
 *
 *  Created on: Feb 14, 2025
 *      Author: mortonip
 */

#include "speaker.h"

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

void NoteDurationConfiguration()
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

    // Enable TA1 TA1CCR0 compare interrupt
    NVIC->ISER[0] |= (1) << TA1_0_IRQn;
}

void TA1_0_IRQHandler(void)
{
    static char nextnote = 0; //start with first note in a song
    static char insert_rest = 0;
    /* Check if interrupt triggered by CCR0 */
    //clear interrupt flag

    // serve CCR0 interrupt
    if (insert_rest == 1)
    {
        // set CCR[0] interrupt to generate a 100ms rest
        //turn off speaker;  SpeakerPort->DIR &= ~Speaker; to set P2.4 as input
        TIMER_A1->CCR[0] = DELAY100MS;
        SpeakerPort->DIR &= ~Speaker;
        insert_rest = 0;
    }
    else
    { //play next note
      //set next note duration interrupt
      //play the current note
      //get next note into  TIMER_A0_CCR[0] and  TIMER_A0_CCR[1]

           // TODO, define SONG array
        if (TwinkleTwinkleLittleStar[nextnote] == NULL){
            nextnote = 0;
        }
        switch(TwinkleBeats[nextnote]) {
        case 4:
            TIMER_A1->CCR[0] = FULL_NOTE;
            break;
        case 2:
            TIMER_A1->CCR[0] = HALF_NOTE;
            break;
        case 1:
            TIMER_A1->CCR[0] = QUARTER_NOTE;
            break;
        default:
            TIMER_A1->CCR[0] = QUARTER_NOTE;
        }
        SpeakerPort->DIR |= Speaker;
        PlayNote(TwinkleTwinkleLittleStar[nextnote]);
        nextnote++;
        insert_rest = 1;

//        if (ANewSongNotes[nextnote] != NULL)
//        {
//            nextnote = nextnote + 1;
//        }
//        else
//        {
//            nextnote = 0;
//        }
//        insert_rest = 1;      //insert 100ms rest after the note is played.
    }
    TIMER_A1->CCTL[0] &= ~ TIMER_A_CCTLN_CCIFG;
}      //end interrupt service
