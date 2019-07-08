/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 15.02.2012     1.00        First release
*******************************************************************************/
#ifndef _S12ADC_H_
#define _S12ADC_H_

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdbool.h>

/* Values for conversion of S12ADC counts to voltage */
#define MAX_COUNTS 4095.0
#define VREFH 3.3
#define VREFL 0.0

/******************************************************************************
Prototypes for exported functions
******************************************************************************/
void S12ADC_init (void) ;
void S12ADC_start (void) ;
bool S12ADC_conversion_complete (void) ;
uint16_t S12ADC_read (void) ;

#endif
