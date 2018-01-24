#include "tools.h"
#include <stdlib.h>

uint32_t flash_pages_data[FLASH_DATA_LEN] = {0};

uint8_t *_itoa(int value, uint8_t *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

int myatoi(const char *str)
{
	int s=0;
	uint8_t falg=0;
	
	while(*str==' ')
	{
		str++;
	}

	if(*str=='-'||*str=='+')
	{
		if(*str=='-')
		falg=1;
		str++;
	}

	while(*str>='0'&&*str<='9')
	{
		s=s*10+*str-'0';
		str++;
		if(s<0)
		{
			s=2147483647;
			break;
		}
	}
	return s*(falg?-1:1);
}

void HexToStr(uint8_t *pbDest, uint8_t *pbSrc, uint32_t nLen)
{
	char ddl,ddh;
	int i;
	for (i=0; i<nLen; i++)
	{
		ddh = 48 + pbSrc[i] / 16;
		ddl = 48 + pbSrc[i] % 16;
		if (ddh > 57) ddh = ddh + 7;
		if (ddl > 57) ddl = ddl + 7;
		pbDest[i*2] = ddh;
		pbDest[i*2+1] = ddl;
	}
	pbDest[nLen*2] = '\0';
}

uint8_t *ByteToHexStr(const uint8_t* source, uint32_t sourceLen)  
{  
    uint8_t a[100] = {0};
    uint8_t *dest = a;
    short i;  
    unsigned char highByte, lowByte;  
  
    for (i = 0; i < sourceLen; i++)  
    {  
        highByte = source[i] >> 4;
        lowByte = source[i] & 0x0f ;
  
        highByte += 0x30;  
  
        if (highByte > 0x39)  
                dest[i * 2] = highByte + 0x07;  
        else  
                dest[i * 2] = highByte;  
  
        lowByte += 0x30;  
        if (lowByte > 0x39)  
            dest[i * 2 + 1] = lowByte + 0x07;  
        else  
            dest[i * 2 + 1] = lowByte;  
    }
    return dest;  
}


void flash_write(uint32_t *data){

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = FLASH_DATA_ADDR;
    f.NbPages = 1;
    uint32_t PageError = 0;
    HAL_FLASHEx_Erase(&f, &PageError);

    uint32_t addr = FLASH_DATA_ADDR;
    for(uint8_t i = 0 ; i < FLASH_DATA_LEN ; i++){
        
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *data++);
        addr += 4;
    }
    HAL_FLASH_Lock();
}

void flash_write_word(uint8_t address, uint32_t data){

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef f;
    f.TypeErase = FLASH_TYPEERASE_PAGES;
    f.PageAddress = FLASH_DATA_ADDR;
    f.NbPages = 1;
    uint32_t PageError = 0;
    HAL_FLASHEx_Erase(&f, &PageError);

    uint32_t addr = FLASH_DATA_ADDR;

    flash_pages_data[address] = data;

    for(uint8_t i = 0 ; i < FLASH_DATA_LEN ; i++){
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, flash_pages_data[i]);
        addr += 4;
    }
    HAL_FLASH_Lock();
}

uint32_t flash_read(uint32_t addr){
    return *(uint32_t*)(FLASH_DATA_ADDR+(addr*4));
}

void processing_server_command(){
//    0  2  4  6        14       22 24 26 28 30 32 34 36 38 40 42 44 46
//    01 01 00 00000000 00000000 00 64 64 64 64 64 64 64 64 64 64 01 43482D524F2D3030303031232323232323232323
    /*!< A 设备开机 */
    uint8_t boot[3] = {0};              
    memmove(boot, &bc95_recv.server_cmd[0], (sizeof(device_status.boot) * 2));
    device_status.boot = atoi(boot);
    
    /*!< B 停机开关机 */
    uint8_t arrears_boot[3] = {0};
    memmove(arrears_boot, &bc95_recv.server_cmd[2], (sizeof(device_status.arrears_boot) * 2));
    device_status.arrears_boot = atoi(arrears_boot);

    /*!< C 冲洗开关 */
    uint8_t rinse[3] = {0};
    memmove(rinse, &bc95_recv.server_cmd[4], (sizeof(device_status.rinse) * 2));
    device_status.rinse = atoi(rinse);
    
    /*!< D 时间 */
    uint8_t time[9] = {0};
    memmove(time, &bc95_recv.server_cmd[6], (sizeof(device_status.time) * 2));
    device_status.time = atoi(time);
    
    /*!< F 流量 */
    uint8_t flow[9] = {0};
    memmove(flow, &bc95_recv.server_cmd[14], (sizeof(device_status.flow) * 2));
    device_status.flow = atoi(flow);
    
    /*!< g1-g10 滤芯 */
    for(uint8_t i = 0 ; i < 10 ; i++){
        uint8_t filter[3] = {0};
        memmove(filter, &bc95_recv.server_cmd[24 + (i * 2)], (sizeof(device_status.filter) * 2));
        device_status.filter[i] = atoi(filter);
    }
    
    /*!< H 注册是否成功*/
    uint8_t device_registe[3] = {0};
    memmove(device_registe, &bc95_recv.server_cmd[44], (sizeof(device_status.device_registe) * 2));
    device_status.device_registe = atoi(device_registe);

    /*!< I 二维码 */
    uint8_t qr_code[QR_CODE_LEN] = {0};
    memmove(qr_code, &bc95_recv.server_cmd[46], (sizeof(device_status.qr_code) * 2));

}