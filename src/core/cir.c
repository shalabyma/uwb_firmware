#include "cir.h"
#include <math.h>

// #define READ_SIZE 100
#define NUM_CIR_POINTS 1016
#define ACCUM_DATA_LEN (NUM_CIR_POINTS)
static uint32 accum_data[ACCUM_DATA_LEN];

#define READ_SIZE 25
#define NUM_SYMBOLS 50
char buf[NUM_SYMBOLS*5], *pos = buf;

int read_cir(uint8_t initiator_id, uint8_t target_id){
	uint8 *cir; cir = (uint8 *)malloc((1+READ_SIZE*4)*sizeof(uint8));
	int16 real;
	int16 imag;

	uint16 first_path_idx = dwt_read16bitoffsetreg(
		RX_TIME_ID, 
		RX_TIME_FP_INDEX_OFFSET
	);

	for(int i = 0;i<NUM_CIR_POINTS;i+=READ_SIZE)
	{
		dwt_readaccdata(cir, (1+READ_SIZE*4), 0 + 4*i);
		// accum_data[i] = (uint32)sqrt(pow(real,2) + pow(imag,2));
		for (int j=0; j<READ_SIZE && j+i<NUM_CIR_POINTS; j++){
			real =  (int16)cir[4*j+2] << 8 | (int16)cir[4*j+1];
			imag =  (int16)cir[4*j+4] << 8 | (int16)cir[4*j+3];
			accum_data[j+i] = (uint32)(
				fmax(abs(real),abs(imag)) + fmin(abs(real),abs(imag))/4
			);
		}
	}
	free(cir);

	// osDelay(1);
	output_cir(initiator_id, target_id, first_path_idx);
	return 1;
}

void output_cir(uint8_t initiator_id, uint8_t target_id, uint16_t first_path_idx){
	char response[21];
	char* ptr = buf;

	for (int lv0=0; lv0<NUM_CIR_POINTS; lv0+=NUM_SYMBOLS){
		ptr = pos;
		for (int lv1=lv0; lv1<lv0+NUM_SYMBOLS && lv1<NUM_CIR_POINTS; ++lv1){
			if (lv1 == 0) {
				sprintf(
					response, "%s|%d|%d|%u|%u",
					"S10", initiator_id, target_id, 
					first_path_idx/64, (first_path_idx%64)*1000/64
				);
				strcpy(ptr, response);
				ptr += strlen(response);
			}

			sprintf(response, "|%lu", accum_data[lv1]);
			strcpy(ptr, response);
			ptr += strlen(response);
		}

		osDelay(1);

		usb_print(buf);

		// osDelay(1);
	}

	osDelay(1);

	usb_print("\r\n");

	osDelay(1);
}