#ifndef __APP_H__
#define	__APP_H__
#include "bc95.h"
#include "tds.h"
#include "tools.h"
#include <string.h>

#define QR_CODE_LEN 20

#define RINSE_PORT          GPIOB
#define RINSE_PIN           GPIO_PIN_9
#define open_rinse          HAL_GPIO_WritePin(RINSE_PORT, RINSE_PIN, ENABLE);
#define shut_rinse          HAL_GPIO_WritePin(RINSE_PORT, RINSE_PIN, DISABLE);

#define CREATE_WATER_PORT   GPIOB
#define CREATE_WATER_PIN    GPIO_PIN_8
#define open_create_water   HAL_GPIO_WritePin(CREATE_WATER_PORT, CREATE_WATER_PIN, ENABLE);
#define shut_create_water   HAL_GPIO_WritePin(CREATE_WATER_PORT, CREATE_WATER_PIN, DISABLE);

#define PUMP_PORT           GPIOB
#define PUMP_PIN            GPIO_PIN_7
#define open_pump           HAL_GPIO_WritePin(PUMP_PORT, PUMP_PIN, ENABLE);
#define shut_pump           HAL_GPIO_WritePin(PUMP_PORT, PUMP_PIN, DISABLE);

#define start_create_water  open_create_water; open_pump; HAL_TIM_Base_Start_IT(&htim4);

#define stop_create_water   shut_create_water; shut_pump; HAL_TIM_Base_Stop_IT(&htim4);

#define start_rinse         start_create_water; open_rinse;
#define stop_rinse          stop_create_water;  shut_rinse;

#define BEEP_PORT           GPIOC
#define BEEP_PIN            GPIO_PIN_6
#define beep(time)          HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, ENABLE);\
                            HAL_Delay(time);\
                            HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, DISABLE);

#define LOW_SWITCH_PORT     GPIOA
#define LOW_SWITCH_PIN      GPIO_PIN_11

#define HIGH_SWITCH_PORT    GPIOA
#define HIGH_SWITCH_PIN     GPIO_PIN_12

#define SYSTEM_LED_PORT     GPIOA
#define SYSTEM_LED_PIN      GPIO_PIN_15
#define _system_led         HAL_GPIO_TogglePin(SYSTEM_LED_PORT, SYSTEM_LED_PIN);

#define OPEN_RINSE_SWITCH   1

typedef struct{
    uint8_t      processing_status;
    uint32_t     boot;                   //设备开关机
    uint32_t     arrears_boot;           //停机开关机
    uint32_t     device_registe;         //设备注册状态
    uint32_t     device_mode;            //设备类型
    uint16_t     pure_tds;
    uint16_t     raw_tds;
    uint32_t     time;
    uint32_t     flow;
    uint32_t     filter[10];
    uint32_t     rinse;                  //冲洗
    uint8_t      rinse_lock;             //冲洗锁
    uint32_t     rinse_time;             //冲洗时间
    uint8_t      rinse_time_count;       //冲洗了多长时间
    uint8_t      qr_code[QR_CODE_LEN+1];
    uint32_t     create_water_time_s;    //制水时间秒
    uint32_t     create_water_time_m;    //制水时间分钟
    uint32_t     create_water_rinse;     //制水多长时间冲洗 分钟
    uint32_t     create_water_rinse_count;
}device_statusTypeDef;

extern device_statusTypeDef device_status; 

typedef struct{
    uint8_t bc95_init_error;
    uint8_t leakage;
    uint8_t raw_no_water;
    uint8_t create_water_too_long;
}device_errorTypeDef;

extern device_errorTypeDef device_error;

void init_flash();
void init_device_from_flash();
uint8_t registe_device();
uint8_t get_low_switch();
uint8_t get_high_switch();


#endif