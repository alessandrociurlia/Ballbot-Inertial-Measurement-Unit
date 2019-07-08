/* Authors: Alessandro Ciurlia, Human Mahdavidaronkola, Giacomo D'Amicantonio, Simone Marroncelli, Raffaele Berchicci */

/*******************************************************************************
Includes: <System Includes> , "Project Includes"
*******************************************************************************/
#include <machine.h>
#include <mathf.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "CMT.h"
#include "IMU.h"
#include "r_riic_rx600.h"
#include "r_riic_rx600_master.h"

/*******************************************************************************
* Nome funzione     : IMU_init
* Descrizione  	    : Inizializza l'IMU
* Argomenti         : (IMU_data struct) *x -
* 						puntatore alla struttura dell'IMU
* Valori restituiti : No
*******************************************************************************/
void IMU_init(IMU_data_struct *x)
{
	/* Definisce le variabili locali */
    uint8_t target_data = 0;
    riic_ret_t ret = RIIC_OK;

    /* Inizializza il CMT */
    CMT_init();

    /* Inizializza l'IIC */
	R_RIIC_Init(&riic_master_config);

	/* Resetta l'IMU (si assicura che il bit dello stato precedente non sia presente) */
    do
    {
		target_data = INV_MPU6050_BIT_H_RESET;
		ret = IMU_write(CHANNEL_0, MPU_ADDRESS, INV_MPU6050_REG_PWR_MGMT_1, &target_data, 1);

    } while(RIIC_OK != ret);

    /* Disattiva/Attiva lo stato di alimentazione (dopo il reset, il bit di sospensione
     potrebbe essere acceso o spento a seconda delle impostazioni OTP) */
    ms_delay(INV_MPU6050_POWER_UP_TIME);
    do
    {
		ret = IMU_set_power(false);

    } while(RIIC_OK != ret);

    ms_delay(INV_MPU6050_POWER_UP_TIME);
    do
    {
		ret = IMU_set_power(true);

    } while(RIIC_OK != ret);

    /* Configura l'IMU */
    do
    {
		ret = IMU_config();

    } while(RIIC_OK != ret);

    /* Inizializza l'accelerometro */
    Accel_init(x);

    /* Inizializza il giroscopio */
    Gyro_init(x);

} /* Fine IMU_init() */

