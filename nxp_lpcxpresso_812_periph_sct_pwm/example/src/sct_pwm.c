/*
 * @brief State Configurable Timer (SCT) PWM example
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

/* Systick is used for general timing */
#define TICKRATE_HZ (33)	/* 33% rate of change per second */

/* PWM cycle time - time of a single PWM sweep */
#define PWMCYCLERATE (1000)

/* Saved tick count used for a PWM cycle */
static uint32_t cycleTicks;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Set SCT PWM 'high' period based on passed percentage */
void setPWMRate(int pwnNum, uint8_t percentage)
{
	uint32_t value;

	/* Limit valid PWMs to 3 */
	if ((pwnNum < 0) || (pwnNum > 3)) {
		return;
	}

	if (percentage >= 100) {
		value = 1;
	}
	else if (percentage == 0) {
		value = cycleTicks + 1;
	}
	else {
		uint32_t newTicks;

		newTicks = (cycleTicks * percentage) / 100;

		/* Approximate duty cycle rate */
		value = cycleTicks - newTicks;
	}

	LPC_SCT->MATCHREL[pwnNum + 1].U = value;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	/* This is only used to wakeup up the device from sleep */
}

/**
 * @brief	Handle interrupt from State Configurable Timer
 * @return	Nothing
 */
void SCT_IRQHandler(void)
{
	/* Clear the Interrupt */
	Chip_SCT_ClearEventFlag(LPC_SCT, SCT_EVT_0);
}

/**
 * @brief	Application main program
 * @return	Nothing (This function will not return)
 */
int main(void)
{
	uint8_t dutyCycle;
	int i, j, countdir = 1;

	/* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();

	/* Enable SysTick Timer */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ);

	/* Chip specific SCT setup - clocks and peripheral reset
	   There are a lot of registers in the SCT peripheral. Performing
	   the reset allows the default states of the SCT to be loaded, so
	   we don't need to set them all and rely on defaults when needed. */
	Chip_SCT_Init(LPC_SCT);

	/* Enable SWM clock before altering SWM */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
#if (defined(BOARD_NXP_XPRESSO_812) || defined(BOARD_LPC812MAX))
	/* Connect SCT output 0 to LED pin PIO7, SCT output 1 to PIO17 */
	Chip_SWM_MovablePinAssign(SWM_CTOUT_0_O, 7);
	Chip_SWM_MovablePinAssign(SWM_CTOUT_1_O, 17);
#else
	/* Configure your own SCT pin muxing here if needed */
#warning "No SCT pin muxing defined"
#endif
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

	/* Configure the SCT as a 32bit counter using the bus clock */
	LPC_SCT->CONFIG = SCT_CONFIG_32BIT_COUNTER | SCT_CONFIG_CLKMODE_BUSCLK;

	/* Initial CTOUT0 state is high */
	LPC_SCT->OUTPUT = (7 << 0);

	/* The PWM will use a cycle time of (PWMCYCLERATE)Hz based off the bus clock */
	cycleTicks = Chip_Clock_GetSystemClockRate() / PWMCYCLERATE;

	/* Setup for match mode */
	LPC_SCT->REGMODE_L = 0;

	/* Start at 50% duty cycle */
	dutyCycle = 50;

	/* Setup match counter 0 for the number of ticks in a PWM sweep, event 0
	    will be used with the match 0 count to reset the counter.  */
	LPC_SCT->MATCH[0].U = cycleTicks;
	LPC_SCT->MATCHREL[0].U = cycleTicks;
	LPC_SCT->EVENT[0].CTRL = 0x00001000;
	LPC_SCT->EVENT[0].STATE = 0xFFFFFFFF;
	LPC_SCT->LIMIT_L = (1 << 0);

	/* For CTOUT0 to CTOUT2, event 1 is used to clear the output */
	LPC_SCT->OUT[0].CLR = (1 << 0);
	LPC_SCT->OUT[1].CLR = (1 << 0);
	LPC_SCT->OUT[2].CLR = (1 << 0);

	/* Setup PWM0(CTOUT0), PWM1(CTOUT1), and PWM2(CTOUT2) to 50% dutycycle */
	setPWMRate(0, dutyCycle);	/* On match 1 */
	setPWMRate(1, dutyCycle);	/* On match 2 */
	setPWMRate(2, dutyCycle);	/* On match 3 */

	/* Setup event 1 to trigger on match 1 and set CTOUT0 high */
	LPC_SCT->EVENT[1].CTRL = (1 << 0) | (1 << 12);
	LPC_SCT->EVENT[1].STATE = 1;
	LPC_SCT->OUT[0].SET = (1 << 1);

	/* Setup event 2 trigger on match 2 and set CTOUT1 high */
	LPC_SCT->EVENT[2].CTRL = (2 << 0) | (1 << 12);
	LPC_SCT->EVENT[2].STATE = 1;
	LPC_SCT->OUT[1].SET = (1 << 2);

	/* Setup event 3 trigger on match 3 and set CTOUT2 high */
	LPC_SCT->EVENT[3].CTRL = (3 << 0) | (1 << 12);
	LPC_SCT->EVENT[3].STATE = 1;
	LPC_SCT->OUT[2].SET = (1 << 3);

	/* Don't use states */
	LPC_SCT->STATE_L = 0;

	/* Unhalt the counter to start */
	LPC_SCT->CTRL_U &= ~(1 << 2);

	/* Background loop alters duty cycle every sysTick */
	while (1) {
		/* WIll sleep until next SysTick */
		__WFI();

		/* Slowly ramp up duty cycle */
		dutyCycle += countdir;
		if ((dutyCycle  == 0) || (dutyCycle >= 100)) {
			countdir = -countdir;

			/* 10 short LED toggles between dim up and down states */
			for (i = 0; i < 10; i++) {
				dutyCycle = 100 - dutyCycle;
				setPWMRate(0, dutyCycle);
				setPWMRate(1, dutyCycle);
				setPWMRate(2, dutyCycle);

				for (j = 0; j < ( TICKRATE_HZ / 5); j++) {
					/* WIll sleep until next SysTick */
					__WFI();
				}
			}
		}

		/* Update duty cycle in SCT/PWM by change match 1 reload time */
		setPWMRate(0, dutyCycle);
		setPWMRate(1, dutyCycle);
		setPWMRate(2, dutyCycle);
	}

	return 0;
}
