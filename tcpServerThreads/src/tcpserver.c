// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
// https://www.geeksforgeeks.org/multithreading-c-2/
#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <../include/tcp.h>
#define DEBUG_LEVEL 1
#define NO_CONNECTION -1
// struct sockaddr {
//    unsigned short   sa_family;
//    char             sa_data[14];
// };
// struct sockaddr_in {
//    short int            sin_family;
//    unsigned short int   sin_port;
//    struct in_addr       sin_addr;
//    unsigned char        sin_zero[8];
// };

// typedef struct error {
//     int error_binding_socket = 0;
// } errors;


int checkAvailableConnections(struct info * connectionInfo, struct Client * clients);
// int checkAvailableConnections(struct info * connectionInfo);
void printCurrentConnections(struct Client * clients);
void* acceptClientThread(void* data);

int main(void) {
    // @param sockfd − It is a socket descriptor returned by the socket function.
    // @param cliaddr − It is a pointer to struct sockaddr that contains client IP address and port.
    // @param connfd − 

    /*SOCKET*/
    int sockfd; 
    struct sockaddr_in servaddr;
    struct info information = {0};


    char menu[5];
    /*SOCKET END*/
    struct Client clients[MAXCONNECTIONS];
    pthread_t  thread_id; 
    signal(SIGINT, exit_signal); 
    // Initialize socket
    initSocket(&servaddr, &sockfd);
    // Init available connections, MAXCONNECTIONS
    initClient(&clients[0], sockfd);

    int currentConnections = 0;
    while(1) {
        // if (currentConnections < MAXCONNECTIONS) {
            // check if current client is created, 1/0 value
            if (clients[currentConnections].threadCreated == false) {
                // start creating connection
                clients[currentConnections].threadCreated = true;
                // create thread for client listening, waiting untill client is ready
                pthread_create(&thread_id, NULL, acceptClientThread, (void*)&clients[currentConnections]);
            }
            // if [currentConnections] acceptedClient have something in it otherwise it is 0
            if (clients[currentConnections].acceptedClient > 0){
                // if client is accepted it will be moved in own thread to listen client
                pthread_create(&thread_id, NULL, receiveDataThread, (void*)&clients[currentConnections]);
                // set flag for information table that there is connection for designated spot
                information.connectionTable[currentConnections]++;
                // ??? if some connection is lost, use that slot ????
                currentConnections = checkAvailableConnections(&information, &clients[0]);
            }
        // }
        // printCurrentConnections(&clients);
        // int test = printCurrentConnections(&clients);
        // if (test != 0) {
        //     printf("connections %d\n", test);
        // }
    //     // if (error.zeroBuffer == 1) {
    //     //     close(sockfd);
    //     //     pthread_exit(NULL);
    //     //     exit(1);
    //     // }
    }


    close(sockfd);
    pthread_exit(NULL);
}


// int a = pthread_create(&thread_id, NULL, acceptClientThread, (void*)&clients[0]);
// while (clients[0].acceptedClient < 0);

// // int asd = pthread_create(&thread_id, NULL, receiveDataThread, (void*)&clients[0]);


// // initClient(&clients[1], sockfd);
// int dda = pthread_create(&thread_id, NULL, acceptClientThread, (void*)&clients[1]);
// while (clients[1].acceptedClient < 0);
// int ddd = pthread_create(&thread_id, NULL, receiveDataThread, (void*)&clients[1]);