/*******************************************************************************
* Nome funzione     : IMU_result
* Descrizione  	    : Acquisice i dati dall'IMU
* Argomenti         : (IMU_data struct) *x -
* 						puntatore alla struttura dell'IMU
* Valori restituiti : No
*******************************************************************************/
void IMU_result(IMU_data_struct *x)
{
	/* Definisce le variabili locali */
	uint8_t data[6];
	int16_t raw_data[6];
	float ax, ay, az, gx, gy, gz;

	/* Legge i valori dall'accelerometro */
	IMU_read(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_RAW_ACCEL_X, data, 6);

	/* Esegue il masking (unisce gli 8 bit trasmessi tramite IIC di ogni componente in un vettore di 6 elementi ognuno
	 di 16 bit. Esegue lo shift degli 8 bit verso sinistra e, con un AND bit a  bit ("&"), ottiene una variabile i cui
	 primi 8 bit sono uguali a data[0] e gli ultimi 8 sono 0. Siamo sicuri di  questo grazie all'AND eseguito
	 con 0xFF00 (0xFF00 = 11111111 00000000). Poi con un OR bit a bit ("|") ottiene il valore unito e completo in
	 un unica cella di memoria da 16 bit) */
	raw_data[0] = (int16_t)((((uint16_t)data[0]) << 8) & 0xFF00);
	raw_data[0] |= data[1]; /*raw_data[0] ora contiene il dato grezzo letto del registro x dell'accelerometro */

	raw_data[1] = (int16_t)((((uint16_t)data[2]) << 8) & 0xFF00);
	raw_data[1] |= data[3]; /*raw_data[1] ora contiene il dato grezzo letto del registro y dell'accelerometro */

	raw_data[2] = (int16_t)((((uint16_t)data[4]) << 8) & 0xFF00);
	raw_data[2] |= data[5]; /*raw_data[2] ora contiene il dato grezzo letto del registro z dell'accelerometro */

	/* Calibra i valori sulla sensitività scelta per l'accelerometro */
	ax = (float)raw_data[0]/16384;
	ay = (float)raw_data[1]/16384;
	az = (float)raw_data[2]/16384;

	/* Calcola gli angoli */
	x->RollRad  = atanf(ay/sqrtf(ax*ax + az*az));
	x->PitchRad = atanf(-ax/sqrtf(ay*ay+az*az));
	x->YawRad  =  atanf(az/sqrtf(ax*ax + ay*ay));

	/* Calibra gli angoli (rad) sottraendo l'offset e li memorizza nella struttura */
	x->RollRad  = x->RollRad  -  x->off_RollRad;
	x->PitchRad = x->PitchRad -  x->off_PitchRad;
	x->YawRad   = x->YawRad   -  x->off_YawRad;

	/* Converte gli angoli in gradi e li memorizza nella struttura */
	x->RollDeg  = x->RollRad  * (180.0/M_PI);
	x->PitchDeg = x->PitchRad * (180.0/M_PI);
	x->YawDeg   = x->YawRad   * (180.0/M_PI);

	/* Legge i valori dal giroscopio */
	IMU_read(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_RAW_GYRO_X, data, 6);

	/* Esegue il masking */
	raw_data[3] = (int16_t)((((uint16_t)data[0]) << 8) & 0xFF00);
	raw_data[3] |= data[1];  /*raw_data[3] ora contiene il dato grezzo del registro x del giroscopio*/

	raw_data[4] = (int16_t)((((uint16_t)data[2]) << 8) & 0xFF00);
	raw_data[4] |= data[3]; /*raw_data[4] ora contiene il dato grezzo del registro y del giroscopio*/

	raw_data[5] = (int16_t)((((uint16_t)data[4]) << 8) & 0xFF00);
	raw_data[5] |= data[5]; /*raw_data[5] ora contiene il dato grezzo del registro z del giroscopio*/

	/* Calibra i valori sulla sensitività scelta per il giroscopio */
	gx = (float)raw_data[3]/131;
	gy = (float)raw_data[4]/131;
	gz = (float)raw_data[5]/131;

	/* Calibra le velocità angolari (grad/s) sottraendo l'offset e le memorizza nella struttura */
	x->omegaRollDeg  = gx - x->off_omegaRollDeg;
	x->omegaPitchDeg = gy - x->off_omegaPitchDeg;
	x->omegaYawDeg   = gz - x->off_omegaYawDeg;

	/* Converte le velocità angolari in rad/s e le memorizza nella struttura */
	x->omegaRollRad  = x->omegaRollDeg  * (M_PI/180.0);
	x->omegaPitchRad = x->omegaPitchDeg * (M_PI/180.0);
	x->omegaYawRad   = x->omegaYawDeg   * (M_PI/180.0);

} /* Fine IMU_result() */

