/*
 * buttons.h
 *
 *  Created on: Feb 18, 2025
 *      Author: seilerbc
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include <msp.h>

#define SwitchPort P1
#define JukeboxPort P3

#define Button1 BIT0
#define Button2 BIT1
#define Button3 BIT2

#define PitchLOW BIT3
#define PitchMID BIT4
#define PitchHIGH BIT5

#define PPbutton BIT0
#define SKIPbutton BIT2
#define SONGUP BIT5
#define SONGDOWN BIT6

extern void ButtonInit();



#endif /* BUTTONS_H_ */
