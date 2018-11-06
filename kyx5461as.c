/*
 * File:   kyx5461as.c
 * Author: Jaerin Lee
 * Description: KYX-5461AS Quadruple 7-segment display module
 */

#include <xc.h>

#include "kyx5461as.h"

void kyx5461as_init_direct(void) {
    /* Set digit port as Output */
    DIGIT_DIR3 = 0;
    DIGIT_DIR2 = 0;
    DIGIT_DIR1 = 0;
    DIGIT_DIR0 = 0;
    
    /* Set digit port as initially HIGH */
    DIGIT_PORT3 = 1;
    DIGIT_PORT2 = 1;
    DIGIT_PORT1 = 1;
    DIGIT_PORT0 = 1;
    
    /* Set digit port as Output */
    SEGMENT_DIR7 = 0;
    SEGMENT_DIR6 = 0;
    SEGMENT_DIR5 = 0;
    SEGMENT_DIR4 = 0;
    SEGMENT_DIR3 = 0;
    SEGMENT_DIR2 = 0;
    SEGMENT_DIR1 = 0;
    SEGMENT_DIR0 = 0;
    
    /* Set digit port as initially LOW */
    SEGMENT_PORT7 = 0;
    SEGMENT_PORT6 = 0;
    SEGMENT_PORT5 = 0;
    SEGMENT_PORT4 = 0;
    SEGMENT_PORT3 = 0;
    SEGMENT_PORT2 = 0;
    SEGMENT_PORT1 = 0;
    SEGMENT_PORT0 = 0;
}

void kyx5461as_display_direct(uint8_t digit, uint8_t number, uint8_t dot) {
    if (digit >= 4 || number >= 10 || dot >= 2)
        return;
    
    switch (number) {
        case 0:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 1;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 0;
            break;
        case 1:
            SEGMENT_PORT7 = 0;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 0;
            SEGMENT_PORT3 = 0;
            SEGMENT_PORT2 = 0;
            SEGMENT_PORT1 = 0;
            break;
        case 2:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 0;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 1;
            SEGMENT_PORT2 = 0;
            SEGMENT_PORT1 = 1;
            break;
        case 3:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 0;
            SEGMENT_PORT2 = 0;
            SEGMENT_PORT1 = 1;
            break;
        case 4:
            SEGMENT_PORT7 = 0;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 0;
            SEGMENT_PORT3 = 0;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 1;
            break;
        case 5:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 0;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 0;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 1;
            break;
        case 6:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 0;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 1;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 1;
            break;
        case 7:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 0;
            SEGMENT_PORT3 = 0;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 0;
            break;
        case 8:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 1;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 1;
            break;
        case 9:
            SEGMENT_PORT7 = 1;
            SEGMENT_PORT6 = 1;
            SEGMENT_PORT5 = 1;
            SEGMENT_PORT4 = 1;
            SEGMENT_PORT3 = 0;
            SEGMENT_PORT2 = 1;
            SEGMENT_PORT1 = 1;
            break;
        default:
            break;
    }
    SEGMENT_PORT0 = dot;
    
    switch (digit)
    {
        case 0:
            DIGIT_PORT3 = 1;
            DIGIT_PORT2 = 1;
            DIGIT_PORT1 = 1;
            DIGIT_PORT0 = 0;
            break;
        case 1:
            DIGIT_PORT3 = 1;
            DIGIT_PORT2 = 1;
            DIGIT_PORT1 = 0;
            DIGIT_PORT0 = 1;
            break;
        case 2:
            DIGIT_PORT3 = 1;
            DIGIT_PORT2 = 0;
            DIGIT_PORT1 = 1;
            DIGIT_PORT0 = 1;
            break;
        case 3:
            DIGIT_PORT3 = 0;
            DIGIT_PORT2 = 1;
            DIGIT_PORT1 = 1;
            DIGIT_PORT0 = 1;
            break;
    }
    return;
}

