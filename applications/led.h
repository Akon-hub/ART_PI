/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     16795       the first version
 */
#ifndef APPLICATIONS_LED_H_
#define APPLICATIONS_LED_H_

extern struct rt_mailbox led_mail;

enum Led_Switch
{
    Blue,
    Red
};
typedef enum Led_Switch Led_switch_e;

struct Led_light
{
    enum Led_Switch led_switch;
    char *light_mode;
    rt_int32_t loop_cnt;
};
typedef struct Led_light Led_light_t;





#endif /* APPLICATIONS_LED_H_ */
