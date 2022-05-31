#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int num = 0;

void    handler(int signum, siginfo_t *sip, void *ptr)
{
    sleep(1);
    num ++;
    write(1, "processs!\n", 10);
}

int main(void)
{
    int pid = getpid();
    struct sigaction	act1;

    printf("%d\n", pid);

    //act1.sa_flags = SA_NODEFER;
    act1.sa_sigaction = &handler;
    sigaction(SIGUSR1, &act1, NULL);
    sigaction(SIGUSR2, &act1, NULL);
    while (1)
    {
        sleep(1);
        printf("%d\n", num);
    };
}