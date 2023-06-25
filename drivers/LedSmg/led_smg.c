#include "led_smg.h"
#include <stdio.h>

uint8_t led_memory_data[8] = {0};
// [0] 关断 / [1] (0) / [2] (1)
//static uint8_t smg_num[18] = {0x00, 0xfc,0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe,
//                              0xf6};

static uint8_t smg_num[] = {
        // 数字及特殊字符
        0x00,
        0x02, // -
        0x01, // .
        0x00, // / (no)
        0xfc, // 0
        0x60, // 1
        0xda, // 2
        0xf2, // 3
        0x66, // 4
        0xb6, // 5
        0xbe, // 6
        0xe0, // 7
        0xfe, // 8
        0xf6, // 9
        0x0c, // :
        // 字母表
        0xee, // A
        0x00, // B (NO)
        0x9c, // C
        0xfc, // D
        0x9e, // E
        0xce, // F
        0x00, // G (NO)
        0x6e, // H
        0x0c, // I
        0x70, // J
        0x00, // K (NO)
        0x1c, // L
};

void delay_us(uint32_t us) {
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--);
}


/**
 * @brief 数码管驱动 IO 初始化
 */
void LED_SMG_Init(void) {
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE(); //开启 GPIOB 时钟
    __HAL_RCC_GPIOC_CLK_ENABLE(); //开启 GPIOC 时钟
    __HAL_RCC_AFIO_CLK_ENABLE(); //开启 AFIO 时钟
//    __HAL_AFIO_REMAP_SWJ_NOJTAG(); //关闭 jtag，使能 SWD，可以用 SWD 模式调

    //74HC595 DS-PB3 LCLK-PB4 SCK-PB5
    GPIO_Initure.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;//PB3~5
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP; //推挽输出
    GPIO_Initure.Pull = GPIO_PULLUP; //上拉
    GPIO_Initure.Speed = GPIO_SPEED_HIGH; //高速
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);

    //74HC138 A0-PC10 A1-PC11 A2-PC12
    GPIO_Initure.Pin = GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;//PC10~12
    HAL_GPIO_Init(GPIOC, &GPIO_Initure);

    // Init Pin
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}

/**
 * @brief 数码管位选
 * @param num 要显示的数码管编号 0-7(共 8 个数码管)
 */
static void _LED_Wei(uint8_t num) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, (GPIO_PinState) (num & 0x01));
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, (GPIO_PinState) ((num & 0x02) >> 1));
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, (GPIO_PinState) ((num & 0x04) >> 2));
}

/**
 * @brief 数码管驱动
 * @param duan 段数
 * @param wei 显示位
 */
static void _LED_Write_Data(uint8_t duan, uint8_t wei) {
    uint8_t i;
    for (i = 0; i < 8; i++)//先送段
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (GPIO_PinState) ((duan >> i) & 0x01));
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        delay_us(5);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    }
    _LED_Wei(wei);//后选中位
}

/**
 * @brief 数码管刷新显示
 */
static void _LED_Refresh(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    delay_us(5);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
}

static uint8_t LED_Assignment(uint8_t x) {
    if (x >= 45 && x <= 58) {
        return x - 44;
    } else if (x >= 65 && x <= 76) {
        return x - 50;
    } else {
        return 0;
    }

    return 0;
}

/**
 * @brief 写入缓存数据
 * @param buf 只接受字符串
 * @param start_bit
 * @param len
 * ## 测试数据
 * buf "123.-" (0x31,0x32,0x33,0x2e,0x2d | 49,50,51,46,45)
 */
void LED_Write_Date(uint8_t *buf, uint8_t start_bit, uint8_t len) {


    for (int i = 0; i < len; i++) {
        // printf("buf = %d \r\n", *buf);
//        判断数字

        led_memory_data[start_bit + i] = LED_Assignment(buf[i]);

    }

    // printf("led_memory_data[%d] = %d\r\n", start_bit + 0, led_memory_data[1]);
}

// 处理函数计数
uint8_t ledSmg_count = 0;

void LED_Handle(void) {
    _LED_Write_Data(smg_num[led_memory_data[ledSmg_count]], ledSmg_count);
    _LED_Refresh();

    delay_us(300);

    // 数码管消影
    _LED_Write_Data(0x00, ledSmg_count);
    _LED_Refresh();

    ledSmg_count++;

    if (ledSmg_count > 8) {
        ledSmg_count = 0;
    }
}