/*******************************************************************************
* Nome funzione     : IMU_write
* Descrizione  	    : Scrive un numero specifico di byte sull'IMU
* Argomenti         : (uint8_t) riic_channel -
* 					  	 quale canale iic deve usare il microcontrollore
* 					  (uint8_t) slave_addr -
* 					  	 indirizzo slave
* 					  (uint8_t) register_number -
* 					  	 registro slave su cui scrive il master
* 					  (uint8_t) *source_buff -
* 					  	 puntatore al vettore da cui vengono copiati i dati
* 					  	 da scrivere
* 					  (uint32_t) num_byte -
* 					     numero di byte da scrivere
* Valori restituiti : (riic_ret_t) ret -
* 						 risultato della comunicazione
*******************************************************************************/
static riic_ret_t IMU_write (uint8_t riic_channel, uint8_t slave_addr, uint8_t register_number, uint8_t *source_buff, uint32_t num_bytes)
{
	/* Definisce le variabili locali */
    uint8_t   addr_and_register[2]={slave_addr, register_number};
    riic_ret_t  ret = RIIC_OK;


    /* Il master trasmette indirizzo e numero di registro dello slave su cui vuole scrivere */
    ERR_COUNT=0;
    ret |= R_RIIC_MasterTransmitHead(CHANNEL_0, addr_and_register, 2);

    /* Controlla se si sono verificati errori */
    if(ret != RIIC_OK)
    {
    	ERROR_HEAD_WRITE = 1;
    	ERR_COUNT++;
    	if (ERR_COUNT == 50) return ret;
    	IMU_write (riic_channel, slave_addr, register_number, source_buff, num_bytes);
    }

    /* Il master trasmette i dati presi dal source_buff sul registro */
    ERR_COUNT=0;
    ret |= R_RIIC_MasterTransmit(CHANNEL_0, source_buff, num_bytes);

    /* Controlla se si sono verificati errori */
    if(ret != RIIC_OK) {
    	ERROR_WRITE = 1;
    	ERR_COUNT++;
    	if (ERR_COUNT == 50) return ret;
    	IMU_write (riic_channel, slave_addr, register_number, source_buff, num_bytes);
    }

    return ret;

} /* Fine IMU_write() */

/*******************************************************************************
* Nome funzione     : IMU_read
* Descrizione  	    : Legge un numero specifico di byte dall'IMU
* Argomenti         : (uint8_t) riic_channel -
* 					  	 quale canale iic deve usare il microcontrollore
* 					  (uint8_t) slave_addr -
* 					  	 indirizzo slave
* 					  (uint8_t) register_number -
* 					  	 registro slave da cui legge il master
* 					  (uint8_t) *dest_buff -
* 					  	 puntatore al vettore su cui vengono copiati i dati
* 					  	 letti
* 					  (uint32_t) num_byte -
* 					  	 numero di byte da leggere
* Valori restituiti : (riic_ret_t) ret -
* 						 risultato della comunicazione
*******************************************************************************/
static riic_ret_t IMU_read(uint8_t riic_channel, uint8_t slave_addr, uint8_t register_number, uint8_t *dest_buff, uint32_t num_bytes)
{
	/* Definisce le variabili locali */
	riic_ret_t  ret = RIIC_OK;
	uint8_t     addr_and_register[2] = {slave_addr, register_number};


	/* Il master trasmette indirizzo e numero di registro dello slave da cui vuole leggere */
	ERR_COUNT=0;
	ret |= R_RIIC_MasterTransmitHead(riic_channel, addr_and_register, 2);

	/* Controlla se si sono verificati errori */
	if(ret != RIIC_OK)
	{
		ERROR_HEAD_READ = 1;
		ERR_COUNT++;
		if (ERR_COUNT == 50) return ret;
        IMU_read (riic_channel, slave_addr, register_number, dest_buff, num_bytes);
	}

	/* Il master riceve i dati presi dal registro sul dest_buff  */
	ERR_COUNT=0;
	ret |= R_RIIC_MasterReceive(riic_channel, slave_addr, dest_buff, num_bytes);

	/* Controlla se si sono verificati errori */
	if(ret != RIIC_OK)
	{
		ERROR_READ = 1;
		ERR_COUNT++;
		if (ERR_COUNT == 50) return ret;
    	IMU_read (riic_channel, slave_addr, register_number, dest_buff, num_bytes);
	}

	return ret;

} /* Fine IMU_read() */

