/*
 * speaker.c
 *
 *  Created on: Feb 18, 2025
 *      Author: seilerdf
 */

#include "buttons.h"
enum Status {NO, YES};
char NewNotePressed=NO;
char FoundNote;

char NewButtonPressed=NO;
char FoundButton;


const char NoteBits = (Button1|Button2|Button3|PitchLOW|PitchMID| PitchHIGH);
const char Notes[24]={Note1,Note2,Note3,Note4,Note5, Note6, Note7,Note8,
                      Note9,Note10,Note11, Note12, Note13,Note14,Note15,Note16,
                      Note17,Note18,Note19,Note20,Note21,Note22,Note23,Note24};
const char ButtonBits =  (PPbutton|SKIPbutton|SONGUP|SONGDOWN);
const char JukeboxPresses[4]= {PPbuttonPressed, SkipPressed, SongUpPressed, SongDownPressed};
void ButtonInit()
{
        SwitchPort->DIR &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->REN |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->OUT |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->IES |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->IE |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        SwitchPort->IFG &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        NVIC->ISER[1] |= (1)<<(PORT6_IRQn-32);

        JukeboxPort->DIR &= ~(PPbutton | SKIPbutton | SONGUP | SONGDOWN);
        JukeboxPort->REN |= (PPbutton | SKIPbutton | SONGUP | SONGDOWN);
        JukeboxPort->OUT |= (PPbutton | SKIPbutton | SONGUP | SONGDOWN);
        JukeboxPort->IES |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        JukeboxPort->IE |= (Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        JukeboxPort->IFG &= ~(Button1 | Button2 | Button3 | PitchLOW | PitchMID | PitchHIGH);
        NVIC->ISER[1] |= (1)<<(PORT3_IRQn-32);
}


/*
 * Finds note pressed
 */

char FindNote(const char Notes[]){
#define DEBOUNCETIME 15000
char i;
char NoteNumber;
char PortValue;
uint16_t delayloop;
    for(delayloop=0; delayloop<DEBOUNCETIME; delayloop++); //debounce the key
    for(i=0;i<=23;i++) {
//output key pattern
        PortValue = SwitchPort->IN;
        if((PortValue & NoteBits) ==(Notes[i] & NoteBits))  {   //check key press
            for(delayloop=0; delayloop<DEBOUNCETIME; delayloop++); //debounce the key
            if((PortValue & NoteBits) ==(Notes[i] & NoteBits))  {   //still pressed
                NoteNumber = i+1;
                while((PortValue & NoteBits) ==(Notes[i] & NoteBits))
                    PortValue=SwitchPort->IN; //wait for release
                break;
        }
        for(delayloop=0; delayloop<DEBOUNCETIME; delayloop++); //debounce the key
    }
}
    return NoteNumber;
}

char FindButton(const char JukeBoxPresses[]){
#define DEBOUNCETIME 15000
char i;
char ButtonNumber;
char PortValue;
uint16_t delayloop;
    for(delayloop=0; delayloop<DEBOUNCETIME; delayloop++); //debounce the key
    for(i=0;i<=3;i++) {
//output key pattern
        PortValue = JukeboxPort->IN;
        if((PortValue & ButtonBits) ==(JukeBoxPresses[i] & ButtonBits))  {   //check key press
            for(delayloop=0; delayloop<DEBOUNCETIME; delayloop++); //debounce the key
            if((PortValue & ButtonBits) ==(JukeBoxPresses[i] & ButtonBits))  {   //still pressed
                ButtonNumber = i+1;
                while((PortValue & ButtonBits) ==(JukeBoxPresses[i] & ButtonBits))
                    PortValue=JukeboxPort->IN; //wait for release
                break;
        }
        for(delayloop=0; delayloop<DEBOUNCETIME; delayloop++); //debounce the key
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
    FoundNote = FindNote(Notes);

    if(FoundNote!=0) {
            NewNotePressed=YES;
        }
        else NewNotePressed=NO;
        status = SwitchPort->IFG;
        SwitchPort->IFG &=~status;

}



/*
 * Interrupt for jukebox buttons
 */
void PORT3_IRQHandler(void)



{
    uint32_t status;
       FoundButton = FindButton(JukeboxPresses);

       if(FoundNote!=0) {
               NewButtonPressed=YES;
           }
           else NewButtonPressed=NO;
           status = JukeboxPort->IFG;
           JukeboxPort->IFG &=~status;

}


