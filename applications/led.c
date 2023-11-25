/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     16795       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#include "led.h"
#include <agile_led.h>

static rt_thread_t led_thread = RT_NULL;

struct agile_led *led_blue = RT_NULL;
struct agile_led *led_red = RT_NULL;

/* 邮箱控制块 */
struct rt_mailbox led_mail;
/* 用于放邮件的内存池 */
static char led_mail_pool[512];

/* 线程 1 的入口函数 */
static void led_thread_entry(void *parameter)
{
//    rt_ubase_t *str;
    Led_light_t test =
    {
            .led_switch = Blue,
            .light_mode = "200,200",
            .loop_cnt = 10
    };
    Led_light_t *str;
    *str = test;
    while (1)
    {
        if (rt_mb_recv(&led_mail, (rt_ubase_t *)&str, 0) == RT_EOK)
        {
            rt_kprintf("switch: %d, light_mode %s,loop_cnt: %d\n",str->led_switch,str->light_mode,str->loop_cnt);
            switch (str->led_switch)
            {
                case Blue:
                    agile_led_dynamic_change_light_mode(led_blue, str->light_mode, str->loop_cnt);
                    agile_led_start(led_blue);
                    break;
                case Red:
                    agile_led_dynamic_change_light_mode(led_red, str->light_mode, str->loop_cnt);
                    agile_led_start(led_red);
                    break;
                default:
                    break;
            }

        }

        agile_led_process();

        rt_thread_mdelay(5);
    }
}

/* 线程示例 */
int led_thread_init(void)
{
    rt_err_t result;

    agile_led_env_init();

    /* 初始化一个 mailbox */
    result = rt_mb_init(&led_mail,
                        "led_mail",                      /* 名称是 mbt */
                        &led_mail_pool[0],                /* 邮箱用到的内存池是 mb_pool */
                        sizeof(led_mail_pool) / 4,        /* 邮箱中的邮件数目，因为一封邮件占 4 字节 */
                        RT_IPC_FLAG_FIFO);          /* 采用 FIFO 方式进行线程等待 */
    if (result != RT_EOK)
    {
//        LOG_E("init Led Mail Fail!");
        return -1;
    }

    /* 创建线程 1，名称是 thread1，入口是 thread1_entry*/
    led_thread = rt_thread_create("led_thread",
                            led_thread_entry, RT_NULL,
                            2048,
                            20, 1);

    /* 如果获得线程控制块，启动这个线程 */
    if (led_thread != RT_NULL)
        rt_thread_startup(led_thread);

    const char * init_light_mode = "200,100";
    led_blue = agile_led_create(GET_PIN(I, 8), PIN_LOW, init_light_mode, 2);
    agile_led_start(led_blue);

    led_red = agile_led_create(GET_PIN(C, 15), PIN_LOW, init_light_mode, 2);
    agile_led_start(led_red);

    return 0;
}

INIT_APP_EXPORT(led_thread_init);
