/**
 ****************************************************************************************************
 * @file        atk_md0700_touch.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0700ģ�鴥����������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef __ATK_MD0700_TOUCH_H
#define __ATK_MD0700_TOUCH_H

#include "./BSP/ATK_MD0700/atk_md0700.h"

#if (ATK_MD0700_USING_TOUCH != 0)

/* ���Ŷ��� */
#define ATK_MD0700_TOUCH_PEN_GPIO_PORT          GPIOF
#define ATK_MD0700_TOUCH_PEN_GPIO_PIN           GPIO_PIN_10
#define ATK_MD0700_TOUCH_PEN_GPIO_CLK_ENABLE()  do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)
#define ATK_MD0700_TOUCH_CS_GPIO_PORT           GPIOF
#define ATK_MD0700_TOUCH_CS_GPIO_PIN            GPIO_PIN_11
#define ATK_MD0700_TOUCH_CS_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOF_CLK_ENABLE(); }while(0)

/* IO���� */
#define ATK_MD0700_TOUCH_READ_PEN()             HAL_GPIO_ReadPin(ATK_MD0700_TOUCH_PEN_GPIO_PORT, ATK_MD0700_TOUCH_PEN_GPIO_PIN)
#define ATK_MD0700_TOUCH_PEN(x)                 do{ x ?                                                                                                 \
                                                    HAL_GPIO_WritePin(ATK_MD0700_TOUCH_PEN_GPIO_PORT, ATK_MD0700_TOUCH_PEN_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(ATK_MD0700_TOUCH_PEN_GPIO_PORT, ATK_MD0700_TOUCH_PEN_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)
#define ATK_MD0700_TOUCH_TCS(x)                 do{ x ?                                                                                                 \
                                                    HAL_GPIO_WritePin(ATK_MD0700_TOUCH_CS_GPIO_PORT, ATK_MD0700_TOUCH_CS_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(ATK_MD0700_TOUCH_CS_GPIO_PORT, ATK_MD0700_TOUCH_CS_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

/* �������������ݽṹ */
typedef struct
{
    uint16_t x;     /* ������X���� */
    uint16_t y;     /* ������Y���� */
} atk_md0700_touch_point_t;

/* ������� */
#define ATK_MD0700_TOUCH_EOK                    0   /* û�д��� */
#define ATK_MD0700_TOUCH_ERROR                  1   /* ���� */

/* �������� */
void atk_md0700_touch_init(void);                                               /* ATK-MD0700ģ�鴥����ʼ�� */
uint8_t atk_md0700_touch_scan(atk_md0700_touch_point_t *point, uint8_t cnt);    /* ATK-MD0700ģ�鴥��ɨ�� */

#endif /* ATK_MD0700_USING_TOUCH */

#endif
