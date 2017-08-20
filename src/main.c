/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined MEDIA_USB_KEY
 USB_OTG_CORE_HANDLE          USB_OTG_Core;
 USBH_HOST                    USB_Host;
#endif

RCC_ClocksTypeDef RCC_Clocks;

/* Private functions ---------------------------------------------------------*/
static void Start_Application(void);
static void Start_Bootloader(void);
/**
  * @brief  Main program.
  * @param  None
  * @retval None
*/
int main(void)
{
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

   GPIO_InitTypeDef Struct_Init;
   Struct_Init.GPIO_Pin  = GPIO_Pin_1;
   Struct_Init.GPIO_Mode = GPIO_Mode_IN;
   Struct_Init.GPIO_Speed = GPIO_Speed_100MHz;
   Struct_Init.GPIO_OType = GPIO_OType_PP;
   Struct_Init.GPIO_PuPd = GPIO_PuPd_DOWN;
   GPIO_Init(GPIOB,&Struct_Init);
  /* Initialize LEDS */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  uint8_t test = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
  if(1 == test)
  {
	  Start_Bootloader();
  }
  else
  {
	  Start_Application();
  }
  while(1);

}
static void Start_Application(void)
{
	boot_main();
}
static void Start_Bootloader(void)
{
	  /* Init Host Library */
	  USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID, &USB_Host, &USBH_MSC_cb, &USR_Callbacks);
	  //Program_flash();
	  while (1)
	  {
	    /* Host Task handler */
	    USBH_Process(&USB_OTG_Core, &USB_Host);
	  }


}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
