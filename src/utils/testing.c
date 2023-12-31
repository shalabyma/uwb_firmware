/**
  ******************************************************************************
  * @file    testing.c
  * @brief   This file provides sample tests to be utilized in development.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "testing.h"
#include "cmsis_os.h"
#include "common.h"
#include <stdio.h>
#include "deca_device_api.h"

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: dw_test()
 *
 * The purpose of this function is to test if the UWB module has been
 * configured properly.
 * The expected output is 0xDECA0130.
 * 
 */
void dw_test(){
  uint32_t id;
  char print_buff[100];

  id = dwt_readdevid();
  sprintf(print_buff,"Id read = 0x%lx \n",id);
  usb_print(print_buff);
  
  osDelay(100);
} // end dw_test()

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: read_id()
 *
 * The purpose of this function is to test if the UWB module has been
 * given the ID programmed in main.h.
 * 
 */
void read_id(){
  uint8_t id;
  char print_buff[100];

  // id = dwt_readdevid();
  dwt_geteui(&id);
  sprintf(print_buff,"Id read = 0x%x \n",id);
  usb_print(print_buff);
  
  osDelay(100);
} // end dw_test()