#ifndef __TOOLS_H__
#define	__TOOLS_H__
#include "main.h"
#include "stm32f1xx_hal.h"
#include "app.h"

#define FLASH_DATA_ADDR 0x0800F000
#define FLASH_DATA_LEN  50

#define FIRST_BOOT_ADDR   0
#define REGISTE_ADDR      1
#define PURE_TDS_ADDR     2
#define RAW_TDS_ADDR      3
#define TIME_ADDR         4
#define FLOW_ADDR         5
#define BOOT_ADDR         6
#define DEVICE_MODE_ADDR  7         //1:租赁  2：零售 
#define QR_CODE_MODE_ADDR 8
#define FILTER_ADDR       7         //10个滤芯，依次后排    到17


extern uint32_t flash_pages_data[FLASH_DATA_LEN];

uint8_t *_itoa(int value, uint8_t *string, int radix);
int myatoi(const char *str);

uint8_t *ByteToHexStr(const uint8_t* source, uint32_t sourceLen);
void HexToStr(uint8_t *pbDest, uint8_t *pbSrc, uint32_t nLen);
uint8_t *high_befor_low(uint8_t *data, uint8_t length);

void flash_write(uint32_t *data);
void flash_write_word(uint8_t address, uint32_t data);
uint32_t flash_read(uint32_t addr);

#endif