#ifndef __APP_H__
#define	__APP_H__
#include "bc95.h"
#include "tds.h"
#include "tools.h"
#include <string.h>

#define QR_CODE_LEN 20

typedef struct{
    uint8_t     processing_status;
    uint8_t     boot;                   //设备开关机
    uint8_t     arrears_boot;           //停机开关机
    uint8_t     device_registe;         //设备注册状态
    uint8_t     device_mode;            //设备类型
    uint16_t    pure_tds;
    uint16_t    raw_tds;
    uint32_t    time;
    uint32_t    flow;
    uint8_t     filter[10];
    uint8_t     rinse;                  //冲洗
    uint8_t     qr_code[QR_CODE_LEN];

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


#endif