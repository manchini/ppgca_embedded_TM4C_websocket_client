/*
 *    ======== eth_network.c ========
 *    Contains non-BSD sockets code (NDK Network Open Hook)
 */

#include "project_includes/eth_network.h"
#include <string.h>

char ip_domain[200];
char path[200];
int port;


/**
 * Divide campos da URL em
 * dominio
 * porta
 * path
 */
void fillFields(char *url)
{
    char *res = NULL;
    char *res1 = NULL;

    char buf[200];
    strcpy(buf, url);

    res = strtok(buf, ":");


    if (strcmp(res, "ws"))
    {
        System_printf(
                "\nFormat printfor: please use: ws://ip-or-domain[:port]/path \n");
    }
    else
    {
        //ip_domain and port
        res = strtok(NULL, "/");

        //path
        res1 = strtok(NULL, " ");
        if (res1 != NULL)
        {
            //path = res1;
            strncpy(path,res1,strlen(res1));
        }

        //ip_domain
        res = strtok(res, ":");

        //port
        res1 = strtok(NULL, " ");
        if (res1 != NULL)
        {
            port = atoi(res1);;
        }
        else
        {
            port = 80;
        }

        if (res != NULL)
        {
            strncpy(ip_domain,res,strlen(res));
        }
    }
    //System_printf("ip_domain [%s] \n",ip_domain);
    //System_printf("port = [%d] \n", port);
    //System_printf("path = [%s] \n", path);
}

//seta OpCode na Mensagem
int sendOpcode(uint8_t opcode, char * msg)
{
    msg[0] = 0x80 | (opcode & 0x0f);
    return 1;
}


//
int sendMask(char * msg)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        msg[i] = 0;
    }
    return 4;
}

//
int sendLength(uint32_t len, char * msg)
{
    int i;
    if (len < 126)
    {
        msg[0] = len | (1 << 7);
        return 1;
    }
    else if (len < 65535)
    {
        msg[0] = 126 | (1 << 7);
        msg[1] = (len >> 8) & 0xff;
        msg[2] = len & 0xff;
        return 3;
    }
    else
    {
        msg[0] = 127 | (1 << 7);
        for (i = 0; i < 8; i++)
        {
            msg[i + 1] = (len >> i * 8) & 0xff;
        }
        return 9;
    }
}

/**
 * Método que envia a mensagem no websocket
 */
int WebsocketSend(char * str)
{
    int res;
    char  msg[strlen(str) + 15];
    int idx = 0;
    idx = sendOpcode(0x01, msg);
    idx += sendLength(strlen(str),msg + idx);
    idx += sendMask(msg + idx);
    memcpy(msg+idx, str, strlen(str));

    //System_printf(" %s ",*msg);
    //System_flush();

    res = send(lSocket,  msg, idx + strlen(str), 0);

    return res;
}


int WebSocketReadAux(char * str, int len, int min_len) {
    int res = 0, idx = 0;
    int j = 0;
    for (j = 0; j < MAX_TRY_WRITE; j++) {
        res = recv(lSocket,str, len - idx,0);
        if (res == -1)
            continue;

        idx += res;

        if (idx == len || (min_len != -1 && idx > min_len))
            return idx;
    }

    return (idx == 0) ? -1 : idx;
}

int WebSocketReadChar(char * pC) {
    return WebSocketReadAux(pC, 1, 1);
}

/**
 * Metodo que recebe a mensagem de retorno do websocket
 */
int WebSocketRead(char * message) {
    int i = 0;
    uint32_t len_msg;
    char opcode = 0;
    char c;
    char mask[4] = {0, 0, 0, 0};
    bool is_masked = false;

    // read the opcode
    while (true) {
        if ( recv(lSocket,&opcode,1,0) != 1) {
            return false;
        }

        if (opcode == 0x81)
            break;
    }

    WebSocketReadChar(&c);
    len_msg = c & 0x7f;
    is_masked = c & 0x80;
    if (len_msg == 126) {
        WebSocketReadChar(&c);
        len_msg = c << 8;
        WebSocketReadChar(&c);
        len_msg += c;
    } else if (len_msg == 127) {
        len_msg = 0;
        for (i = 0; i < 8; i++) {
            WebSocketReadChar(&c);
            len_msg += (c << (7-i)*8);
        }
    }

    if (len_msg == 0) {
        return false;
    }

    if (is_masked) {
        for (i = 0; i < 4; i++)
            WebSocketReadChar(&c);
        mask[i] = c;
    }

    int nb = WebSocketReadAux(message, len_msg, len_msg);
    if (nb != len_msg)
        return false;

    for (i = 0; i < len_msg; i++) {
        message[i] = message[i] ^ mask[i % 4];
    }

    message[len_msg] = '\0';

    return true;
}


