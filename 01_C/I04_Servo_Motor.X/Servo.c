/*
 * File: Servo.c
 * Author: Armstrong Subero
 * PIC: 16F1717 w/Int OSC @ 16MHz, 5v
 * Program: Library file to configure PIC16F1717
 * Compiler: XC8 (v1.38, MPLAX X v3.40)
 * Program Version: 1.0
 *                
 * Program Description: This Library allows you to control a standard servo
 *                      
 * Created on January 14th, 2017, 10:41 PM
 */

#include "16F1717_Internal.h"


/*******************************************************************************
* Function: void servoRotate0()
*
* Returns: Nothing
*
* Description: Rotates servo to 0 degree position
*
*******************************************************************************/

void servoRotate0() 
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD0 = 1;
    __delay_us(700);
    RD0 = 0;
    __delay_us(19300);
  }
}

/*******************************************************************************
* Function: void servoRotate90()
*
* Returns: Nothing
*
* Description: Rotates servo to 90 degree position
*
*******************************************************************************/

void servoRotate90() //90 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD0 = 1;
    __delay_us(1700);
    RD0 = 0;
    __delay_us(18300);
  }
}

/*******************************************************************************
* Function: void servoRotate90()
*
* Returns: Nothing
*
* Description: Rotates servo to 180 degree position
*
*******************************************************************************/

void servoRotate180() //180 Degree
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    RD0 = 1;
    __delay_us(2600);
    RD0 = 0;
    __delay_us(17400);
  }
}



