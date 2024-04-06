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
 * @file      driver_gp2y1051au0f.c
 * @brief     driver gp2y1051au0f source file
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

#include "driver_gp2y1051au0f.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "SHARP GP2Y1051AU0F"        /**< chip name */
#define MANUFACTURER_NAME         "SHARP"                     /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        4.8f                        /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.2f                        /**< chip max supply voltage */
#define MAX_CURRENT               20.0f                       /**< chip max current */
#define TEMPERATURE_MIN           -10.0f                      /**< chip min operating temperature */
#define TEMPERATURE_MAX           65.0f                       /**< chip max operating temperature */
#define DRIVER_VERSION            1000                        /**< driver version */

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
uint8_t gp2y1051au0f_init(gp2y1051au0f_handle_t *handle)
{
    if (handle == NULL)                                                     /* check handle */
    {
        return 2;                                                           /* return error */
    }
    if (handle->debug_print == NULL)                                        /* check debug_print */
    {
        return 3;                                                           /* return error */
    }
    if (handle->uart_init == NULL)                                          /* check uart_init */
    {
        handle->debug_print("gp2y1051au0f: uart_init is null.\n");          /* uart_init is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_deinit == NULL)                                        /* check uart_deinit */
    {
        handle->debug_print("gp2y1051au0f: uart_deinit is null.\n");        /* uart_deinit is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_read == NULL)                                          /* check uart_read */
    {
        handle->debug_print("gp2y1051au0f: uart_read is null.\n");          /* uart_read is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->uart_flush == NULL)                                         /* check uart_flush */
    {
        handle->debug_print("gp2y1051au0f: uart_flush is null.\n");         /* uart_flush is null */
        
        return 3;                                                           /* return error */
    }
    if (handle->delay_ms == NULL)                                           /* check delay_ms */
    {
        handle->debug_print("gp2y1051au0f: delay_ms is null.\n");           /* delay_ms is null */
        
        return 3;                                                           /* return error */
    }

    if (handle->uart_init() != 0)                                           /* uart init */
    {
        handle->debug_print("gp2y1051au0f: uart init failed.\n");           /* uart init failed */
        
        return 1;                                                           /* return error */
    }
    handle->inited = 1;                                                     /* flag finish initialization */
    
    return 0;                                                               /* success return 0 */
}

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
uint8_t gp2y1051au0f_deinit(gp2y1051au0f_handle_t *handle)
{
    if (handle == NULL)                                                    /* check handle */
    {
        return 2;                                                          /* return error */
    }
    if (handle->inited != 1)                                               /* check handle initialization */
    {
        return 3;                                                          /* return error */
    }
    
    if (handle->uart_deinit() != 0)                                        /* uart deinit */
    {
        handle->debug_print("gp2y1051au0f: uart deinit failed.\n");        /* uart deinit failed */
        
        return 1;                                                          /* return error */
    }         
    handle->inited = 0;                                                    /* flag close */
    
    return 0;                                                              /* success return 0 */ 
}

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
uint8_t gp2y1051au0f_read(gp2y1051au0f_handle_t *handle, uint16_t *raw, float *mg_m3)
{
    uint8_t res;
    uint8_t i;
    uint8_t offset;
    uint8_t done;
    uint16_t len;
    uint16_t check_sum;
    uint8_t buf[14];
    
    if (handle == NULL)                                                          /* check handle */
    {
        return 2;                                                                /* return error */
    }
    if (handle->inited != 1)                                                     /* check handle initialization */
    {
        return 3;                                                                /* return error */
    }
    
    res = handle->uart_flush();                                                  /* uart flush */
    if (res != 0)                                                                /* check result */
    {
        handle->debug_print("gp2y1051au0f: uart flush failed.\n");               /* uart flush failed */
        
        return 1;                                                                /* return error */
    }
    handle->delay_ms(180);                                                       /* delay 180ms */
    len = handle->uart_read((uint8_t *)buf, 14);                                 /* uart read */
    if (len != 14)                                                               /* check result */
    {
        handle->debug_print("gp2y1051au0f: uart read failed.\n");                /* uart read failed */
        
        return 1;                                                                /* return error */
    }
    offset = 0;                                                                  /* init 0 */
    done = 0;                                                                    /* init 0 */
    for (i = 0; i < 14; i++)                                                     /* loop all */
    {
        if ((buf[i] == 0xAA) && ((i + 7) < 14))                                  /* check frame */
        {
            if (buf[i + 6] != 0xFF)                                              /* check frame trail */
            {
                handle->debug_print("gp2y1051au0f: frame is invalid.\n");        /* frame is invalid */
                
                return 4;                                                        /* return error */
            }
            offset = i;                                                          /* sava index */
            done = 1;                                                            /* flag done */
            
            break;                                                               /* break */
        }
    }
    if (done != 1)                                                               /* check done */
    {
        handle->debug_print("gp2y1051au0f: frame is error.\n");                  /* frame is error */
        
        return 5;                                                                /* return error */
    }
    check_sum = 0;                                                               /* init 0 */
    for (i = 1; i < 5; i++)                                                      /* sum 4 bytes */
    {
        check_sum += buf[offset + i];                                            /* sum all */
    }
    if ((check_sum & 0xFF) != buf[offset + 5])                                   /* check sum */
    {
        handle->debug_print("gp2y1051au0f: frame check error.\n");               /* frame check error */
        
        return 6;                                                                /* return error */
    }
    *raw = ((uint16_t)buf[offset + 1]) << 8 | buf[offset + 2];                   /* get raw */
    *mg_m3 = (float)(*raw) / 3.5f;                                               /* convert to mg/m3 */
    
    return 0;                                                                    /* success return 0 */ 
}

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
uint8_t gp2y1051au0f_get_buf(gp2y1051au0f_handle_t *handle, char *buf, uint16_t len, uint32_t ms)
{
    uint8_t res;
    uint16_t l;

    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = handle->uart_flush();                                           /* uart flush */ 
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("gp2y1051au0f: uart flush failed.\n");        /* uart flush failed */
       
        return 1;                                                         /* return error */
    }
    handle->delay_ms(ms);                                                 /* delay */
    l = handle->uart_read((uint8_t *)buf, len);                           /* uart read */
    if (l != len)                                                         /* check result */
    {
        handle->debug_print("gp2y1051au0f: uart read failed.\n");         /* uart read failed */
       
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */ 
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a gp2y1051au0f info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t gp2y1051au0f_info(gp2y1051au0f_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(gp2y1051au0f_info_t));                   /* initialize gp2y1051au0f info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "UART", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
