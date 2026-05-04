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

static volatile int Key = 0;

/*
 * msh 命令：set_mode <value>
 * 例如：
 * msh />set_mode 0
 * msh />set_mode 1
 * msh />set_mode 2
 */
static int set_mode(int argc, char **argv)
{
    int value;

    if (argc != 2)
    {
        rt_kprintf("Usage: set_mode <value>\n");
        rt_kprintf("Example: set_mode 1\n");
        return -RT_ERROR;
    }

    value = atoi(argv[1]);

    Key = value;

    rt_kprintf("Key = %d\n", Key);

    return RT_EOK;
}
MSH_CMD_EXPORT(set_mode, set mode value);

/*
 * msh 命令：get_mode
 * 用来查看当前变量值
 */
static int get_mode(int argc, char **argv)
{
    rt_kprintf("Key = %d\n", Key);
    return RT_EOK;
}
MSH_CMD_EXPORT(get_mode, get mode value);


int main(void)
{
	return 0;
}