// check available connections [1, 0, 0, 0, 0] -> [1, 1, 1, 0, 0] -> [0, 1, 1, 0, 0] -> [1, 1, 1, 0, 0]
// so always fill cons
int checkAvailableConnections(struct info * connectionInfo, struct Client * clients) {
    int currentConnection;
    int ii;
    currentConnection = 0;
    ii = 0;
    
    while (ii < MAXCONNECTIONS) {
        printf("<<<<<<<<<<<<%d>>>>>>>>>>>\n", ii);
        if (((clients->acceptedClient)+ii) == NO_CONNECTION) {
            currentConnection = ii;
            ii = MAXCONNECTIONS;
        }
        ii++;
    }

    if (DEBUG_LEVEL == 5) {
        ii = 0;
        printf("DEBUG:\n");
        while (ii < MAXCONNECTIONS) {
            if (((clients->acceptedClient)+ii) != NO_CONNECTION) {
                printf(" 1 ");
            }
            else {
                printf(" 0 ");
            }
            ii++;
        }
        printf("DEBUG END:\n");
    }
    
    // int i = 0;
    // printf("CLIENTS: ");
    // for (int i = 0; i < MAXCONNECTIONS; i++) {
    //     printf("%d ", (clients->acceptedClient));
    //     clients++;
    // }
    // printf("\n-----------------\n");
    // while (connectionInfo->connectionTable[i] != -1) {
    //     i++;
    // }
    // for (int i = 0; i < MAXCONNECTIONS; i++) {
    //     printf("%d ", connectionInfo->connectionTable[i]);
    // }
    // printf("\n");
    printf("<<<%d>>>", currentConnection);
    int i = 0;
    while (connectionInfo->connectionTable[i] != 0) {
        i++;
    }
    return i;
}

void printCurrentConnections(struct Client * clients) {
    int connectionCount = 0;
    printf(RED"Current connections:[%d\n"RESET, connectionCount);
    for (int i = 0; i < MAXCONNECTIONS; i++) {
        if (clients->acceptedClient > 0) {
            printf("1 ");
        }
        else {
            printf("0 ");
        }
        clients++;
    }
    clients -= MAXCONNECTIONS;
    printf("]\n");
}

