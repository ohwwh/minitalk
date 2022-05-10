#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

typedef struct global_set {
    int length;
    int pos;
}global_set;

global_set gset;

void    get_length(int signum)
{
        if (signum == SIGUSR1)
            gset.length += (1 << gset.pos);
        printf("%d\n", gset.length);
        gset.pos ++;
}

int main(void)
{
    gset.length = 0;
    gset.pos = 0;
    int pid = getpid();
    printf("%d\n", pid);
	signal(SIGUSR1, get_length);
    signal(SIGUSR2, get_length);
    pause();
    while (gset.pos < 32)
        pause();
	/*while (1)
	{
		if (send_char(pid, str[i]) == -1)
			return (printf("You can't send\n"));
		i ++;
	}
	send_char(pid, str[i]);*/
	printf("%d\n", gset.length);
}