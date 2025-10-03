#include "main.h"
extern unsigned char reset_flag,operational_mode; 
// extern is used to bring the keyword from 1 file to other

char *washing_program[] = {"Daily","Heavy","Delicates","Whites","Stain wash","Ecocottons","Woolens","Bed sheets","Rinse+Dry","Dry only","Wash only","Aqua store"};
char *water_level[]={"Auto","Low","Medium","High","Max"};
unsigned char program_no = 0;
unsigned char level_no = 0;
unsigned char min,sec;
unsigned int total_time , wash_time , rinse_time , spin_time ,time ;

///////////////////////////////////////////////////////////////////////////////
void power_on_screen(void)
{
    for(unsigned char i=0;i<16;i++)
    {
     clcd_putch(BLOCK,LINE1(i));
     __delay_ms(100);
    }    
     clcd_print("Powering On",LINE2(3));
     clcd_print("Washing Machine",LINE3(1));
     
    for(unsigned char i=0;i<16;i++)
    {
     clcd_putch(BLOCK,LINE4(i));
     __delay_ms(100);
    }  
    
     __delay_ms(2000);
}
//////////////////////////////////////////////////////////////////////////////
void clear_screen(void)
{
     clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}
///////////////////////////////////////////////////////////////////////////////
void washing_program_display(unsigned char key)
{
    if(reset_flag == reset_wash_program_screen)
    {
        clear_screen();
        reset_flag = reset_nothing;
    }
    
    if(key == SW5)
    {
        clear_screen();
        program_no++;
        if(program_no == 12)
        {
            program_no = 0;
        } 
    }
    if(program_no <= 9 )
    {
    clcd_print("Washing Program",LINE1(0)); 
    clcd_putch('*',LINE2(0));
    clcd_print(washing_program[program_no],LINE2(1));
    clcd_print(washing_program[program_no+1],LINE3(1));
    clcd_print(washing_program[program_no+2],LINE4(1));
    }
    else if(program_no == 10)
    {
    clcd_print("Washing Program",LINE1(0)); 
    clcd_putch('*',LINE2(0));
    clcd_print(washing_program[program_no],LINE2(1));
    clcd_print(washing_program[program_no+1],LINE3(1));
    clcd_print(washing_program[0],LINE4(1));
    }
    else if(program_no == 11)
    {
    clcd_print("Washing Program",LINE1(0)); 
    clcd_putch('*',LINE2(0));
    clcd_print(washing_program[program_no],LINE2(1));
    clcd_print(washing_program[0],LINE3(1));
    clcd_print(washing_program[1],LINE4(1));
    }   
}
///////////////////////////////////////////////////////////////////////////////
void water_level_display(unsigned char key)
{
    if(reset_flag == reset_water_level_screen)
    {
        clear_screen();
        reset_flag = reset_nothing;
    }
    if(key == SW5)
    {
        clear_screen();
        level_no++;
        if(level_no == 5)
        {
            level_no = 0;
        }
    }
    if(level_no <= 2)
    {
    clcd_print("Water Level",LINE1(0));
    clcd_putch('*',LINE2(0));
    clcd_print(water_level[level_no],LINE2(1));
    clcd_print(water_level[level_no+1],LINE3(1));
    clcd_print(water_level[level_no+2],LINE4(1));
    }
    else if(level_no == 3)
    {
    clcd_print("Water Level",LINE1(0));
    clcd_putch('*',LINE2(0));
    clcd_print(water_level[level_no],LINE2(1));
    clcd_print(water_level[level_no+1],LINE3(1));
    clcd_print(water_level[0],LINE4(1));
    }
    else if(level_no == 4)
    {
    clcd_print("Water Level",LINE1(0));
    clcd_putch('*',LINE2(0));
    clcd_print(water_level[level_no],LINE2(1));
    clcd_print(water_level[0],LINE3(1));
    clcd_print(water_level[1],LINE4(1));
    }
}
///////////////////////////////////////////////////////////////////////////////
void start_stop_display(unsigned char key)
{
    if(  reset_flag == reset_start_stop_screen)
    {
        clear_screen();
        reset_flag = reset_nothing;
    }
    
    clcd_print("Press Switch : ",LINE1(0));
    clcd_print("SW5: Start",LINE2(1));
    clcd_print("SW6: Stop",LINE3(1));
    
}
///////////////////////////////////////////////////////////////////////////////
void start_display(unsigned char key)
{
    door_status();
    if(  reset_flag == reset_start_screen)
    {
   clear_screen();
   clcd_print("Prog :",LINE1(0)); 
   clcd_print(washing_program[program_no],LINE1(6));
   clcd_print("Time :",LINE2(0)); 
   clcd_putch(min/10 + '0' ,LINE2(6));    //converting INT to ASCII value (no.+ 48 or '0') //
   clcd_putch(min%10 + '0' ,LINE2(7));
   clcd_putch(':',LINE2(8));
   clcd_putch(sec/10 + '0' ,LINE2(9));
   clcd_putch(sec%10 + '0' ,LINE2(10));
   reset_flag = reset_nothing;
   
   __delay_ms(2000); // wait for 2 sec
   
   clear_screen();
   clcd_print("Function:",LINE1(0));
   clcd_print("Time:",LINE2(0));
   clcd_print("SW5 : Start",LINE3(0));
   clcd_print("SW6 : Pause",LINE4(0));
   
   total_time = time = min*60 + sec;
   wash_time =  total_time*0.46;
   rinse_time =  total_time*0.12;
   spin_time =  total_time*0.42;
   TMR2ON = 1;//timer on
   fan = 1;
    } 
    if(key == SW6)
    {
        TMR2ON = 0;
        fan = 0;
        operational_mode = pause;
    }
    
    total_time = min*60 + sec;
    if(program_no <= 7)
    {
        if(total_time >= (time - wash_time))
        {
            clcd_print("Wash",LINE1(10));
        }
        else if(total_time >= (time - wash_time - spin_time))
        {
            clcd_print("Rinse",LINE1(10));
        }
        else
        {
            clcd_print("Spin ",LINE1(10));
        }
    }
    else if(program_no == 8)
    {
        if(total_time >= time - (time*0.40))
        {
            clcd_print("Rinse",LINE1(10));
        }
        else
        {
            clcd_print("Spin ",LINE1(10));
        }
    }
    else if(program_no == 9)
    {
        clcd_print("Spin ",LINE1(10));
    }
    else
    {
        clcd_print("Wash",LINE1(10)); 
    }
   clcd_putch(min/10 + '0' ,LINE2(6));    //converting INT to ASCII value (no.+ 48 or '0') //
   clcd_putch(min%10 + '0' ,LINE2(7));
   clcd_putch(':',LINE2(8));
   clcd_putch(sec/10 + '0' ,LINE2(9));
   clcd_putch(sec%10 + '0' ,LINE2(10));

   if(min == 0 && sec == 0)
   {
       clear_screen();
       fan = 0;
       buzzer = 1;
       clcd_print("Prog. completed",LINE1(0));
       clcd_print("Remove clothes",LINE2(0));
       __delay_ms(2000);
       buzzer = 0;
       operational_mode = washing_program_screen;
       reset_flag = reset_wash_program_screen;
       clear_screen();
       
   }
}
///////////////////////////////////////////////////////////////////////////////
void set_time(void)
{
    switch(program_no)
    {
        case 0://daily
            switch(level_no)
            {
                case 1:
                    sec = 33;
                    break;
                case 0:
                case 2:
                    sec = 41;
                    break;
                case 3:
                case 4:
                    sec = 45; 
                    break;
            }
            break;
        case 1://heavy
             switch(level_no)
            {
                case 1:
                    sec = 43;
                    break;
                case 0:
                case 2:
                    sec = 50;
                    break;
                case 3:
                case 4:
                    sec = 57; 
                    break;
            }
            break;
        case 2://delicates
             switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                    sec = 26;
                    break;
                case 3:
                case 4:
                    sec = 31; 
                    break;
            }
            break;
        case 3://whites
             switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 1;
                    sec = 16;
                    break;
            }
            break;
        case 4://stainwash
           switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 1;
                    sec = 36;
                    break;
            }
            break;
        case 5://ecocotton
             switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                    min = 0;
                    sec = 31;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 36;
                    break;
            }
            break;
        case 6://woollen
             switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 29;
                    break;
            }
            break;
        case 7://bedsheet
             switch(level_no)
            {
                case 1:
                    sec = 46;
                    break;
                case 0:
                case 2:
                    sec = 53;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 60;
                    break;
            }
            break;
        case 8://rinse+dry
             switch(level_no)
            {
                case 1:
                    sec = 18;
                    break;
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 20;
                    break;
            }
            break;
        case 9://dry only
             switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 6;
                    break;
            }
            break;
        case 10://wash only
             switch(level_no)
            {
                case 1:
                    sec = 16;
                    break;
                case 0:
                case 2:
                    sec = 21;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 26;
                    break;
            }
            break;
        case 11://aqua store
            switch(level_no)
            {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 50;
                    break;
            }
            break;    
    }   
}
///////////////////////////////////////////////////////////////////////////////
void door_status()
{
    if(RB0 == 0)
    {
       fan = 0;
       TMR2ON = 0;
       buzzer = 1;
       clear_screen();
       clcd_print("Door is open",LINE1(0));
       clcd_print("Close the door",LINE2(0));
       while(RB0 == 0)
       {
           ;//wait until door closed
       }
       fan = 1;
       TMR2ON = 1;
       buzzer = 0;
       clear_screen();
   clcd_print("Function:",LINE1(0));
   clcd_print("Time:",LINE2(0));
   clcd_print("SW5 : Start",LINE3(0));
   clcd_print("SW6 : Pause",LINE4(0));
    }
}