/*******************************************************************************
* Nome funzione     : IMU_axis_read
* Descrizione  	    : Legge i dati dai singoli assi dell'accelerometro e del
* 					  giroscopio dell'IMU
* Argomenti         : (uint8_t) axis -
* 						 registro del singolo asse
* Valori restituiti : (int16_t) axis_val -
* 						 valore del singolo asse letto
*******************************************************************************/
static int16_t  IMU_axis_read (uint8_t axis)
{
	/* Definisce le variabili locali */
    int16_t    axis_val=0;
    uint8_t    reg = axis;
    uint8_t    data[2];
    riic_ret_t ret;
    unsigned char local_index = 0;

    /* Legge i valori dal singolo asse */
    ms_delay(1);
    ret = IMU_read(RIIC_CHANNEL, MPU_ADDRESS, reg, data, 2);

    /* Controlla se si sono verificati errori */
    while (RIIC_OK != ret)
    {
        IMU_axis_read (axis);
    }

    /* Esegue il masking */
    for(local_index = 0; local_index < 8; local_index++)
      {
    	if(data[0] & (1 << local_index)) axis_val |= ((uint16_t)1 << (8 + local_index));
    	if(data[1] & (1 << local_index)) axis_val |= ((uint16_t)1 << local_index);
      }

    return axis_val;

} /* Fine IMU_axis_read() */

/*******************************************************************************
* Nome funzione     : Accel_init
* Descrizione  	    : Inizializza l'accelerometro
* Argomenti         : (IMU_data_struct) *x -
*   					 puntatore alla struttura dell'IMU
* Valori restituiti : No
*******************************************************************************/
void Accel_init(IMU_data_struct *x)
{
	/* Definisce le variabili locali */
	float raw_data_zero[3], Rad[3], off_Rad[3]={0};
	float ax_zero = 0;
	float ay_zero = 0;
	float az_zero = 0;

	/* Esegue le prime 10 letture a vuoto (stabilizzazione dei valori di accelerazione) */
	for (int i = 0; i < 10; i++)
    {
       IMU_axis_read(INV_MPU6050_REG_RAW_ACCEL_X);
       IMU_axis_read(INV_MPU6050_REG_RAW_ACCEL_Y);
       IMU_axis_read(INV_MPU6050_REG_RAW_ACCEL_Z);
    }

	/* Esegue 100 letture */
	for (int i = 0; i < 100; i++)
	{
		/* Legge i valori grezzi */
		raw_data_zero[0] = (float)IMU_axis_read(INV_MPU6050_REG_RAW_ACCEL_X);
	    raw_data_zero[1] = (float)IMU_axis_read(INV_MPU6050_REG_RAW_ACCEL_Y);
	    raw_data_zero[2] = (float)IMU_axis_read(INV_MPU6050_REG_RAW_ACCEL_Z);

	    /* Calibra i valori sulla sensitività scelta per l'accelerometro */
	    ax_zero = raw_data_zero[0]/16384;
	    ay_zero = raw_data_zero[1]/16384;
	    az_zero = raw_data_zero[2]/16384;

	    /* Calcola gli angoli */
	    Rad[0] = atanf(ay_zero/sqrtf(ax_zero*ax_zero+az_zero*az_zero));
	    Rad[1] = atanf(-ax_zero/sqrtf(ay_zero*ay_zero+az_zero*az_zero));
	    Rad[2] = atanf(az_zero/sqrtf(ax_zero*ax_zero+ay_zero*ay_zero));

	    /* Somma gli angoli misurati  */
	    off_Rad[0] += Rad[0];
	    off_Rad[1] += Rad[1];
	    off_Rad[2] += Rad[2];
    }

	/* Determina i valori medi, ossia gli angoli di offset (rad), e li memorizza nella struttura */
	x->off_RollRad  = off_Rad[0]/100;
	x->off_PitchRad = off_Rad[1]/100;
	x->off_YawRad   = off_Rad[2]/100;

	/* Converte gli angoli di offset in gradi e li memorizza nella struttura */
	x->off_RollDeg  = x->off_RollRad  * (180.0/M_PI);
	x->off_PitchDeg = x->off_PitchRad * (180.0/M_PI);
	x->off_YawDeg   = x->off_YawRad   * (180.0/M_PI);

} /* Fine Accel_init() */

