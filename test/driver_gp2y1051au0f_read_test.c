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
 * @file      driver_gp2y1051au0f_read_test.c
 * @brief     driver gp2y1051au0f read test source file
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

#include "driver_gp2y1051au0f_read_test.h"

static gp2y1051au0f_handle_t gs_handle;        /**< gp2y1051au0f handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t gp2y1051au0f_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    gp2y1051au0f_info_t info;
    
    /* link interface function */
    DRIVER_GP2Y1051AU0F_LINK_INIT(&gs_handle, gp2y1051au0f_handle_t);
    DRIVER_GP2Y1051AU0F_LINK_UART_INIT(&gs_handle, gp2y1051au0f_interface_uart_init);
    DRIVER_GP2Y1051AU0F_LINK_UART_DEINIT(&gs_handle, gp2y1051au0f_interface_uart_deinit);
    DRIVER_GP2Y1051AU0F_LINK_UART_READ(&gs_handle, gp2y1051au0f_interface_uart_read);
    DRIVER_GP2Y1051AU0F_LINK_UART_FLUSH(&gs_handle, gp2y1051au0f_interface_uart_flush);
    DRIVER_GP2Y1051AU0F_LINK_DELAY_MS(&gs_handle, gp2y1051au0f_interface_delay_ms);
    DRIVER_GP2Y1051AU0F_LINK_DEBUG_PRINT(&gs_handle, gp2y1051au0f_interface_debug_print);
    
    /* get gp2y1051au0f information */
    res = gp2y1051au0f_info(&info);
    if (res != 0)
    {
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: chip is %s.\n", info.chip_name);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: manufacturer is %s.\n", info.manufacturer_name);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: interface is %s.\n", info.interface);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: max current is %0.2fmA.\n", info.max_current_ma);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: max temperature is %0.1fC.\n", info.temperature_max);
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* gp2y1051au0f init */
    res = gp2y1051au0f_init(&gs_handle);
    if (res != 0)
    {
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: init failed.\n");

        return 1;
    }
    
    /* start read test */
    gp2y1051au0f_interface_debug_print("gp2y1051au0f: start read test.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t raw;
        float mg_m3;
        
        /* delay 2000ms */
        gp2y1051au0f_interface_delay_ms(2000);
        
        /* read */
        res = gp2y1051au0f_read(&gs_handle, &raw, &mg_m3);
        if (res != 0)
        {
            gp2y1051au0f_interface_debug_print("gp2y1051au0f: read failed.\n");
            (void)gp2y1051au0f_deinit(&gs_handle);
            
            return 1;
        }
        
        /* output */
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: dust density is %0.2fmg/m3.\n", mg_m3);
    }
    
    /* finish read test */
    gp2y1051au0f_interface_debug_print("gp2y1051au0f: finish read test.\n");
    (void)gp2y1051au0f_deinit(&gs_handle);

    return 0;
}
