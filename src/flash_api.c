/*
 * flash_api.c
 *
 *  Created on: Aug 7, 2017
 *      Author: root
 */
/**
  ******************************************************************************
  * @file    FLASH_Program/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
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
  ******************************************************************************
  */

#include "flash_conf.h"
#include "usbh_core.h"
#include "ff.h"
#include "CRC_32.h"
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t StartSector = 0, EndSector = 0, Address = 0, i = 0 ;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0 ;
extern  USB_OTG_CORE_HANDLE          USB_OTG_Core;
FIL file,file0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
uint32_t GetSector(uint32_t Address);

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
uint32_t Computed_CRC = 0;
uint32_t Computed_CRC0 = 0;
int Program_flash(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f4xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f4xx.c file
     */
	uint32_t read_data;
	uint16_t bytesReadWritten;
	uint32_t End_Address = FLASH_USER_START_ADDR;
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
//    CRC_ResetDR();
  if(HCD_IsDeviceConnected(&USB_OTG_Core))
  {
		  /* Unlock the Flash to enable the flash control register access *************/
		  FLASH_Unlock();

		  /* Erase the user Flash area
			(area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

		  /* Clear pending flags (if any) */
		  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
						  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
		  if(FR_OK == f_open(&file,"USB_HOST.bin",FA_READ))
		   {
			  End_Address += file.fsize;

		   }
		  else
		  {
			  return 1;
		  }
		  /* Get the number of the start and end sectors */
		  StartSector = GetSector(FLASH_USER_START_ADDR);
		  EndSector   = GetSector(End_Address);


		  for (i = StartSector; i <= EndSector; i += 8)
		  {
			/* Device voltage range supposed to be [2.7V to 3.6V], the operation will
			   be done by word */
			if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)
			{
			  /* Error occurred while sector erase.
				 User can add here some code to deal with this error  */
			  while(1)
			  {

			  }
			}
			else {/*Empty else*/}
		  }

		  /* Program the user Flash area word by word
			(area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

		  Address = FLASH_USER_START_ADDR;
		  while (!f_eof(&file))
		  {
			if(FR_OK == f_read(&file,&read_data,4,(void *)&bytesReadWritten))
			{

				if (FLASH_ProgramWord(Address,read_data) == FLASH_COMPLETE)
				{

				  Address = Address + 4;

				}
				else
				{
				  /* Error occurred while writing data in Flash memory.
					 User can add here some code to deal with this error */
				    return 4;
				}
			 }
			else
			{
			  /* Error occurred while reading data from DISK.
				 User can add here some code to deal with this error */
			    return 3 ;
			}
		  }

		  Computed_CRC0 = calcCrc32((uint32_t*)FLASH_USER_START_ADDR,file.fsize-4);
		  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, DISABLE);
		  if(Compare_CRC(&Computed_CRC0,&read_data))
		  {

		  }else
		  {
            while(1);
		  }
		     /* Lock the Flash to disable the flash control register access (recommended
			 to protect the FLASH memory against possible unwanted operation) *********/
		  f_close(&file);
		  FLASH_Lock();

  }
  return 0;
}

/**
  * @brief  Gets the sector of a given address
  * @param  None
  * @retval The sector of a given address
  */
uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;

  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;
  }

  return sector;
}
/**
  * @brief  Computes the CRC
  * @param  None
  */
uint32_t CRC_CalcBlockCRC(uint32_t pBuffer[], uint32_t BufferLength)
{
 uint32_t index = 0;

 for(index = 0; index < (BufferLength % 4 ) ? BufferLength/4+1 : BufferLength/4; index++)
 {
   CRC->DR = pBuffer[index];
 }
 return (CRC->DR);
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
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

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