/*******************************************************************************
* Nome funzione     : Gyro_init
* Descrizione  	    : Inizializza il giroscopio
* Argomenti         : (IMU_data_struct) *x -
*   					 puntatore alla struttura dell'IMU
* Valori restituiti : No
*******************************************************************************/
void Gyro_init(IMU_data_struct *x)
{
	/* Definisce le variabili locali */
	float raw_data_zero[3], off_omegaDeg[3];
	float gx_zero = 0;
	float gy_zero = 0;
	float gz_zero = 0;

	/* Esegue le prime 10 letture a vuoto (stabilizzazione dei valori di velocità) */
	for (int i = 0; i < 10; i++)
	{
		IMU_axis_read(INV_MPU6050_REG_RAW_GYRO_X);
		IMU_axis_read(INV_MPU6050_REG_RAW_GYRO_Y);
		IMU_axis_read(INV_MPU6050_REG_RAW_GYRO_Z);
	}

	/* Esegue 100 letture */
	for (int i = 0; i < 100; i++)
	{
		/* Legge i valori grezzi */
		raw_data_zero[0] = (float)IMU_axis_read(INV_MPU6050_REG_RAW_GYRO_X);
		raw_data_zero[1] = (float)IMU_axis_read(INV_MPU6050_REG_RAW_GYRO_Y);
		raw_data_zero[2] = (float)IMU_axis_read(INV_MPU6050_REG_RAW_GYRO_Z);

		/* Calibra i valori sulla sensitività scelta per il giroscopio */
		gx_zero = raw_data_zero[0]/131;
		gy_zero = raw_data_zero[1]/131;
		gz_zero = raw_data_zero[2]/131;

		/* Somma le velocità angolari misurate */
		off_omegaDeg[0] += gx_zero;
		off_omegaDeg[1] += gy_zero;
		off_omegaDeg[2] += gz_zero;
	}

    /* Determina i valori medi, ossia le velocità angolari di offset (grad/s), e le memorizza nella struttura */
	x->off_omegaRollDeg  = off_omegaDeg[0]/100;
	x->off_omegaPitchDeg = off_omegaDeg[1]/100;
	x->off_omegaYawDeg   = off_omegaDeg[2]/100;

	/* Converte le velocità angolari di offset in rad/s e le memorizza nella struttura*/
	x->off_omegaRollRad  = x->off_omegaRollDeg  * (M_PI/180.0);
    x->off_omegaPitchRad = x->off_omegaPitchDeg * (M_PI/180.0);
	x->off_omegaYawRad   = x->off_omegaYawDeg   * (M_PI/180.0);

} /* Fine Gyro_init() */

