/*
 * File:   main.c
 * Author: Ramazan Subasi (Subram)
 * web-site: ramazansubasi.com
 * Created on 30 Ocak 2015 Carsamba, 15:19
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CCPMX = RB0
#pragma config CP = OFF
#pragma config FCMEN = OFF
#pragma config IESO = OFF

#define _XTAL_FREQ 4000000

unsigned int duty=0;
bit pwmLogic;

void initilazion(void);
void pwmSet();


void main(void)
{
    initilazion();
    while(1){
     if(pwmLogic == 1)
        {
            duty--;
            if(duty == 0)
                pwmLogic = 0;
        }
        else
        {
            duty++;
            if(duty == 1023)
                pwmLogic = 1;

        }
        pwmSet(duty);
        __delay_ms(1);
    }
}

void pwmSet (){
    CCP1Y = duty & 1;
    CCP1X = (duty & 2);
    CCPR1L= duty>>2;
}

void initilazion (void){
   //GPIO Settings
    TRISB=0x00;		// PORTB Cikis
    PORTB=0x00;		// PORTB Temizlendi

    //Duty Cycle Settings
    CCP1CON=0X0F;       // CCP PWM MOD
    CCPR1L=0xFF;        //i registere deger yukleniyor
    CCP1Y=1;
    CCP1X=1;

    //TMR2 Settings
    T2CON=0X03;         // Prescaler 1:16 oluyor
    TMR2ON=1;		// Timer 2 Aktif
    PR2=255;            // PWM 10bit
}






