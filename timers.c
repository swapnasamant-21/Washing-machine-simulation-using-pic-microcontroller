#include <xc.h>
#include "timers.h"

void init_timer2(void)
{
   
//    T2CKPS0 = 1;
//    T2CKPS1 = 1;
    
    PR2 = 250;
    
    TMR2IE = 1;//time interrupt enabled
    
    TMR2ON = 0;//initially timer off....since requied only in run program
    
    
}
