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
 * @file      driver_gp2y1051au0f_basic.c
 * @brief     driver gp2y1051au0f basic source file
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

static gp2y1051au0f_handle_t gs_handle;        /**< gp2y1051au0f handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t gp2y1051au0f_basic_init(void)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_GP2Y1051AU0F_LINK_INIT(&gs_handle, gp2y1051au0f_handle_t);
    DRIVER_GP2Y1051AU0F_LINK_UART_INIT(&gs_handle, gp2y1051au0f_interface_uart_init);
    DRIVER_GP2Y1051AU0F_LINK_UART_DEINIT(&gs_handle, gp2y1051au0f_interface_uart_deinit);
    DRIVER_GP2Y1051AU0F_LINK_UART_READ(&gs_handle, gp2y1051au0f_interface_uart_read);
    DRIVER_GP2Y1051AU0F_LINK_UART_FLUSH(&gs_handle, gp2y1051au0f_interface_uart_flush);
    DRIVER_GP2Y1051AU0F_LINK_DELAY_MS(&gs_handle, gp2y1051au0f_interface_delay_ms);
    DRIVER_GP2Y1051AU0F_LINK_DEBUG_PRINT(&gs_handle, gp2y1051au0f_interface_debug_print);
    
    /* gp2y1051au0f init */
    res = gp2y1051au0f_init(&gs_handle);
    if (res != 0)
    {
        gp2y1051au0f_interface_debug_print("gp2y1051au0f: init failed.\n");
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *mg_m3 points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t gp2y1051au0f_basic_read(float *mg_m3)
{
    uint8_t res;
    uint16_t raw;

    /* read */
    res = gp2y1051au0f_read(&gs_handle, &raw, mg_m3);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t gp2y1051au0f_basic_deinit(void)
{
    /* deinit gp2y1051au0f */
    if (gp2y1051au0f_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}
