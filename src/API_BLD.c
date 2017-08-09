/*
 * API_BLD.c
 *
 *  Created on: Aug 8, 2017
 *      Author: root
 */

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "flash_conf.h"
typedef enum {FALSE, TRUE} boolean;

/* Application start address */
#define APPLICATION_ADDRESS        FLASH_USER_START_ADDR

typedef void (*pFunction)(void);

/**
**===========================================================================
**  Abstract: Bootloader
**===========================================================================
*/
int boot_main(void)
{

	__disable_irq();
	pFunction appEntry;
	uint32_t appStack;
	/* Get the application stack pointer (First entry in the application vector table) */
	appStack = (uint32_t) *((__IO uint32_t*)APPLICATION_ADDRESS);
	/* Get the application entry point (Second entry in the application vector table) */
	appEntry = (pFunction) *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);

	/* Reconfigure vector table offset register to match the application location */
	SCB->VTOR = APPLICATION_ADDRESS;

	/* Set the application stack pointer */
	__set_MSP(appStack);
	/* Start the application */
	appEntry();

	while(1);

}
