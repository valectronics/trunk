/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
    ISR_init();
    
    TRISD = 0x00; /* Initialize PORTD pins as outputs */
    LATD = 0x00; /* Set LOW level on PORTD outputs */
    
    Timer0_init();
}

void Timer0_init()
{
    T0CONbits.T0PS = 0x04; /* Prescaler 1:32 */ 
    T0CONbits.PSA = 0x00; /* Prescaler is on */ 
    T0CONbits.T0CS = 0x00; /* Timer mode used! Internal Clock (Fosc/4) = 10 MHz */ 
    T0CONbits.T08BIT = 0x00; /* 0 = 16-bit mode / 1 = 8-bit */ 
    
    TMR0L = 0xED; /* set initial value of the timer for 100ms */
    TMR0H = 0x84; 
    
    T0CONbits.TMR0ON = 0x01; /* Start Timer0 */ 
}

void Timer1_init()
{
    T1CONbits.RD16 = 0x00; /* 16 bit operation ? */ 
    //T1CONbits.T1RUN = 0x00; /* System Clock? */ 
    T1CONbits.T1CKPS = 0x03; /* 1:8 Prescaler = > 10MHz / 8 = 1.25 MHz => T = 800ns */
    T1CONbits.TMR1CS = 0x00; /* Internal Clock (Fosc/4) = 10 MHz */ 

    T1CONbits.TMR1ON = 0x01; /* Start Timer1 */
}

void ISR_init()
{
    INTCONbits.GIE = 0x01; /* Global Interrupt Enable */ 
    INTCONbits.PEIE = 0x01; /* Enable all peripherals interrupts */
    INTCONbits.TMR0IE = 0x01; /* Interrupt Timer0 enabled */ 
    INTCONbits.RBIE = 0x01; /* RB Port Change Interrupt Enable bit */
    INTCONbits.INT0E = 0x01; /* INT0 External Interrupt Enable bit */
    
    PIE1bits.TMR1IE = 0x01; /* Interrupt Timer1 enabled */ 
    IPR1bits.TMR1IP = 0x01; /* High priority overflow interrupt ? */
}

void Button_debounce()
{
    if(INT0IF != 0)
    {
        Timer0_init();
        if((TMR0IF != 0) && (PORTBbits.RB0 == 0))
        {
            TMR0IF = 0;
            INT0IF = 0;
            PORTD = PORTD ^ 0x01;
        }  
    }
    else
    {
        INT0IF = 0;
    }
}
