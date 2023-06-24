//
// Created by paopa on 2023/5/24.
//

#ifndef __LED_SMG_H
#define __LED_SMG_H

#include "main.h"

void LED_SMG_Init(void);

void LED_Write_Date(uint8_t *buf, uint8_t start_bit, uint8_t len);

void LED_Handle(void);

#endif //__LED_SMG_H
