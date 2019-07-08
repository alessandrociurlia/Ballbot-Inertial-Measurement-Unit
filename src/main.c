/* Authors: Alessandro Ciurlia, Human Mahdavidaronkola, Giacomo D'Amicantonio, Simone Marroncelli, Raffaele Berchicci */

/*******************************************************************************
Includes: <System Includes> , "Project Includes"
*******************************************************************************/
#include "platform.h"
#include "S12ADC.h"
#include "main.h"

/*******************************************************************************
Definizione strutture
*******************************************************************************/
IMU_data_struct IMU;

/*******************************************************************************
* Nome funzione     : main
* Descrizione  	    : Funzione principale del programma
* Argomenti         : No
* Valori restituiti : No
*******************************************************************************/
void main(void)
{
    /* Inizializza il display LCD */
	lcd_initialize();
    
    /* Pulisce il display LCD */
    lcd_clear();
    
    /* Inizializza l'A/D converter 12-bit */
    S12ADC_init();

    /* Inizializza l'IMU */
    IMU_init(&IMU);

    /* Loop principale*/
    while (1)
    {
    	/* Acquisisce i risultati dall'IMU*/
    	IMU_result(&IMU);

    	/* Stampa i risultati sul display LCD*/
    	IMU_update(&IMU);
    }
} /* Fine main() */
