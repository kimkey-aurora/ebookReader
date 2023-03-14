/**
 ****************************************************************************************************
 * @file        atk_md0700_touch.c
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

#include "./BSP/ATK_MD0700/atk_md0700_touch.h"
#include "./BSP/ATK_MD0700/atk_md0700_touch_iic.h"
#include "./SYSTEM/delay/delay.h"
#include <string.h>
#include "./SYSTEM/usart/usart.h"

#if (ATK_MD0700_USING_TOUCH != 0)

/* ATK-MD0700ģ�鴥�����ּĴ������� */
#define ATK_MD0700_TOUCH_REG_DEVIDE_MODE        0x00    /* �豸ģʽ���ƼĴ��� */
#define ATK_MD0700_TOUCH_REG_ID_G_MODE          0xA4    /* �ж�ģʽ���ƼĴ��� */
#define ATK_MD0700_TOUCH_REG_ID_G_THGROUP       0x80    /* ��Ч������ֵ���üĴ��� */
#define ATK_MD0700_TOUCH_REG_ID_G_PERIODACTIVE  0x88    /* �����������üĴ��� */
#define ATK_MD0700_TOUCH_REG_TD_STATUS          0x02    /* ����״̬�Ĵ��� */
#define ATK_MD0700_TOUCH_REG_TP1                0x03    /* ������1���ݼĴ��� */
#define ATK_MD0700_TOUCH_REG_TP2                0x09    /* ������2���ݼĴ��� */
#define ATK_MD0700_TOUCH_REG_TP3                0x0F    /* ������3���ݼĴ��� */
#define ATK_MD0700_TOUCH_REG_TP4                0x15    /* ������4���ݼĴ��� */
#define ATK_MD0700_TOUCH_REG_TP5                0x1B    /* ������5���ݼĴ��� */

/* ����״̬�Ĵ������� */
#define ATK_MD0700_TOUCH_TD_STATUS_MASK_CNT     0x0F

/* ATK-MD0700ģ�鴥�������ݼĴ��� */
static const uint16_t g_atk_md0700_touch_tp_reg[ATK_MD0700_TOUCH_TP_MAX] = {
    ATK_MD0700_TOUCH_REG_TP1,
    ATK_MD0700_TOUCH_REG_TP2,
    ATK_MD0700_TOUCH_REG_TP3,
    ATK_MD0700_TOUCH_REG_TP4,
    ATK_MD0700_TOUCH_REG_TP5,
};

/**
 * @brief       ATK-MD0700ģ�鴥��Ӳ����ʼ��
 * @param       ��
 * @retval      ��
 */
static void atk_md0700_touch_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��ʱ�� */
    ATK_MD0700_TOUCH_PEN_GPIO_CLK_ENABLE();
    ATK_MD0700_TOUCH_CS_GPIO_CLK_ENABLE();
    
    /* ��ʼ��PEN���� */
    gpio_init_struct.Pin    = ATK_MD0700_TOUCH_PEN_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0700_TOUCH_PEN_GPIO_PORT, &gpio_init_struct);
    
    /* ��ʼ��TCS���� */
    gpio_init_struct.Pin    = ATK_MD0700_TOUCH_CS_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0700_TOUCH_CS_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ATK-MD0700ģ�鴥��Ӳ����λ
 * @param       ��
 * @retval      ��
 */
static void atk_md0700_touch_hw_reset(void)
{
    ATK_MD0700_TOUCH_TCS(0);
    delay_ms(20);
    ATK_MD0700_TOUCH_TCS(1);
    delay_ms(50);
}

/**
 * @brief       ATK-MD0700ģ�鴥���Ĵ�����ʼ��
 * @param       ��
 * @retval      ��
 */
