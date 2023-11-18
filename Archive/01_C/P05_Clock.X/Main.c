/*
 * File: Main.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: P05_Clock
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 *                
 * Program Description: This Program creates a clock using the PIC17F1717
 *                      microcontroller and the DS1302. The display is
 *                      the intelligent Nextion 2.4 LCD. There are two screens
 *                      the main screen displays. The main screen displays the
 *                      time and date. The second screen allows the user to set
 *                      the current time and date.
 * 
 * Hardware Description: The DS1302 is connected to the microcontroller as 
 *                       follows:
 * 
 *                      CE   ->  RD0
 *                      SCLK ->  RD1
 *                      IO   ->  RD2 
 *                      
 *                      
 * Created April 21st, 2017, 7:11 PM
 */


/*******************************************************************************
 *Includes and defines
 ******************************************************************************/

#include "16F1717_Internal.h"
#include "I2C.h"
#include "oled.h"
#include "ds1302.h"
#include "EUSART.h"
#include "setup.h"
#include "touchscreen.h"
#include "bool_support.h"
#include <string.h>


// Variables for date and time
unsigned char yr1, mn1, date1, dy1, hr1, min1, sec1;
unsigned char yr2, mn2, date2, dy2, hr2, hr3,  min2, sec2;

// Arrays for int to ascii conversion
char min_arr[8];
char hr_arr[8];
char dt_arr[5];
char minute_arr[10];
char hour_arr[10];
char date_arr[10];
char mth_arr[10];
char month_arr[10];

// Arrays to hold date, month and time string   
char time_string[10];
char date_string[10];   
char hour_string[10];
char min_string[10];
char date1_string[10];
char month_string[10];
char mth_string[10];

// String constants for commands
const char screen_time[] = "time.txt=";
const char screen_date[] = "date.txt=";
const char screen_mth[]  = "month.txt=";
const char screen_hour[] = "t0.txt=";
const char screen_mins[] = "t1.txt=";
const char screen_date1[] = "t2.txt=";
const char screen_month[] = "t3.txt=";

