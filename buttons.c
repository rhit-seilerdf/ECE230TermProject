/*
 * speaker.c
 *
 *  Created on: Feb 18, 2025
 *      Author: seilerdf
 */

#include "buttons.h"


void ButtonInit()
{
        SwitchPort->DIR &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->REN |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->OUT |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->IES |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->IE |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->IFG &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        NVIC->ISER[1] |= (1)<<(PORT1_IRQn-32);

        JukeboxPort->DIR &= ~(PPbutton | SKIPbutton | SONGUP | SONGDOWN);
        JukeboxPort->REN |= (PPbutton | SKIPbutton | SONGUP | SONGDOWN);
        JukeboxPort->OUT |= (PPbutton | SKIPbutton | SONGUP | SONGDOWN);
        JukeboxPort->IES |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        JukeboxPort->IE |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        JukeboxPort->IFG &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        NVIC->ISER[1] |= (1)<<(PORT3_IRQn-32);
}




/*
 * Interrupt for notes and pitch
 */
void PORT1_IRQHandler(void)

{




}



/*
 * Interrupt for jukebox buttons
 */
void PORT3_IRQHandler(void)

{


}


