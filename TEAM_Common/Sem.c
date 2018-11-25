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

static TaskHandle_t taskHndl;

static void vSlaveTask(void *pvParameters) {
	/*! \todo Implement functionality */
	SemaphoreHandle_t sem = (xSemaphoreHandle) pvParameters;

	if (sem == NULL) {
		for (;;) {
			/* should not be NULL? */
		}
	}
	for (;;) {
		/*! \todo Implement functionality */
		if (xSemaphoreTake(sem, portMAX_DELAY) == pdPASS) { /* block on semaphore */
			LED3_Neg();
		}
	}
}

static void vMasterTask(void *pvParameters) {
	/*! \todo send semaphore from master task to slave task */
	SemaphoreHandle_t sem = NULL;

	(void) pvParameters; /* parameter not used */
	sem = xSemaphoreCreateBinary();
	if (sem == NULL) { /* semaphore creation failed */
		for (;;) {
		} /* error */
	}
	// For Tracking
	vQueueAddToRegistry(sem, "IPC_Sem");
	/* create slave task */
	if (xTaskCreate(vSlaveTask, "Slave", 400 / sizeof(StackType_t), sem,
			tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		for (;;) {
		} /* error */
	}
	for (;;) {
		(void) xSemaphoreGive(sem); /* give control to other task */
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void SEM_Deinit(void) {
	vTaskDelete(taskHndl);
}

/*! \brief Initializes module */
void SEM_Init(void) {
	if (xTaskCreate(vMasterTask, "Master", 400 / sizeof(StackType_t), NULL,
			tskIDLE_PRIORITY + 1, &taskHndl) != pdPASS) {
		for (;;) {
		} /* error */
	}
}

#endif /* PL_CONFIG_HAS_SEMAPHORE */
