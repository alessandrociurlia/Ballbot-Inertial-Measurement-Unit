/* Authors: Alessandro Ciurlia, Human Mahdavidaronkola, Giacomo D'Amicantonio, Simone Marroncelli, Raffaele Berchicci */

/*******************************************************************************
Definzione struttura principale dell'IMU
*******************************************************************************/
typedef struct
{
	float off_RollRad;
	float off_PitchRad;
	float off_YawRad;
	float off_RollDeg;
	float off_PitchDeg;
	float off_YawDeg;
	float off_omegaRollRad;
	float off_omegaPitchRad;
	float off_omegaYawRad;
	float off_omegaRollDeg;
	float off_omegaPitchDeg;
	float off_omegaYawDeg;
	float RollRad;
	float PitchRad;
	float YawRad;
	float RollDeg;
	float PitchDeg;
	float YawDeg;
	float omegaRollRad;
	float omegaPitchRad;
	float omegaYawRad;
	float omegaRollDeg;
	float omegaPitchDeg;
	float omegaYawDeg;
	uint8_t channel;
	uint8_t slave_address;
	uint8_t register_number;

} IMU_data_struct;

/*******************************************************************************
Prototipi funzioni
*******************************************************************************/
void IMU_init(IMU_data_struct *x);
void IMU_result(IMU_data_struct *x);
void IMU_update(IMU_data_struct *x);

