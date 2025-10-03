/*
 * File:   MAIN.c
 * Author: Acer
 *
 * Created on 11 June, 2025, 8:11 PM
 */


#include "main.h"
#pragma config WDTE = OFF

unsigned char operational_mode = washing_program_screen  ;
unsigned char reset_flag = reset_wash_program_screen;

static void init_config()
{
    init_clcd();
    init_digital_keypad();
    init_timer2();
    
    GIE = 1;
    PEIE = 1;
    
   fan_ddr = 0;
   buzzer_ddr = 0;
   fan = 0;
   buzzer = 0; 

}

void main(void) {
    init_config();
    
    clcd_print("Press Key5 To",LINE1(1));
    clcd_print("Power ON",LINE2(3));
    clcd_print("Washing Machine",LINE3(1));
    
    while(read_digital_keypad(STATE) != SW5 );// wait until sw5 is pressed
   
    clear_screen(); 
    power_on_screen();
   
    while(1)
    {
        unsigned char key = read_digital_keypad(STATE);
        for(unsigned int i=300;i--;);
        
        if((key == LPSW4) && (operational_mode == washing_program_screen))
        {
            operational_mode = water_level_screen;
            reset_flag = reset_water_level_screen;
        }
        else if((key == LPSW4) && (operational_mode == water_level_screen))
        {
            operational_mode = start_stop_screen;
            reset_flag = reset_start_stop_screen;
        }
        else if((key == SW5) && (operational_mode == start_stop_screen))
        {
            operational_mode = start_screen;
            set_time();
            reset_flag = reset_start_screen;
        }
        else if((key == SW6) && (operational_mode == start_stop_screen)) 
        {
            operational_mode = washing_program_screen;
            reset_flag = reset_wash_program_screen;
        }
        else if((key == SW5) && (operational_mode == pause))
        {
            fan = 1;
            TMR2ON = 1;
            operational_mode = start_screen;
        }
        
        
        switch(operational_mode)
        {
            case washing_program_screen:
                washing_program_display(key);
                break;
            
            case water_level_screen:
                water_level_display(key);
                break;
           
            case start_stop_screen:
                start_stop_display(key);
                break;
                
            case start_screen:
                start_display(key);
                break;
        }
        
    }
    
    return;
}


