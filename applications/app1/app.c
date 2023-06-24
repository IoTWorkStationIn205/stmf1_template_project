#include <stdio.h>
#include "app.h"
#include "main.h"
#include "usart.h"

#include "led_smg.h"

/**
 * @brief 应用函数
 */
void app(void) {
    LED_SMG_Init();
    LED_Write_Date((uint8_t *) "12", 0, 2);

     HAL_Delay(999);

    LED_Write_Date((uint8_t *) "12", 2, 2);
    while (1) {
        HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
        printf("Hello!\r\n");
        HAL_Delay(1000);
    }
}


int _write(int fd, char *ptr, int len) {
    HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, 0xFFFF);
    return len;
}