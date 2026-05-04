/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-16     armink       first implementation
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <finsh.h>
#include <stdlib.h>

/* 软件按键事件 */
#define EVENT_KEY1          (1 << 0)
#define EVENT_KEY2          (1 << 1)
#define EVENT_KEY3          (1 << 2)
#define EVENT_KEY_ALL       (EVENT_KEY1 | EVENT_KEY2 | EVENT_KEY3)

/* LED 控制事件 */
#define LED_EVENT_ALL_OFF       (1 << 0)
#define LED_EVENT_ALL_ON        (1 << 1)
#define LED_EVENT_FLOW_IDLE     (1 << 2)
#define LED_EVENT_FLOW_FORWARD  (1 << 3)
#define LED_EVENT_FLOW_REVERSE  (1 << 4)
#define LED_EVENT_ALL       (LED_EVENT_ALL_OFF      | \
                             LED_EVENT_ALL_ON       | \
                             LED_EVENT_FLOW_IDLE    | \
                             LED_EVENT_FLOW_FORWARD | \
                             LED_EVENT_FLOW_REVERSE)

/* 工作模式 */
#define MODE_OFF            0
#define MODE_ALL_ON         1
#define MODE_FLOW           2

static rt_event_t key_event = RT_NULL;
static rt_event_t led_event = RT_NULL;

static int led_state[3] = {0, 0, 0};

static void led_print_state(void)
{
    rt_kprintf("LED state: LED1=%s, LED2=%s, LED3=%s\n",
               led_state[0] ? "ON" : "OFF",
               led_state[1] ? "ON" : "OFF",
               led_state[2] ? "ON" : "OFF");
}

static void led_set(int index, rt_bool_t on)
{
    if (index < 0 || index >= 3)
    {
        return;
    }

    led_state[index] = on ? 1 : 0;
}

static void led_all_on(void)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        led_set(i, RT_TRUE);
    }

    led_print_state();
}

static void led_all_off(void)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        led_set(i, RT_FALSE);
    }

    led_print_state();
}

static void led_show_one(int index)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        led_set(i, RT_FALSE);
    }

    led_set(index, RT_TRUE);

    led_print_state();
}

/*
 * msh 软件按键命令：
 *
 * msh />key 1
 * msh />key 2
 * msh />key 3
 */
static int key(int argc, char **argv)
{
    int value;

    if (argc != 2)
    {
        rt_kprintf("Usage: key <1|2|3>\n");
        rt_kprintf("Example:\n");
        rt_kprintf("  key 1\n");
        rt_kprintf("  key 2\n");
        rt_kprintf("  key 3\n");
        return -RT_ERROR;
    }

    if (key_event == RT_NULL)
    {
        rt_kprintf("key_event is not initialized.\n");
        return -RT_ERROR;
    }

    value = atoi(argv[1]);

    if (value == 1)
    {
        rt_event_send(key_event, EVENT_KEY1);
        rt_kprintf("simulate KEY1 pressed\n");
    }
    else if (value == 2)
    {
        rt_event_send(key_event, EVENT_KEY2);
        rt_kprintf("simulate KEY2 pressed\n");
    }
    else if (value == 3)
    {
        rt_event_send(key_event, EVENT_KEY3);
        rt_kprintf("simulate KEY3 pressed\n");
    }
    else
    {
        rt_kprintf("Invalid key value. Please input 1, 2 or 3.\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}
MSH_CMD_EXPORT(key, simulate key input);


int main(void)
{
	return 0;
}
