 /*
 * WebSocket.h
 *
 *  Created on: 19 de nov de 2017
 *      Author: fernandomanchini
 */


#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

 /* NDK Header files */
#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/_stack.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>

/* Project Header files */
#include "project_includes/Board.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

#include <string.h>





#define MAX_TRY_WRITE 20
#define MAX_TRY_READ 10


SOCKET lSocket;
char ip_domain[200];
char path[200];
int port;



void Websocket(char *url);
void WebsocketHandshake(void);
int WebsocketSend(char * str);
int WebSocketRead(char * message);

void fillFields(char *url);
int sendOpcode(uint8_t opcode, char * msg);
int sendMask(char * msg);
int sendLength(uint32_t len, char * msg);
int WebSocketReadChar(char * str, int len, int min_len);


int WebSocketReadWorker(char * message);
int WebSocketReadTask(char * message );