void Websocket(char *url)
{
    fillFields(url);
}

void WebsocketConnect()
{

    struct sockaddr_in sLocalAddr;
    struct  timeval timeout;


    lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (lSocket < 0)
    {
        System_printf("tcpHandler: socket failed\n");
        Task_exit();
       // return ;
    }

    memset((char *) &sLocalAddr, 0, sizeof(sLocalAddr));
    sLocalAddr.sin_family = AF_INET;
    sLocalAddr.sin_addr.s_addr = inet_addr(ip_domain);
    sLocalAddr.sin_port = htons(port);

    /* Configure our timeout to be 5 seconds */
    timeout.tv_sec  = 0;
    timeout.tv_usec = 1000000;
    setsockopt( lSocket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof( timeout ) );
    setsockopt( lSocket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof( timeout ) );

    while (connect(lSocket, (struct sockaddr *) &sLocalAddr, sizeof(sLocalAddr)) < 0)
    {
        Task_sleep(1000);
    }
    //System_printf("Conectou\n");

    char cmd[200];
    int ret;

    //System_printf("Host: %s\r\n", ip_domain);

    // sent http header to upgrade to the ws protocol
    sprintf(cmd, "GET /%s HTTP/1.1\r\n", path);
    send(lSocket, (char *) cmd, strlen(cmd), 0);
    Task_sleep(100);

    sprintf(cmd, "Host: %s \r\n", ip_domain);
    send(lSocket, (char *) cmd, strlen(cmd), 0);
    Task_sleep(100);

    sprintf(cmd, "Upgrade: WebSocket\r\n");
    send(lSocket, (char *) cmd, strlen(cmd), 0);
    Task_sleep(100);

    sprintf(cmd, "Connection: Upgrade\r\n");
    send(lSocket, (char *) cmd, strlen(cmd), 0);
    Task_sleep(100);

    //Deveria gerar a chave aleatoria
    sprintf(cmd, "Sec-WebSocket-Key: L159VM0TWUzyDxwJEIEzjw==\r\n");
    send(lSocket, (char *) cmd, strlen(cmd), 0);
    Task_sleep(100);

    sprintf(cmd, "Sec-WebSocket-Version: 13\r\n\r\n");
    ret = send(lSocket, (char *) cmd, strlen(cmd), 0);
    Task_sleep(100);


    if (ret != strlen(cmd)) {
        System_printf("Could not receive answer\r\n");
     }


    ret = recv(lSocket, cmd, 200, 0);
    if (ret < 0)
    {
        //close();
        System_printf("Could not receive answer\r\n");
    }

    cmd[199] = '\0';
    //System_printf("recv: %s\r\n", cmd);

    if (strstr(cmd, "DdLWT/1JcX+nQFHebYP+rqEx5xI=") == NULL)
    {
        System_printf("Wrong answer from server, got \"%s\" instead\r\n", cmd);
        do
        {
            ret = recv(lSocket, cmd, 200, 0);
            if (ret < 0)
            {
                System_printf("Could not receive answer\r\n");
            }
            cmd[ret] = '\0';
            printf("%s", cmd);
        }
        while (ret > 0);

        return false;
    }

}

/*
 *  ======== tcpHandler ========
 *  Creates new Task to handle
 */
void tcpHandler(UArg arg0, UArg arg1)
{

    Websocket("ws:/192.168.2.1:8080/ws");
    WebsocketConnect();
    WebsocketSend("hue");

    char * msg;
    WebSocketRead(*msg);
    System_printf(" voltou %s",msg);
    System_flush();

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