static void atk_md0700_touch_reg_init(void)
{
    uint8_t dat;
    
    /* �豸ģʽ���ƼĴ��� */
    dat = 0x00;
    atk_md0700_touch_iic_write_reg(ATK_MD0700_TOUCH_REG_DEVIDE_MODE, &dat, sizeof(dat));
    
    /* �ж�ģʽ���ƼĴ��� */
    dat = 0x00;
    atk_md0700_touch_iic_write_reg(ATK_MD0700_TOUCH_REG_ID_G_MODE, &dat, sizeof(dat));
    
    /* ��Ч������ֵ���üĴ��� */
    dat = 22;
    atk_md0700_touch_iic_write_reg(ATK_MD0700_TOUCH_REG_ID_G_THGROUP, &dat, sizeof(dat));
    
    /* �����������üĴ���������С��12 */
    dat = 12;
    atk_md0700_touch_iic_write_reg(ATK_MD0700_TOUCH_REG_ID_G_PERIODACTIVE, &dat, sizeof(dat));
}

/**
 * @brief       ATK-MD0700ģ�鴥����ʼ��
 * @param       ��
 * @retval      ��
 */
void atk_md0700_touch_init(void)
{
    atk_md0700_touch_hw_init();
    atk_md0700_touch_hw_reset();
    atk_md0700_touch_iic_init();
    atk_md0700_touch_reg_init();
}

/**
 * @brief       ATK-MD0700ģ�鴥��ɨ��
 * @note        �������ü�������4ms
 * @param       point: ɨ�赽�Ĵ�������Ϣ
 *              cnt  : ��Ҫɨ��Ĵ�����������1~ATK_MD0700_TOUCH_TP_MAX��
 * @retval      0   : û��ɨ�赽������
 *              ����: ʵ�ʻ�ȡ���Ĵ�������Ϣ����
 */
uint8_t atk_md0700_touch_scan(atk_md0700_touch_point_t *point, uint8_t cnt)
{
    uint8_t tp_stat;
    uint8_t tp_cnt;
    uint8_t point_index;
    atk_md0700_lcd_disp_dir_t dir;
    uint8_t tpn_info[4];
    atk_md0700_touch_point_t point_raw;
    
    if ((cnt == 0) || (cnt > ATK_MD0700_TOUCH_TP_MAX))
    {
        return 0;
    }
    
    for (point_index=0; point_index<cnt; point_index++)
    {
        if (&point[point_index] == NULL)
        {
            return 0;
        }
    }
    
    atk_md0700_touch_iic_read_reg(ATK_MD0700_TOUCH_REG_TD_STATUS, &tp_stat, sizeof(tp_stat));
    tp_cnt = tp_stat & ATK_MD0700_TOUCH_TD_STATUS_MASK_CNT;
    if ((tp_cnt != 0) && (tp_cnt <= ATK_MD0700_TOUCH_TP_MAX))
    {
        tp_cnt = (cnt < tp_cnt) ? cnt : tp_cnt;
        
        for (point_index=0; point_index<tp_cnt; point_index++)
        {
            atk_md0700_touch_iic_read_reg(g_atk_md0700_touch_tp_reg[point_index], tpn_info, sizeof(tpn_info));
            point_raw.x = (uint16_t)((tpn_info[0] & 0x0F) << 8) | tpn_info[1];
            point_raw.y = (uint16_t)((tpn_info[2] & 0x0F) << 8) | tpn_info[3];
            
            dir = atk_md0700_get_disp_dir();
            switch (dir)
            {
                case ATK_MD0700_LCD_DISP_DIR_0:
                {
                    point[point_index].x = atk_md0700_get_lcd_width() - point_raw.x;
                    point[point_index].y = point_raw.y;
                    break;
                }
                case ATK_MD0700_LCD_DISP_DIR_90:
                {
                    point[point_index].x = point_raw.y;
                    point[point_index].y = point_raw.x;
                    break;
                }
                case ATK_MD0700_LCD_DISP_DIR_180:
                {
                    point[point_index].x = point_raw.x;
                    point[point_index].y = atk_md0700_get_lcd_height() - point_raw.y;
                    break;
                }
                case ATK_MD0700_LCD_DISP_DIR_270:
                {
                    point[point_index].x = atk_md0700_get_lcd_width() - point_raw.y;
                    point[point_index].y = atk_md0700_get_lcd_height() - point_raw.x;
                    break;
                }
            }
        }
        
        return tp_cnt;
    }
    else
    {
        return 0;
    }
}

#endif /* ATK_MD0700_USING_TOUCH */
