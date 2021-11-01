/**
  ******************************************************************************
  * @file    common.c
  * @brief   This file provides general code to be used by all submodules.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "common.h"

void convert_float_to_string(char* str,float data){
	int int_part, dec_part;
	int_part = (int) data;
	dec_part = (int) ((data-(float)int_part)*10000.0);

	if (dec_part < 0 && int_part >= 0){
		sprintf(str,(char*)"-%d.%d",int_part,-dec_part);
	}
	else if (dec_part < 0){
		sprintf(str,(char*)"%d.%d",int_part,-dec_part);
	}
	else{
		sprintf(str,(char*)"%d.%d",int_part,dec_part);
	} 
}

void convert_elementR3_to_string(char* str, element_R3 data){
	char x_str[5], y_str[5], z_str[5];

	convert_float_to_string(x_str, data.x);
	convert_float_to_string(y_str, data.y);
	convert_float_to_string(z_str, data.z);

	sprintf(str,(char*)"[%s, %s, %s]",x_str,y_str,z_str);
}

void usb_print(char* c){
    CDC_Transmit_FS(c,strlen(c));
}