void* receiveDataThread(void* client) {
    struct Client * Client = (struct Client*)client;
    receiveData(Client);
    pthread_exit(NULL);
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn void initClient(Client * client) 
 * @brief 
 * @param 
 * @return 
*/
/*********************************************************************/
void initClient(struct Client * currentClient, int sockfd) {
    for (int i = 0; i < MAXCONNECTIONS; i++) {
        currentClient->sockfd = sockfd;
        currentClient->acceptedClient = -1;
        currentClient->error.zeroBuffer = false;
        currentClient->options.sendDataBack = true;
        currentClient->threadCreated = false;
        currentClient++;
    }
}
/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn void* acceptClientThread(void* data) 
 * @brief Thread to make new connections
 * @param 
 * @return 
*/
/*********************************************************************/
void* acceptClientThread(void* data) {
    static clientCounter = 0;
    struct Client * newClient = (struct Client*)data;
    int len = 0;

    clientCounter++;
    printf(RED"acceptClient Thread threads created: %d\n"RESET,clientCounter);

    /* int listen(int sockfd,int backlog);
    backlog − It is the number of allowed connections.
    */ 
    if ((listen(newClient->sockfd, MAXCONNECTIONS) != 0)) {
        printf(RED"Listening failed\n"RESET);
    }
    else {
        printf(GRN"Server listening..\n"RESET);
    }

    len = sizeof((struct sockaddr_in *)&newClient->client);
    // printf(RED"LEN:<%d>\n"RESET,len);
    // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    newClient->acceptedClient = accept(newClient->sockfd, (struct sockaddr*)&newClient->client, &len);
    // printf(RED"acceptedClient:<%d>\n"RESET, newClient->acceptedClient);

    if (newClient->acceptedClient < 0) {
        printf(RED"Accepting server failed\n"RESET);
    }
    else{
        printf(GRN"Server accepted the client\n"RESET);
    }
    pthread_exit(NULL);
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn s
 * @brief 
 * @param 
 * @return 
*/
/*********************************************************************/
void acceptMultipleConnections(){
    int i = 0;
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn sendData(int * sockfd, char (*data)[MAX])
 * @brief send data to target address 
 * @param char(*data)[MAX]
 * @return writes to target destination
 * @remark char (*data)[MAX] is this correct way to do
*/
/*********************************************************************/
void sendData(int * sockfd, char (*data)[MAX]) {
    write(*sockfd, *data, sizeof(*data));
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn acceptClient(struct sockaddr_in * client, int * sockfd, int * acceptClient)
 * @brief 
 * @param struct sockaddr_in* client
 * @param int* sockfd
 * @param int* acceptClient
 * @return writes to target destination
*/
/*********************************************************************/
void acceptClient(struct sockaddr_in * client, int * sockfd, int * acceptClient) {
    int len = 0;
    /* int listen(int sockfd,int backlog);
    backlog − It is the number of allowed connections.
    */ 
    if ((listen(*sockfd, MAXCONNECTIONS) != 0)) {
        printf("Listening failed\n");
    }
    else {
        printf("Server listening..\n");
    }

    len = sizeof(client);
    // printf(RED"LEN:<%d>\n"RESET,len);
    // int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
    *acceptClient = accept(*sockfd,(struct sockaddr*)client, &len);
    if (*acceptClient < 0) {
        printf("Accepting server failed\n");
    }
    else{
        printf("Server accepted the client\n");
    }
}


/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn initSocket(struct sockaddr_in * servAddr, int * sockfd)
 * @brief initialize socket
 * @param struct sockaddr_in * servAddr
 * @param int* sockfd
 * @return 
*/
/*********************************************************************/
void initSocket(struct sockaddr_in * servAddr, int * sockfd) {
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("ERROR opening socket\n");
    }
    else{
        printf("Socket created\n");
    }
    
    bzero(servAddr, sizeof(servAddr));
    
    servAddr->sin_family = AF_INET;
    servAddr->sin_addr.s_addr = INADDR_ANY;
    servAddr->sin_port = htons(PORT);
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    if (bind(*sockfd, (const struct sockaddr*)servAddr, sizeof(*servAddr)) < 0) {
        printf("error binding socket\n");
        exit(0);
    }
    else{
        printf("Socket binded\n");
    }
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
----------------------------------------------------------------------*/
/**
 * @fn receiveData(int * sockfd, struct tcpErrors * error, struct tcpOptions * options)
 * @brief Receive data from socket until error, set option to send data back to sender
 * @param int* sockfd
 * @param struct tcpErrors * error
 * @return 
*/
/*********************************************************************/
void receiveData(struct Client * currentClient) {
    char buff[MAX];
    int n;
    printf("Receiving data:\n");
    while (((strncmp("exit", buff, 4)) != 0) && (currentClient->error.zeroBuffer == false)){
        bzero(buff, MAX);
        // read the message from client and copy it in buffer 
        // int read(int fildes, const void *buf, int nbyte);
        read(currentClient->acceptedClient, buff, sizeof(buff));
        if(buff[0] == '\0') {
            // in case of connection lost etc..
            currentClient->error.zeroBuffer = true;
            printf(YEL"Got empty buffer, maybe lost connection\n"RESET);
            currentClient->acceptedClient = -1;
        }
        else{
            printf("From client : %s\n", buff);
            if (currentClient->options.sendDataBack == true) {
                sendData(&currentClient->acceptedClient, &buff);
            }
        }
    }
    printf("Communication ends..\n");
}



void func(int *sockfd) { 
    char buff[MAX]; 
    int n; 
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
  
        // read the message from client and copy it in buffer 
        read(*sockfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client: %s\t To client : \n", buff); 
        bzero(buff, MAX); 
        n = 0; 
        // copy server message in the buffer 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
  
        // and send that buffer to client 
        write(sockfd, buff, sizeof(buff)); 
  
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buff, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
    } 
}

void exit_signal(int sig) {
    printf("CTRL-C exit\n");
    exit(1);
}