#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}

unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    static unsigned char long_press = 1;
    static unsigned char pre_key;
    
    if (mode == LEVEL_DETECTION)
    {
        return KEYPAD_PORT & INPUT_LINES;
    }
    else if(mode == STATE_DETECTION)
    {
        if (((KEYPAD_PORT & INPUT_LINES) != ALL_RELEASED) && once)
        {
            once = 0;
            long_press = 0; 
            pre_key = KEYPAD_PORT & INPUT_LINES;
        }
        else if (((KEYPAD_PORT & INPUT_LINES) == ALL_RELEASED) && (!once))
        {
            once = 1;
            if (long_press < 5)
            {
                return pre_key;
            }
        }
        else if ((!once) && (long_press <= 5))
        {
            long_press++ ;
        }
        else if(!once && (long_press == 6) && ((KEYPAD_PORT & INPUT_LINES) == SW4))
        {
            long_press ++;
            return LPSW4;
        }
//        else if(!once && (long_press == 6) && ((KEYPAD_PORT & INPUT_LINES) == SW5))
//        {
//            long_press ++;
//            return LPSW5;
//        }
//        else if(!once && (long_press == 6) && ((KEYPAD_PORT & INPUT_LINES) == SW6))
//        {
//            long_press ++;
//            return LPSW6;
//        }
    }
    
    return ALL_RELEASED;
}
