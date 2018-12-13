/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_TIMER
#include "Timer.h"
#if PL_CONFIG_HAS_EVENTS
#include "Event.h"
#endif
#if PL_CONFIG_HAS_TRIGGER
#include "Trigger.h"
#endif
#if PL_CONFIG_HAS_MOTOR_TACHO
#include "Tacho.h"
#endif
#include "TMOUT1.h"
#include "TmDt1.h"

#include "FRTOS1.h"

#if PL_CONFIG_HAS_MOTOR_TACHO
// Software Timer Handler
xTimerHandle timerHndl_5mSec;
#endif


void TMR_OnInterrupt(void) {
static unsigned int cntr = 0;
/* this one gets called from an interrupt!!!! */
/*! \todo Add code for a blinking LED here */
cntr++;
if (cntr == (1000 / TMR_TICK_MS)) {
	EVNT_SetEvent(EVNT_LED_HEARTBEAT);
	cntr = 0;
}
}

#if PL_CONFIG_HAS_MOTOR_TACHO
static void vTimerCallback5mSecExpired(xTimerHandle pxTimer) {

	TACHO_Sample(); /* toggle red LED */

}
#endif

void TMR_Init(void) {
#if PL_CONFIG_HAS_MOTOR_TACHO
	//Create 5ms Timer for Tacho
	timerHndl_5mSec = xTimerCreate("timer5m_Sec", /* name */
	pdMS_TO_TICKS(5), /* period/time */
	pdTRUE, /* auto reload */
	(void*) 0, /* timer ID */
	vTimerCallback5mSecExpired); /* callback */
	if(timerHndl_5mSec == NULL){
		for(;;); //Error
	}

	if (xTimerStart(timerHndl_5mSec, 0)!=pdPASS) {
	  for(;;); /* failure!?! */
	}
#endif

}
void TMR_Deinit(void) {
}

#endif /* PL_CONFIG_HAS_TIMER*/
