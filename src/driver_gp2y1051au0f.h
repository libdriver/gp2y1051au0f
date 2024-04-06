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
 * @file      driver_gp2y1051au0f.h
 * @brief     driver gp2y1051au0f header file
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

#ifndef DRIVER_GP2Y1051AU0F_H
#define DRIVER_GP2Y1051AU0F_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup gp2y1051au0f_driver gp2y1051au0f driver function
 * @brief    gp2y1051au0f driver modules
 * @{
 */

/**
 * @addtogroup gp2y1051au0f_basic_driver
 * @{
 */

/**
 * @brief gp2y1051au0f handle structure definition
 */
typedef struct gp2y1051au0f_handle_s
{
    uint8_t (*uart_init)(void);                               /**< point to a uart_init function address */
    uint8_t (*uart_deinit)(void);                             /**< point to a uart_deinit function address */
    uint16_t (*uart_read)(uint8_t *buf, uint16_t len);        /**< point to a uart_read function address */
    uint8_t (*uart_flush)(void);                              /**< point to a uart_flush function address */
    void (*delay_ms)(uint32_t ms);                            /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);          /**< point to a debug_print function address */
    uint8_t inited;                                           /**< inited flag */
} gp2y1051au0f_handle_t;

/**
 * @brief gp2y1051au0f information structure definition
 */
typedef struct gp2y1051au0f_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} gp2y1051au0f_info_t;

/**
 * @}
 */

/**
 * @defgroup gp2y1051au0f_link_driver gp2y1051au0f link driver function
 * @brief    gp2y1051au0f link driver modules
 * @ingroup  gp2y1051au0f_driver
 * @{
 */

/**
 * @brief     initialize gp2y1051au0f_handle_t structure
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] STRUCTURE is gp2y1051au0f_handle_t
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link uart_init function
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] FUC points to a uart_init function address
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_UART_INIT(HANDLE, FUC)   (HANDLE)->uart_init = FUC

/**
 * @brief     link uart_deinit function
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] FUC points to a uart_deinit function address
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_UART_DEINIT(HANDLE, FUC) (HANDLE)->uart_deinit = FUC

/**
 * @brief     link uart_read function
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] FUC points to a uart_read function address
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_UART_READ(HANDLE, FUC)   (HANDLE)->uart_read = FUC

/**
 * @brief     link uart_flush function
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] FUC points to a uart_flush function address
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_UART_FLUSH(HANDLE, FUC)  (HANDLE)->uart_flush = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a gp2y1051au0f handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_GP2Y1051AU0F_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup gp2y1051au0f_basic_driver gp2y1051au0f basic driver function
 * @brief    gp2y1051au0f basic driver modules
 * @ingroup  gp2y1051au0f_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a gp2y1051au0f info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t gp2y1051au0f_info(gp2y1051au0f_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a gp2y1051au0f handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t gp2y1051au0f_init(gp2y1051au0f_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a gp2y1051au0f handle structure
 * @return    status code
 *            - 0 success
 *            - 1 uart deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t gp2y1051au0f_deinit(gp2y1051au0f_handle_t *handle);

/**
 * @brief      read the data
 * @param[in]  *handle points to a gp2y1051au0f handle structure
 * @param[out] *raw points to a raw buffer
 * @param[out] *mg_m3 points to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 frame is invalid
 *             - 5 frame is error
 *             - 6 frame check error
 * @note       none
 */
uint8_t gp2y1051au0f_read(gp2y1051au0f_handle_t *handle, uint16_t *raw, float *mg_m3);

/**
 * @}
 */

/**
 * @defgroup gp2y1051au0f_extern_driver gp2y1051au0f extern driver function
 * @brief    gp2y1051au0f extern driver modules
 * @ingroup  gp2y1051au0f_driver
 * @{
 */

/**
 * @brief      get buffer
 * @param[in]  *handle points to a gp2y1051au0f handle structure
 * @param[out] *buf points to a data buffer
 * @param[in]  len is the buffer length
 * @param[in]  ms is the delay time in ms
 * @return     status code
 *             - 0 success
 *             - 1 get buf failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t gp2y1051au0f_get_buf(gp2y1051au0f_handle_t *handle, char *buf, uint16_t len, uint32_t ms);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
