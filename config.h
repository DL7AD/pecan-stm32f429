


typedef struct {
	int32_t cycletime;
	(void*) cycleMethod;
	uint8_t radio;
	uint16_t power;
	uint32_t frequency;
	mod_t modulation;
	(void*) sleepMethod;
} module_params_t;

#define MODULE_POS(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_pos, NULL); \
}

#define MODULE_SAT(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT,TLE1,TLE2) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	parm.cycleMethod = sgp4_visible(TLE1, TLE2); \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_pos, NULL); \
}

#define MODULE_TEL(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_tel, NULL); \
}

#define MODULE_IMG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_img, NULL); \
}

#define MODULE_LOG(CYCLE,PWRSAVE,FREQ,PWR,MOD,PROT) { \
	module_params_t parm; \
	parm.cycletime = CYCLE; \
	parm.radio = RADIO; \
	parm.power = PWR; \
	parm.modulation = MOD; \
	chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(1024), NORMALPRIO, module_log, NULL); \
}

#define MOD_ACTIVE	0
#define MOD_SLEEP	1

#define MOD_2FSK	0
#define MOD_AFSK	1

#define PWR_1MW		1
#define PWR_10MW	10
#define PWR_50MW	17
#define PWR_100MW	20
#define PWR_1W		30
#define PWR_2W		33

#define APRS_REGION_FREQ		getAPRSRegionFrequency(void)
#define SYM_BALLOON				/O
#define SYM_SMALLAIRCRAFT		/'
#define SYM_SATELLITE			\S

# Sleep functions
void SLEEP_BELOW_BATTVOLT(v)			{ getBatteryVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE; }
void SLEEP_BELOW_SOLVOLT(v)				{ getSolarVoltage() < (v) ? MOD_SLEEP : MOD_ACTIVE; }
void SLEEP_BELOW_SOLBATTVOLT(sol, batt)	{ getSolarVoltage() < (sol) || getBatteryVoltage() < (batt) ? MOD_SLEEP : MOD_ACTIVE; }

# Hardware definitions
#define OSC_FREQ				26000000		/* Oscillator frequency */
#define CAM_AVAIL				TRUE			/* Camera available */
#define GPS_AVAIL				TRUE			/* uBlox MAX7/8 GNSS receiver available */
#define SD_AVAIL				TRUE			/* microSD card available */
#define RADIO1_AVAIL			TRUE			/* Radio 1 available */
#define RADIO2_AVAIL			TRUE			/* Radio 2 available */
#define BME280_AVAIL			TRUE			/* BME280 air pressure sensor available */
#define MPU9250_AVAIL			TRUE			/* MPU9250 9 axis sensor available */

#define CHECK_RADIO1_BAND(f)	(144000000 <= f && f <= 148000000) /* Frequency range of Radio 1 */
#define CHECK_RADIO2_BAND(f)	(420000000 <= f && f <= 450000000) /* Frequency range of Radio 2 */


# User definitions
#define APRS_CALLSIGN			DL7AD			/* APRS callsign */
#define APRS_SSID				11				/* APRS SSID */
#define APRS_SYMBOL				SYM_BALLOON		/* APRS symbol */
#define APRS_PATH				WIDE1,WIDE2-1	/* APRS path */
#define APRS_PATH_SAT			RS0ISS			/* APRS path */
#define APRS_TXDELAY			200				/* APRS preamble length */

#define GPS_ACQUISITION_TIMEOUT	120				/* GPS acquisition timeout */
#define GPS_FIX_TIMEOUT			120				/* GPS fix gets outdated after */

#define LOG_SIZE				14				/* Log size in days */
#define LOG_CYCLE				120				/* Log cycle in minutes */
#define LOG_TRX_NUM				6				/* Log message that are transmitted in one packet */

#define CALLSIGN_APRS_FSK		D-11			/* FSK callsign for RTTY and DominoEX */

# Module definitions (can be any number of modules)
#define MODULES { \
	MODULE_SD(); \
	MODULE_CAM(); \
	MODULE_GPS(); \
	MODULE_SEN(); \
	\
	MODULE_POS(120, SLEEP_BELOW_BATTVOLT(2.7), APRS_REGION_FREQ, PWR_10MW, MOD_AFSK, PROT_APRS); \
	MODULE_TEL(120, SLEEP_BELOW_BATTVOLT(2.7), APRS_REGION_FREQ, PWR_10MW, MOD_AFSK, PROT_APRS); \
	MODULE_LOG(120, SLEEP_BELOW_BATTVOLT(3.3), APRS_REGION_FREQ, PWR_10MW, MOD_AFSK, PROT_APRS); \
	\
	MODULE_SAT(60,  SLEEP_BELOW_BATTVOLT(3.0), 145825000, PWR_2W, MOD_AFSK, PROT_APRS, TLE1, TLE2); \
	\
	MODULE_IMG(0, SLEEP_BELOW_SOLBATTVOLT(0.5, 4.0), 434500000, PWR_10MW, MOD_2FSK, PROT_SSDV); \
	MODULE_TEL(20, SLEEP_BELOW_SOLBATTVOLT(0.5, 4.0), 434500000, PWR_10MW, MOD_2FSK, PROT_UKHAS); \
}













