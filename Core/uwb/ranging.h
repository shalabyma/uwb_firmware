/**
  ******************************************************************************
  * @file    ranging.h
  * @brief   This file contains all the function prototypes for
  *          the ranging.c file
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RANGING_H__
#define __RANGING_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

/* Function Prototypes -------------------------------------------------------*/
int do_owr(void);
int do_twr(void);
void listen(void);
void listen_twr(void);
void uwb_init(void);
void reset_DW1000(void);

#define UUS_TO_DWT_TIME 65536
/* Default antenna delay values for 64 MHz PRF. */
#define TX_ANT_DLY 16436
#define RX_ANT_DLY 16436

#ifdef __cplusplus
}
#endif

#endif /* __RANGING_H__ */