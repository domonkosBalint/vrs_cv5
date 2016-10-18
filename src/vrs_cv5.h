/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: Bálint
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_

#include "stm32l1xx.h"

void adcIRQInit(void);
void ledInit(void);
void delay(int pocet);
void adcInit(void);

#endif /* VRS_CV5_H_ */
