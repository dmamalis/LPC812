/*
 * @brief Multi-Rate Timer (MRT) example
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

static volatile bool t3Fired;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* Interrupt fire reference counters for t0/1, t2, and t3 */
uint32_t t01, t2, t3;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Setup a timer for a periodic (repeat mode) rate */
static void setupMRT(uint8_t ch, MRT_MODE_T mode, uint32_t rate)
{
	LPC_MRT_CH_T *pMRT;

	/* Get pointer to timer selected by ch */
	pMRT = Chip_MRT_GetRegPtr(ch);

	/* Setup timer with rate based on MRT clock */
	Chip_MRT_SetInterval(pMRT, (Chip_Clock_GetSystemClockRate() / rate) |
						 MRT_INTVAL_LOAD);

	/* Timer mode */
	Chip_MRT_SetMode(pMRT, mode);

	/* Clear pending interrupt and enable timer */
	Chip_MRT_IntClear(pMRT);
	Chip_MRT_SetEnabled(pMRT);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from MRT
 * @return	Nothing
 */
void MRT_IRQHandler(void)
{
	uint32_t int_pend;

	/* Get interrupt pending status for all timers */
	int_pend = Chip_MRT_GetIntPending();
	Chip_MRT_ClearIntPending(int_pend);

	/* Channel 0 and 1 are periodic, toggle on either interrupt */
	if (int_pend & (MRTn_INTFLAG(0) | MRTn_INTFLAG(1))) {
		Board_LED_Toggle(0);
		t01++;
	}

	/* Channel 2 is single shot, reset it here */
	if (int_pend & (MRTn_INTFLAG(2))) {
		setupMRT(2, MRT_MODE_ONESHOT, 500);	/* Will fire in (1/500) seconds */
		Board_LED_Toggle(1);
		t2++;
	}

	/* Channel 3 is single shot, set flag so background loop resets it */
	if (int_pend & (MRTn_INTFLAG(3))) {
		t3Fired = false;
		t3++;
	}
}

/**
 * @brief	MRT example main function
 * @return	Status (This function will not return)
 */
int main(void)
{
	int mrtch;
	static uint32_t mSecShot;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	DEBUGSTR("LPC8xx MRT Example \r\n");

	/* MRT Initialization and disable all timers */
	Chip_MRT_Init();
	for (mrtch = 0; mrtch < MRT_CHANNELS_NUM; mrtch++) {
		Chip_MRT_SetDisabled(Chip_MRT_GetRegPtr(mrtch));
	}

	/* Enable the interrupt for the MRT */
	NVIC_EnableIRQ(MRT_IRQn);

	/* Enable timers 0 and 1 in repeat mode with different rates */
	setupMRT(0, MRT_MODE_REPEAT, 5);/* 5Hz rate */
	setupMRT(1, MRT_MODE_REPEAT, 4);/* 4Hz rate */

	/* Enable timer 2 in single one mode with the interrupt restarting the
	   timer */
	setupMRT(2, MRT_MODE_ONESHOT, 500);	/* Will fire in (1/500) seconds */

	mSecShot = 100;
	Board_LED_Set(0, false);

	/* Timer 3 processing loop - places timer 3 into one shot mode whenever it
	   has been handled in the IRQ handler */
	while (1) {
		if (!t3Fired) {
			t3Fired = true;
			setupMRT(3, MRT_MODE_ONESHOT, mSecShot);/* Will fire in (1/mSecShot) seconds */
			Board_LED_Toggle(2);
			mSecShot += 10;
			if (mSecShot > 1000) {
				mSecShot = 100;
			}
		}

		__WFI();
	}

	return 0;
}
