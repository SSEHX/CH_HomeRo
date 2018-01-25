#include "app.h"
#include "tim.h"

device_statusTypeDef device_status = {0};
device_errorTypeDef device_error = {0};

uint8_t get_low_switch(){
    return HAL_GPIO_ReadPin(LOW_SWITCH_PORT, LOW_SWITCH_PIN);
}

uint8_t get_high_switch(){
    return HAL_GPIO_ReadPin(HIGH_SWITCH_PORT, HIGH_SWITCH_PIN);
}

/*----------------------------------------------------------------
 | Function    :    init_device_from_flash
 | Description :    first judge the device is first boot ,if yes
                    then set the default value to flash then run
                    self function to set the device_status typedef
                    from flash
 | Input       :    null
 | Output      :    null
 | Return      :    null
----------------------------------------------------------------*/
void init_device_from_flash(){
    #ifdef DEBUG
    printf("init device form falsh ...\r\n");
    #endif
    uint8_t first_boot = flash_read(FIRST_BOOT_ADDR);
    if(first_boot == 1){                // judge the device is first boot
        #ifdef DEBUG
        printf("flash is init ...\r\n");
        #endif
        /*!<  from flash get data then init device status */
        device_status.device_registe = flash_read(REGISTE_ADDR);
        device_status.boot           = flash_read(BOOT_ADDR);
        device_status.flow           = flash_read(FLOW_ADDR);
        device_status.time           = flash_read(TIME_ADDR);
        device_status.rinse_time     = flash_read(RINSE_TIME);
        device_status.device_mode    = flash_read(DEVICE_MODE_ADDR);
        device_status.arrears_boot   = flash_read(ARREARS_BOOT_ADDR);
        for(uint8_t i = 0 ; i < 10 ; i++ ){
           
            device_status.filter[i]  = flash_read(FILTER_ADDR+i);
        }
        for(uint8_t i = 0 ; i < QR_CODE_LEN ; i++){
            device_status.qr_code[i] = flash_read(QR_CODE_ADDR + i);
        }
        return;
    }else{
        #ifdef DEBUG
        printf("device first boot init flash ...\r\n");
        #endif
        memset(flash_pages_data, 0, sizeof(flash_pages_data));
        flash_pages_data[FIRST_BOOT_ADDR]    =    1;
        flash_pages_data[REGISTE_ADDR]       =    0;
        flash_pages_data[RINSE_TIME]         =    6;
        flash_pages_data[DEVICE_MODE_ADDR]   =    1;
        for(uint8_t i = 0 ; i < 10 ; i++ ){
            flash_pages_data[FILTER_ADDR + i] = 100;
        }

        flash_write(flash_pages_data);
        init_device_from_flash();
    }
}

/*----------------------------------------------------------------
 | Function    :    registe_device
 | Description :    if not registe device than send to server request 
                    registe if registed than send to server data
 | Input       :    null
 | Output      :    null
 | Return      :    null
----------------------------------------------------------------*/
uint8_t registe_device(){
    if(device_status.device_registe == 1){
        #ifdef DEBUG
        printf("device is registed ...");
        #endif
        bc95_send_coap("+NSMI:SENT");
    }else{
        if(bc95_send_coap("+NNMI") == OK){
            bc95_read_coap(BC95_TIMEOUT);
            return OK;
        }else{
            #ifdef DEBUG
            printf("ERROR:registe error");
            #endif
            return ERROR;
        }
    }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//    if (htim->Instance == htim2.Instance){
//
//    }
    
    if (htim->Instance == htim2.Instance){
        _system_led;
        if(get_low_switch()){
            device_error.raw_no_water = 1;
            if(!device_status.rinse_lock){
                stop_rinse;
            }
        }else{
            device_error.raw_no_water = 0;
            if(!get_high_switch()){
                start_create_water;
            }else{
                if(!device_status.rinse_lock){              // if not rinseing than stop create water ,if rinseing do nothing
                    stop_create_water;
                }
            }
        }

        if(device_status.rinse == 1){
            device_status.rinse_lock = 1;
            start_rinse;
            device_status.rinse = 0;
        }
    }
    

    // create water timer
    if(htim->Instance == htim4.Instance){
        device_status.create_water_time_s++;

        if(device_status.create_water_time_s == 60){
            device_status.create_water_time_m++;
        }

        if(device_status.rinse_lock == 1){
            device_status.rinse_time_count++;
            if(device_status.rinse_time_count > device_status.rinse_time){
                device_status.rinse_lock = 0;
                shut_rinse;
                device_status.rinse_time_count = 0;
            }
        }
    }

    if(htim->Instance == htim3.Instance){
        
    }
}

