/*
 * CRC_32.c
 *
 *  Created on: Aug 16, 2017
 *      Author: root
 */
#include "CRC_32.h"
uint32_t calcCrc32(uint32_t* data, uint32_t len)
{
   uint32_t* pBuffer = (uint32_t*) data;
   uint32_t  BufferLength = len/4;
   uint32_t  index = 0;

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);

   CRC_ResetDR();

   for(index = 0; index < BufferLength; index++)
   {
	   CRC->DR = (uint32_t) ((pBuffer[index] & 0x000000FF) << 24) | \
		                    ((pBuffer[index] & 0x0000FF00) << 8 ) | \
	                        ((pBuffer[index] & 0x00FF0000) >> 8 ) | \
		                    ((pBuffer[index] & 0xFF000000) >> 24);
   }

   return CRC->DR;
}

uint8_t Compare_CRC(uint32_t* crc_computed,uint32_t* crc_file)
{
    uint8_t flag = 0;
    uint32_t crc_file_tmp = (uint32_t) ((*crc_file & 0x000000FF) << 24) | \
    								   ((*crc_file & 0x0000FF00) << 8 ) | \
                                       ((*crc_file & 0x00FF0000) >> 8 ) | \
                                       ((*crc_file & 0xFF000000) >> 24);
    if( *crc_computed != crc_file_tmp)
    {
    	 flag = 0;
    }
    else
    {
    	 flag = 1;
    }


    return flag;
}
