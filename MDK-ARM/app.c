#include "app.h"
#include "tim.h"

device_statusTypeDef device_status = {0};
device_errorTypeDef device_error = {0};

void init_device_from_flash(){
    printf("init device form falsh ...\r\n");
    uint8_t first_boot = flash_read(FIRST_BOOT_ADDR);
    if(first_boot == 1){                // judge the device is first boot
        printf("flash is init ...\r\n");
        /*!<  from flash get data then init device status */
        device_status.device_registe = flash_read(REGISTE_ADDR);
        device_status.boot           = flash_read(BOOT_ADDR);
        device_status.pure_tds       = flash_read(PURE_TDS_ADDR);
        device_status.raw_tds        = flash_read(RAW_TDS_ADDR);
        device_status.flow           = flash_read(FLOW_ADDR);
        device_status.time           = flash_read(TIME_ADDR);
        for(uint8_t i = 0 ; i < 10 ; i++ ){
            device_status.filter[i]  = flash_read(FILTER_ADDR+i);
        }

        return;
    }else{
        printf("device first boot init flash ...\r\n");
        memset(flash_pages_data, 0, sizeof(flash_pages_data));
        flash_pages_data[first_boot] = 1;
        flash_pages_data[RAW_TDS_ADDR] = 546;
        flash_pages_data[REGISTE_ADDR] = 0;
        for(uint8_t i = 0 ; i < 10 ; i++ ){
            flash_pages_data[FILTER_ADDR + i] = 100;
        }
        flash_write(flash_pages_data);
        init_device_from_flash();
    }
}

uint8_t registe_device(){
    if(device_status.device_registe == 1){
        printf("device is registed ...");
    }else{
        if(bc95_send_coap("+NNMI") == OK){
            bc95_read_coap(BC95_TIMEOUT);
            return OK;
        }else{
            printf("ERROR:registe error");
            return ERROR;
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim->Instance == htim2.Instance){
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}