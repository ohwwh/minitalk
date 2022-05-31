#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pid = atoi(argv[1]);
    kill(pid, SIGUSR1);
    //usleep(100);
    kill(pid, SIGUSR1);
}