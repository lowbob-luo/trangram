#ifndef MY_ADC_H
#define MY_ADC_H

#include <stdio.h>
#include <stdlib.h>
#include "driver/adc.h"
#include "driver/gpio.h"
#include "hal/adc_types.h"

#define WIDTH    ADC_WIDTH_BIT_12
#define CHANNEL  ADC_CHANNEL_6 // GPIO34 if ADC1, GPIO14 if ADC2
#define ATTEN    ADC_ATTEN_DB_11

#define ENTER 1
#define LEFT 2
#define RIGHT 3
#define FORWARD 4
#define BACKWARD 5
#define DELETE 6
#define ESC 7
#define RUN 8

void adc_Init(adc_bits_width_t width_bit,adc_channel_t channel,adc_atten_t atten);
int adc_read(adc_channel_t channel);
uint8_t keypad_scan(void);
int middleFilter(int in_data);

#endif
