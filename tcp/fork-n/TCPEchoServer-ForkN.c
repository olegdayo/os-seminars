#include "TCPEchoServer.h"

void ProcessMain(int servSock);         /* Main program of process */

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server*/
    unsigned short echoServPort;     /* Server port */
    pid_t processID;                 /* Process ID */
    unsigned int processLimit;       /* Number of child processes to create */
    unsigned int processCt;          /* Process counter */

    if (argc != 3)     /* Test for correct number of arguments */
    {
        fprintf(stderr,"Usage:  %s <SERVER PORT> <FORK LIMIT>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* First arg: local port */
    processLimit = atoi(argv[2]);  /* Second arg:  number of child processes */

    servSock = CreateTCPServerSocket(echoServPort);

    for (processCt=0; processCt < processLimit; processCt++)
        /* Fork child process and report any errors */
        if ((processID = fork()) < 0)
            DieWithError("fork() failed");
        else if (processID == 0)  /* If this is the child process */
            ProcessMain(servSock);

    exit(0);  /* The children will carry on */
}

void ProcessMain(int servSock)
{
    int clntSock;                  /* Socket descriptor for client connection */

    for (;;)  /* Run forever */
    {
        clntSock = AcceptTCPConnection(servSock);
        printf("with child process: %d\n", (unsigned int) getpid());
        HandleTCPClient(clntSock);
    }
}
