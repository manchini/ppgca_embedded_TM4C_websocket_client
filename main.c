/* Standard variables definitions */
#include <stdint.h>
#include <stdbool.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/cfg/global.h> // to get static definitions from RTOS.cfg file

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Project Header files */
#include "project_includes/Board.h"
#include "project_includes/adc_sample.h"
#include "project_includes/eth_network.h"

/* CMSIS DSP math library */
#include <arm_math.h>

/* C standard libs */
#include <stdio.h>


/* Debug breakpoint value */
#define BREAK_POINT_VALUE   1   // Debug purpose only

/*
 *  ======== main ========
 */
int main(void)
{
    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    Board_initEMAC();

    System_printf("\nPeripheral initiated..." "\nStarting BIOS...\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/* initialize ADC/DMA data acquisition */
void initSamplesTask(void)
{
    DMA_init();
    ADC_init();
    TIMER_ADC_init(SAMPLE_FREQUENCY);
}

/* compute rms value  */
void signalProcessing_Task(void)
{

}

/* heart beat from RTOS*/
void heartBeat_Task(void)
{
    while (1)
    {
        GPIO_toggle(Board_LED0);    // blink LED
        Task_sleep(500);            // goto to sleep
    }
}
