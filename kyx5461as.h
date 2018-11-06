/* 
 * File:   kyx5461as.h
 * Author: Jaerin Lee
 * Comments:
 * Revision history: 
 */

#ifndef KYX5461AS_H
#define	KYX5461AS_H

#include <xc.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif


/*
 * 
 */
    
    
/* Direct ports
 * 
 */
#define SEGMENT_DIR7    TRISAbits.TRISA7
#define SEGMENT_PORT7   LATAbits.LATA7

#define SEGMENT_DIR6    TRISAbits.TRISA6
#define SEGMENT_PORT6   LATAbits.LATA6

#define SEGMENT_DIR5    TRISAbits.TRISA5
#define SEGMENT_PORT5   LATAbits.LATA5

#define SEGMENT_DIR4    TRISAbits.TRISA4
#define SEGMENT_PORT4   LATAbits.LATA4

#define SEGMENT_DIR3    TRISAbits.TRISA3
#define SEGMENT_PORT3   LATAbits.LATA3

#define SEGMENT_DIR2    TRISAbits.TRISA2
#define SEGMENT_PORT2   LATAbits.LATA2

#define SEGMENT_DIR1    TRISAbits.TRISA1
#define SEGMENT_PORT1   LATAbits.LATA1

#define SEGMENT_DIR0    TRISAbits.TRISA0
#define SEGMENT_PORT0   LATAbits.LATA0

#define DIGIT_DIR3      TRISBbits.TRISB3
#define DIGIT_PORT3     LATBbits.LATB3

#define DIGIT_DIR2      TRISBbits.TRISB2
#define DIGIT_PORT2     LATBbits.LATB2

#define DIGIT_DIR1      TRISBbits.TRISB1
#define DIGIT_PORT1     LATBbits.LATB1

#define DIGIT_DIR0      TRISBbits.TRISB0
#define DIGIT_PORT0     LATBbits.LATB0


/* Function declaration */
void kyx5461as_init_direct(void);
void kyx5461as_display_direct(uint8_t digit, uint8_t number, uint8_t dot);

#ifdef	__cplusplus
}
#endif

#endif	/* KYX5461AS_H */