/*******************************************************************************
* Nome funzione     : IMU_config
* Descrizione  	    : Configura l'IMU
* Argomenti         : No
* Valori restituiti : (riic_ret_t) - ret
* 						 risultato della configurazione
*******************************************************************************/
static riic_ret_t IMU_config(void)
{
	/* Definisce le variabili locali */
	riic_ret_t ret;
	uint8_t d;

	/* Attiva lo stato di alimentazione */
	ms_delay(INV_MPU6050_POWER_UP_TIME);
	ret = IMU_set_power(true);

	/* Controlla se si sono verificati errori */
    if(RIIC_OK != ret){
    	return ret;
    }

	/* Configura l'accelerometro */
	d = (INV_MPU6050_FS_02G << INV_MPU6050_ACCL_CONFIG_FSR_SHIFT);
	ms_delay(1);
	ret = IMU_write(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_ACCEL_CONFIG, &d, 1); /* i bit 0,1,2 del registro INV_MPU6050_REG_ACCEL_CONFIG sono riservati e
    non si possono sovrascrivere. Avendo definito INV_MPU6050_FS_02G=0, eseguendo uno shift degli 8bit verso sinistra si avra' qualcosa del tipo 00000xxx.
    Ma gli ultimi tre bit (quelli scritti come x) non sono scrivibili sul registro INV_MPU6050_ACCEL_CONFIG_FSR_SHIFT quindi non importa cosa siano. I bit 3 e 4
    valgono 0 e indicano la scala di 2G, i bit 5, 6 e 7 indicano rispettivamente gli assi z, y e x e vengono quindi inizializzati al valore zero */

	/* Controlla se si sono verificati errori*/
    if(RIIC_OK != ret){
    	return ret;
    }

    /* Configura il giroscopio */
	d = (INV_MPU6050_FSR_250DPS << INV_MPU6050_GYRO_CONFIG_FSR_SHIFT); /* vale lo stesso discorso dell'accelerometro */
	ms_delay(1);
	ret = IMU_write(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_GYRO_CONFIG, &d, 1);

	/* Controlla se si sono verificati errori*/
    if(RIIC_OK != ret){
    	return ret;
    }

	/* Configura il filtro */
	d = INV_MPU6050_FILTER_20HZ;
	ms_delay(1);
	ret = IMU_write(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_CONFIG, &d, 1);

	/* Controlla se si sono verificati errori */
	if(RIIC_OK != ret) {
		return ret;
	}

	/* Configura la frequenza di campionamento */
	d = INV_MPU6050_ONE_K_HZ / INV_MPU6050_INIT_FIFO_RATE - 1;
	ms_delay(1);
	ret = IMU_write(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_SAMPLE_RATE_DIV, &d, 1);

	/* Controlla se si sono verificati errori */
	if(RIIC_OK != ret) {
		return ret;
	}

	return ret;

} /* Fine IMU_init_config() */

/******************************************************************************
* Nome funzione     : IMU_set_power
* Descrizione  	    : Attiva/disattiva lo stato di alimentazione dell'IMU
* Argomenti         : (bool) power on -
* 						 acceso/spento
* Valori restituiti : (riic_ret_t) ret -
* 						 risultato operazione
*******************************************************************************/
riic_ret_t IMU_set_power(bool power_on)
{
	/* Denifisce le variabili locali */
	riic_ret_t ret;
	uint8_t target_data;

	/* Setta lo stato di alimentazione */
	if (power_on)
	{
		target_data = 0;
		ret = IMU_write(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_PWR_MGMT_1, &target_data, 1);
	}
	else
	{
		target_data = INV_MPU6050_BIT_SLEEP;
		ret = IMU_write(RIIC_CHANNEL, MPU_ADDRESS, INV_MPU6050_REG_PWR_MGMT_1, &target_data, 1);
	}

	/* Controlla se si sono verificati errori */
	if(RIIC_OK != ret){
		return ret;
	}

	/* Introduce un delay se lo stato di alimentazione è attivo*/
	if (power_on) {
		ms_delay(INV_MPU6050_REG_UP_TIME);
	}

	return ret;

} /* Fine IMU_set_power() */

/*******************************************************************************
* Nome funzione     : IMU_update
* Descrizione  	    : Stampa i risultati acquisiti dell'IMU
* Argomenti         : (IMU_data_struct) *x -
* 						 puntatore alla struttura dell'IMU
* Valori restituiti : No
*******************************************************************************/
void IMU_update(IMU_data_struct *x)
{
   	uint8_t lcd_buffer[13];

    sprintf((char *)lcd_buffer, "Rg:%5.3f " , x->RollDeg);
   	lcd_display(LCD_LINE1, lcd_buffer);

   	sprintf((char *)lcd_buffer, "Pg:%5.3f ", x->PitchDeg);
   	lcd_display(LCD_LINE2, lcd_buffer);

   	sprintf((char *)lcd_buffer, "wRg:%5.3f" , x->omegaRollDeg);
   	lcd_display(LCD_LINE3, lcd_buffer);

   	sprintf((char *)lcd_buffer, "wPg:%5.3f", x->omegaPitchDeg);
   	lcd_display(LCD_LINE4, lcd_buffer);

} /* Fine IMU_update() */
