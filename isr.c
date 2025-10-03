#include <xc.h>
extern unsigned char min,sec;

void __interrupt() isr(void)
{
    static unsigned int count = 0;
    
    if(TMR2IF == 1)
    {
        if(++count == 20000)
        {
            if(sec != 0)
            {
                sec--;
            }
            else if(sec == 0 && min != 0)
            {
                min--;
                sec = 60;
            }
            count = 0;
        }
        TMR2IF = 0;
    }
}

