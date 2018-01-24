#include "tds.h"

uint32_t value_arr[ADC_NUMBER] = {0};
uint8_t  conversion_ok = 0;

void adc_get(){
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, value_arr, ADC_NUMBER);
    while(!conversion_ok);
    conversion_ok = 0;

}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
    conversion_ok = 1;
}