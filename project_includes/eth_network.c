/*
 *    ======== eth_network.c ========
 *    Contains non-BSD sockets code (NDK Network Open Hook)
 */

#include "project_includes/webSocket.h"
#include "project_includes/eth_network.h"
#include <string.h>


/*
 *  ======== tcpHandler ========
 *
 */
void tcpHandler(UArg arg0, UArg arg1)
{

    Websocket("ws:/192.168.2.1:8080/ws");
    WebsocketHandshake();

    char  msg[200];
    //WebSocketReadTask(msg);
    while(1){
      WebSocketRead(msg);
      WebsocketSend(msg);
      Task_sleep(1000);
    }


}

/*
 *  ======== netOpenHook ========
 *  NDK network open hook used to initialize IPv6
 */
void netOpenHook()
{
    Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;

    /* Make sure Error_Block is initialized */
    Error_init(&eb);

    Task_Params_init(&taskParams);
    Error_init(&eb);

    taskParams.stackSize = 1024;
    taskParams.priority = 1;
    taskHandle = Task_create((Task_FuncPtr) tcpHandler, &taskParams, &eb);
    if (taskHandle == NULL)
    {
        System_printf("main: Failed to create tcpHandler Task\n");
    }

    System_flush();
}