// Array containing months
const char* months[] = {"MMM", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                         "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

// buffer for UART
char buf[50];

// Variables to store values for min, hour, month and date
unsigned char  x = 1;
unsigned char  y = 0;
unsigned char  m = 1;
unsigned char  d = 1;

// energy efficient function
void green(char* buf);


/*******************************************************************************
 * Function: Main
 *
 * Returns: Nothing
 *
 * Description: Program entry point
 ******************************************************************************/

void main(void) {
    initMain();
    
    char* hour1;
    char* min1;
    char* date3;
    char* month1;
    char* set1;
    
    while(1){
        
        // Read EUSART
        EUSART_Read_Text(buf, 11);
       
        // Check for if energy save enabled
        green(buf); 
        
        //////////////////////////
        // Check buffer for each 
        // string from display
        /////////////////////////
        hour1  = strstr(buf, "hour");
        min1   = strstr(buf, "mins");
        date3  = strstr(buf, "date");
        month1 = strstr(buf, "month");
        set1   = strstr(buf,  "set");
      
        
        /////////////////////
        // If minute found
        ////////////////////
        if (min1)
        {
           // Convert date and time to strings
           itoa( minute_arr, y, 10 );
             
           strcpy(min_string, "\"");
           
             
           // If less than 10 pad with a 0
          if (y < 10){
              strcat(min_string, "0");
              strcat(min_string, minute_arr);
          }
          // Else show min as is
          else
          {
              strcat(min_string, minute_arr);
          }
           
          strcat(min_string, "\"");
           
           if (y < 59){
               y++;
           }
           
           else {
               y = 0;
           }
           

           // Write time
           touchscreen_data(screen_mins, min_string); 
        }

        /////////////////////
        // If hour found
        ////////////////////
        if (hour1){
     
           // Convert date and time to strings
           itoa( hour_arr, x, 10 );
             
           strcpy(hour_string, "\"");
           strcat(hour_string, hour_arr);
           strcat(hour_string, "\"");
           
           if (x < 12){
               x++;
           }
           
           else {
               x = 1;
           }
           
           // Write time
           touchscreen_data(screen_hour, hour_string);   
       }
        
        ////////////////////
        // If date found
        ///////////////////
        if(date3)
        {
            // Convert date and time to strings
           itoa( date_arr, d, 10 );
             
           strcpy(date1_string, "\"");
           strcat(date1_string, date_arr);
           strcat(date1_string, "\"");
           
           if (d < 31){
               d++;
           }
           
           else {
               d = 0;
           }
           
           // Write time
           touchscreen_data(screen_date1, date1_string);  
        }
        
        
        ///////////////////
        // If month found
        ///////////////////
        
        if(month1)
        {
            // Convert date and time to strings
           itoa( month_arr, m, 10 );
             
           strcpy(month_string, "\"");
           strcat(month_string, month_arr);
           strcat(month_string, "\"");
           
           if (m < 12){
               m++;
           }
           
           else {
               m = 1;
           }
           
           // Write time
           touchscreen_data(screen_month, month_string);  
        }
        
        ///////////////////////
        // If user pressed set
        //////////////////////
        
        if (set1){
            
            // Initial time and date
            byte sec = 00;
            byte min = y-1;
            byte hr = x-1;
            byte day = 2;
            byte date = d-1;
            byte month = m-1;
            byte year = 17;
            
            // Re-Initialize DS1302 with new values
            DS1302_Initialize(sec, min, hr, day, date, month, year);
            touchscreen_command("page 0");
        }
      
    }
    
    return; 
}
 
/*******************************************************************************
 * Function: void green (char* buf)
 *
 * Returns: Nothing
 *
 * Description: Enables or disables green feature of display
 ******************************************************************************/

void green(char* buf)
{
   char* green1;
    
   green1 = strstr(buf, "ener");
   
   if (green1 == NULL)
   {
       return;
   }
   
   else
   {
      
    if (!on){
        touchscreen_command("t0.txt=\"ON\"");
        __delay_ms(100);
        touchscreen_command("dim=30");
        __delay_ms(100);
        
        on = true;
    }
    
    else {
          touchscreen_command("t0.txt=\"OFF\"");
          __delay_ms(100);
          touchscreen_command("dim=100");
          __delay_ms(100);
       
          on = false; 
       }
   }
}

/*******************************************************************************
 * Function: void interrupt isr(void)
 *
 * Returns: Nothing
 *
 * Description: Timer0 interrupt at a rate of approx. 5 seconds that updates
 *              the time on the display
 ******************************************************************************/

void interrupt isr(void)
{                               
    // Start count at 0
    static int count = 0;
           
    // Reset flag after overflow
    INTCONbits.TMR0IF = 0;
    
    // Zero timer
    TMR0 = 0;
        
    // Increment count
    count++;
    
     // Value = fclk / (4 * 256 * 256 * fout)
     //                                   |-- Frequency out (in Hz)
     //                      |-- Prescaler value
     // Value =  16 000 000 / (262 144)
     // Value =  61.04 for 1 s
     // Therefore 305 for approx 5 secs
    if (count == 305){
        
         ////////////////////////////
         // Read DS1302 clock burst
         ////////////////////////////
        
          DS1302_Reset();
          DS1302_WriteByte(0xBF);
          
          sec1 = DS1302_ReadByte();
          min1 = DS1302_ReadByte();
          hr1 = DS1302_ReadByte();
          date1 = DS1302_ReadByte();
          mn1 = DS1302_ReadByte();
          dy1 = DS1302_ReadByte();
          yr1 = DS1302_ReadByte();
          
          DS1302_Reset();
        
          /////////////////////////
          // Convert all BCD data 
          // to Decimal time format
          //////////////////////////
          
          // Year 
          yr2 = get_dec(yr1);
       
          // Month
          mn2 = get_dec(mn1);
  
          // Date
          date2 = get_dec(date1);
         
          // Hour
          hr2 = get_dec(hr1);
          
          // Minute
          min2 = get_dec(min1);
          
          // Seconds
          sec2 = get_dec(sec1);
          
          ///////////////////////////
          // Convert 24 hr to 12 hr 
          // format
          ///////////////////////////
          
          if (hr2 <= 12 && hr2 > 0){
              hr3 = hr2;
          }
          
          else if (hr2 >= 13 && hr2 < 24)
          {
              hr3 = (hr2-12);
          }
          
          else {
              hr3 = 12;
          }
          
          ////////////////////////////
          // Convert date and time 
          // to strings
          ///////////////////////////
          
          itoa( min_arr, min2, 10 );
          itoa( hr_arr, hr3,  10 );
          itoa( dt_arr, date2, 10);
          
          //////////////////////////
          /// Create date string
          //////////////////////////
          
          strcpy(date_string, "\"");
          strcat(date_string, dt_arr);
          strcat(date_string, "\"");
          
          ///////////////////////////
          // Create month string
          //////////////////////////
          strcpy(mth_string, "\"");
          strcat(mth_string, months[mn2]);
          strcat(mth_string, "\"");
          
          //////////////////////////
          // Create time string
          //////////////////////////
          
          strcpy(time_string, "\"");
          strcat(time_string, hr_arr);
          strcat(time_string, ":");
          
          // If less than 10 pad with a 0
          if (min2 < 10){
              strcat(time_string, "0");
              strcat(time_string, min_arr);
          }
          // Else show min as is
          else
          {
              strcat(time_string, min_arr);
          }
          
          strcat(time_string, "\"");
          
          // Write time
          touchscreen_data(screen_time, time_string);
          
          // Write month
          touchscreen_data(screen_mth, mth_string);
         
          // Write date
          touchscreen_data(screen_date, date_string);
          
          // Reset count
          count = 0;
    }
    
    
    else {
        // No need to do anything
    }
   
}

