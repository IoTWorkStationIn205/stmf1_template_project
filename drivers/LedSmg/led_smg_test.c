//
// Created by paopa on 2023/6/25.
//
#include "led_smg.h"

void led_smg_num_test(void){
    LED_Write_Date((uint8_t *) "12", 0, 2);
    LED_Write_Date((uint8_t *) "-.", 2, 2);
    LED_Write_Date((uint8_t *) ":9", 4, 2);

    LED_Write_Date((uint8_t *) "AL", 6, 2);
}

