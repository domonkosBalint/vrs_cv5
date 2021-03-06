/*
 * vrs_cv5.h
 *
 *  Created on: 18. 10. 2016
 *      Author: B�lint
 */

#ifndef VRS_CV5_H_
#define VRS_CV5_H_

#include "stm32l1xx.h"

void nvicInit(void);
void gpioInit(void);
void delay(int pocet);
void adcInit(void);
void ADC1_IRQHandler(void);
void setFrek(uint16_t ADvalue);

#endif /* VRS_CV5_H_ */
