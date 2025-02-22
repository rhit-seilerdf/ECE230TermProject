/*
 * buttons.h
 *
 *  Created on: Feb 18, 2025
 *      Author: seilerdf
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include <msp.h>
#include "speaker.h"

#define SwitchPort P6
#define JukeboxPort P3

#define Button1 BIT0
#define Button2 BIT1
#define Button3 BIT4

#define PitchLOW BIT5
#define PitchMID BIT6
#define PitchHIGH BIT7

#define PPbutton BIT0
#define SKIPbutton BIT3
#define SONGUP BIT5
#define SONGDOWN BIT6

#define Note1 ~BIT5
#define Note2 ~BIT6
#define Note3 ~BIT7

#define Note4 ~(BIT4|BIT5)
#define Note5 ~(BIT4|BIT6)
#define Note6 ~(BIT4|BIT7)

#define Note7 ~(BIT1|BIT5)
#define Note8 ~(BIT1|BIT6)
#define Note9 ~(BIT1|BIT7)

#define Note10 ~(BIT1|BIT4|BIT5)
#define Note11 ~(BIT1|BIT4|BIT6)
#define Note12 ~(BIT1|BIT4|BIT7)

#define Note13 ~(BIT0|BIT5)
#define Note14 ~(BIT0|BIT6)
#define Note15 ~(BIT0|BIT7)

#define Note16 ~(BIT0|BIT4|BIT5)
#define Note17 ~(BIT0|BIT4|BIT6)
#define Note18 ~(BIT0|BIT4|BIT7)

#define Note19 ~(BIT0|BIT1|BIT5)
#define Note20 ~(BIT0|BIT1|BIT6)
#define Note21 ~(BIT0|BIT1|BIT7)

#define Note22 ~(BIT0|BIT1|BIT4|BIT5)
#define Note23 ~(BIT0|BIT1|BIT4|BIT6)
#define Note24 ~(BIT0|BIT1|BIT4|BIT7)

#define PPbuttonPressed ~(PPbutton)
#define SkipPressed ~(SKIPbutton)
#define SongUpPressed ~(SONGUP)
#define SongDownPressed ~(SONGDOWN)





extern void ButtonInit();
extern char FindNote(const char Notes[]);
extern char FindButton(const char JukeboxPresses[]);
extern void PlayNote(unsigned int CurrentNote);

#endif /* BUTTONS_H_ */
