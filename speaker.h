/*
 * speaker.h
 *
 *  Created on: Feb 14, 2025
 *      Author: mortonip
 */

#ifndef SPEAKER_H_
#define SPEAKER_H_

#include <msp.h>

/* Standard Includes */
#include <stdio.h>  //NULL
#include "csHFXT.h"
#include "csLFXT.h"

#define SpeakerPort P2
#define Speaker BIT4  //P2.4

//48MHz system clock and 4:1 prescaler
//12MHz Timer A clock
//Half period count = (48,000,000/Note frequency)
#define SMCLK 48000000 //Hz
#define TimerA0Prescaler 4 //Timer A prescaler
#define TimerA0Clock  SMCLK/TimerA0Prescaler

#define RestNote 1
#define FrequencyA4 440 //Hz
#define FrequencyB4 493.88 //Hz
#define FrequencyC5 523.26 //Hz
#define FrequencyG3 196.00
#define FrequencyD4 293.66
#define FrequencyE4 329.63
#define FrequencyC4 261.63
#define FrequencyB3 246.94
#define FrequencyA3 220.00
#define FrequencyA4 440 //Hz
#define FrequencyB4 493.88 //Hz
#define FrequencyC5 523.26 //Hz

#define FrequencyF4 349.23 //Hz
#define FrequencyA4 440 //Hz
#define FrequencyE5 659.25
#define FrequencyD5 587.33
#define FrequencyD4 293.66
#define FrequencyE4 329.63
#define FrequencyG4 392



// Note A4 - 440 Hz, B4 - 493.88 Hz, C5 - 523.26 Hz
#define NOTEA4  TimerA0Clock/FrequencyA4    // (48,000,000/440)=4545.45
#define NOTEB4  TimerA0Clock/FrequencyB4   //4049.57
#define NOTEC5  TimerA0Clock/FrequencyC5   //3822.19

#define NOTEF4  TimerA0Clock/FrequencyF4
#define NOTEE5  TimerA0Clock/FrequencyE5
#define NOTED5  TimerA0Clock/FrequencyD5
#define NOTEG4  TimerA0Clock/FrequencyG4
#define NOTEE4  TimerA0Clock/FrequencyE4
#define NOTED4  TimerA0Clock/FrequencyD4

// Note A4 - 440 Hz, B4 - 493.88 Hz, C5 - 523.26 Hz
#define NOTEA4  TimerA0Clock/FrequencyA4    // (48,000,000/440)=4545.45
#define NOTEB4  TimerA0Clock/FrequencyB4   //4049.57
#define NOTEC5  TimerA0Clock/FrequencyC5   //3822.19
#define NOTEG3  TimerA0Clock/FrequencyG3
#define NOTED4  TimerA0Clock/FrequencyD4
#define NOTEE4  TimerA0Clock/FrequencyE4
#define NOTEC4  TimerA0Clock/FrequencyC4
#define NOTEB3  TimerA0Clock/FrequencyB3
#define NOTEA3  TimerA0Clock/FrequencyA3

#define ACLK 32768 //Hz
#define WHOLE_NOTE       ACLK    //1 second
#define HALF_NOTE   ACLK/2  //0.5 second
#define QUARTER_NOTE    ACLK/4  //0.25 second
#define DOTTED_HALF  QUARTER_NOTE *3
#define EIGHTH_NOTE ACLK/8
#define DOTTED_QUARTER  EIGHTH_NOTE *3
#define SIXTEENTH_NOTE ACLK/16
#define DELAY100MS  ACLK/10    //100ms timer delay

extern uint16_t songID;
extern const uint16_t numberOfSongs;
extern char *SongNames[];


extern void speaker_init(void);

extern void PlayNote(unsigned int CurrentNote);

extern void NoteDurationConfiguration();

#endif /* SPEAKER_H_ */
