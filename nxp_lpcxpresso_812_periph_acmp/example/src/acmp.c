/*
 * @brief Analog Comparator example.
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* ACMP Pin mux function - note that SystemInit() may already setup your
   pin muxing at system startup */
static void Init_ACMP_PinMux(void)
{
#if (defined(BOARD_NXP_XPRESSO_812) || defined(BOARD_LPC812MAX))
	/* Enable the clock to the Switch Matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);

#if defined(BOARD_LPC812MAX)
	/* Configure the SWM for ACMP_I2 as the input for the Analog Comparator */
	Chip_SWM_EnableFixedPin(SWM_FIXED_ACMP_I2);
#else
	/* Configure the SWM for ACMP_I1 as the input for the Analog Comparator */
	Chip_SWM_EnableFixedPin(SWM_FIXED_ACMP_I1);
#endif

	/* Configure the SWM for PIO15 as the output for the comparator */
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, 0, 15);
	Chip_SWM_MovablePinAssign(SWM_ACMP_O_O, 15);

	/* Disable the clock to the Switch Matrix to save power */
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

#else
	/* Configure your own ACMP pin muxing here if needed */
#warning" No ACMP pin muxing defined"
#endif
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Analog comparator interrupt handler sub-routine
 * @return	Nothing
 */
void CMP_IRQHandler(void)
{
	/* Clear the interrupt */
	Chip_ACMP_EdgeClear(LPC_CMP);
}

/**
 * @brief	Main program body
 * @return	Does not return
 */
int main(void)
{
	/* initialize the board */
	SystemCoreClockUpdate();
	Board_Init();

	/* initialize the ACMP */
	Chip_ACMP_Init(LPC_CMP);

	/* Setup board specific ACMP pin muxing */
	Init_ACMP_PinMux();

	/* Positive and negative references, both edges, no hysteresis */
	Chip_ACMP_SetupAMCPRefs(LPC_CMP, ACMP_EDGESEL_BOTH, ACMP_POSIN_ACMP_I1, ACMP_NEGIN_INT_REF, ACMP_HYS_NONE);

	/* Enable the Interrupt for the compare output */
	NVIC_EnableIRQ(CMP_IRQn);

	while (1) {
		/* Enter low power mode until interrupt */
		__WFI();

		if (Chip_ACMP_GetCompStatus(LPC_CMP) & ACMP_COMPSTAT_BIT) {
			Board_LED_Set(0, false);
		}
		else {
			Board_LED_Set(0, true);
		}
	}

	return 0;
}
