/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

//#define LED_PIN_B GET_PIN(I, 8)
//#define LED_PIN_R GET_PIN(C, 15)

int main(void)
{
    rt_uint32_t count = 1;

//    rt_pin_mode(LED_PIN_B, PIN_MODE_OUTPUT);
//    rt_pin_mode(LED_PIN_R, PIN_MODE_OUTPUT);

    while(count++)
    {
        rt_thread_mdelay(500);
//        rt_pin_write(LED_PIN_B, PIN_HIGH);
//        rt_pin_write(LED_PIN_R, PIN_LOW);
//        rt_thread_mdelay(500);
//        rt_pin_write(LED_PIN_B, PIN_LOW);
//        rt_pin_write(LED_PIN_R, PIN_HIGH);
    }
    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
    /* Vector Table Relocation in Internal QSPI_FLASH */
    SCB->VTOR = QSPI_BASE;
    return 0;
}
INIT_BOARD_EXPORT(vtor_config);


