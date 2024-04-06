/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-04-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/04/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_gp2y1051au0f_basic.h"
#include "driver_gp2y1051au0f_read_test.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     gp2y1051au0f full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t gp2y1051au0f(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"times", required_argument, NULL, 1},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* times */
            case 1 :
            {
                /* set times */
                times = atoi(optarg);
                
                break;
            }
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (gp2y1051au0f_read_test(times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        res = gp2y1051au0f_basic_init();
        if (res != 0)
        {
            return 1;
        }
        
        for (i = 0; i < times; i++)
        {
            float mg_m3;
            
            /* delay 1000ms */
            gp2y1051au0f_interface_delay_ms(1000);
            
            /* read data */
            res = gp2y1051au0f_basic_read(&mg_m3);
            if (res != 0)
            {
                (void)gp2y1051au0f_basic_deinit();
                
                return 1;
            }
            
            /* output */
            gp2y1051au0f_interface_debug_print("gp2y1051au0f: %d/%d.\n", i + 1, times);
            gp2y1051au0f_interface_debug_print("gp2y1051au0f: dust density is %0.2fmg/m3.\n", mg_m3);
        }
        
        /* deinit */
        (void)gp2y1051au0f_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        gp2y1051au0f_interface_debug_print("Usage:\n");
        gp2y1051au0f_interface_debug_print("  gp2y1051au0f (-i | --information)\n");
        gp2y1051au0f_interface_debug_print("  gp2y1051au0f (-h | --help)\n");
        gp2y1051au0f_interface_debug_print("  gp2y1051au0f (-p | --port)\n");
        gp2y1051au0f_interface_debug_print("  gp2y1051au0f (-t read | --test=read) [--times=<num>]\n");
        gp2y1051au0f_interface_debug_print("  gp2y1051au0f (-e read | --example=read) [--times=<num>]\n");
        gp2y1051au0f_interface_debug_print("\n");
        gp2y1051au0f_interface_debug_print("Options:\n");
        gp2y1051au0f_interface_debug_print("  -e <read>, --example=<read>        Run the driver example.\n");
        gp2y1051au0f_interface_debug_print("  -h, --help                         Show the help.\n");
        gp2y1051au0f_interface_debug_print("  -i, --information                  Show the chip information.\n");
        gp2y1051au0f_interface_debug_print("  -p, --port                         Display the pins used by this device to connect the chip.\n");
        gp2y1051au0f_interface_debug_print("  -t <read>, --test=<read>           Run the driver test.\n");
        gp2y1051au0f_interface_debug_print("      --times=<num>                  Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        gp2y1051au0f_info_t info;
        
        /* print gp2y1051au0f info */
        gp2y1051au0f_info(&info);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: chip is %s.\n", info.chip_name);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: manufacturer is %s.\n", info.manufacturer_name);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: interface is %s.\n", info.interface);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: max current is %0.2fmA.\n", info.max_current_ma);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: max temperature is %0.1fC.\n", info.temperature_max);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: TX connected to GPIOA PIN3.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register gp2y1051au0f function */
    shell_init();
    shell_register("gp2y1051au0f", gp2y1051au0f);
    uart_print("gp2y1051au0f: welcome to libdriver gp2y1051au0f.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("gp2y1051au0f: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("gp2y1051au0f: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("gp2y1051au0f: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("gp2y1051au0f: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("gp2y1051au0f: param is invalid.\n");
            }
            else
            {
                uart_print("gp2y1051au0f: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
