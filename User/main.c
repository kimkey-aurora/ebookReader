#include "SYSTEM/sys/sys.h"
#include "SYSTEM/delay/delay.h"
#include "SYSTEM/usart/usart.h"
#include "BSP/LED/led.h"
#include "BSP/KEY/key.h"
#include "Test/test_atk_md0700.h"
#include <stm32f1xx.h>

/**
 * @brief       ��ʾʵ����Ϣ
 * @param       ��
 * @retval      ��
 */
void show_mesg(void)
{
    /* �������ʵ����Ϣ */
    printf("\n");
    printf("********************************\r\n");
    printf("STM32\r\n");
    printf("ATK-MD0700\r\n");
    printf("ATOM@ALIENTEK\r\n");
    printf("********************************\r\n");
    printf("\r\n");
}

int main(void)
{
	unsigned char i = 0;
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                         /* ��ʼ��LED */
    key_init();                         /* ��ʼ������ */
    show_mesg();                        /* ��ʾʵ����Ϣ */
	test_atk_md0700();
	while(1) {
		printf("Running normally...\r\n");
		if (i%2 == 0) {
			LED0(0);
			LED1(1);
			++i;
		} else {
			LED0(1);
			LED1(0);
			i = 0;
		}
		delay_ms(1000);
	}
}
