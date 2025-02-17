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
#define FULL_NOTE       ACLK    //1 second
#define HALF_NOTE   ACLK/2  //0.5 second
#define QUARTER_NOTE    ACLK/4  //0.25 second
#define DELAY100MS  ACLK/10    //100ms timer delay


extern void speaker_init(void);

extern void PlayNote(unsigned int CurrentNote);

extern void NoteDurationConfiguration();

#endif /* SPEAKER_H_ */
