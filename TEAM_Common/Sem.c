/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module using semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_CONFIG_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"

static xSemaphoreHandle sem = NULL;

static void vSlaveTask(void *pvParameters) {
	/*! \todo Implement functionality */
	for (;;) {
		if (xSemaphoreTake(sem, 0)) {
			LED1_Neg();
		}
	}
}

static void vMasterTask(void *pvParameters) {
	/*! \todo send semaphore from master task to slave task */
	for (;;) {
		xSemaphoreGive(sem);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

void SEM_Deinit(void) {
}

/*! \brief Initializes module */
void SEM_Init(void) {

	sem = xSemaphoreCreateBinary( );

	if (xTaskCreate(vSlaveTask, "slave", 500 / sizeof(StackType_t), NULL,
			tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		for (;;) {
		} //error case
	}

	if (xTaskCreate(vMasterTask, "master", 500 / sizeof(StackType_t), NULL,
			tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		for (;;) {
		} //error case
	}

}
#endif /* PL_CONFIG_HAS_SEMAPHORE */
