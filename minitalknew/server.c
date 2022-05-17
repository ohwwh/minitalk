#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct global_set {
	int length;
	int	ch;
	int pos;
	int	pid;
	int	flag;
}global_set;

global_set gset;

void	check_flag(int signum)
{
	gset.flag = 1;
}

void    get_length(int signum)
{
	static int n;

	long    bit = 0x80000000;

	if (gset.pos < 32)
	{
		if (signum == SIGUSR1) 
			gset.length = gset.length + (bit >> gset.pos);
		gset.pos ++;
		signal(SIGUSR1, get_length);
		signal(SIGUSR2, get_length);
		kill(gset.pid, SIGUSR1);
		printf("%d int ack called, pos is %d, length is %d\n", n ++, gset.pos, gset.length);
	}
}

void    get_char(int signum)
{
	int	bit = 0x80;
	static int	n;

	if (gset.pos < 8)
	{
		if (signum == SIGUSR1)
			gset.ch = gset.ch + (bit >> gset.pos);
		gset.pos ++;
		signal(SIGUSR1, get_char);
		signal(SIGUSR2, get_char);
		kill(gset.pid, SIGUSR1);
		printf("%d ack called, pos is %d\n", n ++, gset.pos);
	}
}

void	get_pid_old(int signum)
{
	long    bit = 0x80000000;
	if (signum == SIGUSR1)
		gset.pid = gset.pid + (bit >> gset.pos);
	gset.pos ++;
}

void	get_pid(int signum, siginfo_t *sip, void *ptr)
{
	gset.pid = sip->si_pid;
	//kill(SIGUSR1, gset.pid);
}

int main(void)
{
	char	*str;
	int		i;

	i = 0;
	gset.length = 0;
	gset.pos = 0;
	gset.pid = 0;
	gset.ch = 0;
	gset.flag = 0;
	int pid = getpid();
	printf("%d\n", pid);
	struct sigaction act, oact;
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &get_pid;
	sigaction(SIGUSR1, &act, &oact);
	pause();



	printf("%d\n", gset.pid);
	gset.pos = 0;
	signal(SIGUSR1, get_length);
	signal(SIGUSR2, get_length);
	kill(gset.pid, SIGUSR1);
	while (gset.pos < 32)
	{
	}
	printf("%d\n", gset.length);
	//str = (char *)malloc(sizeof(char) * gset.length);
	signal(SIGUSR1, get_char);
	signal(SIGUSR2, get_char);
	gset.ch = 0;
	gset.pos = 0;
	kill(gset.pid, SIGUSR1);
	while (gset.pos < 8)
	{
		printf("%d\n", gset.pos);
	}
	printf("%c\n", gset.ch);
	/*while (i < gset.length)
	{
		gset.ch = 0;
		gset.pos = 0;
		kill(gset.pid, SIGUSR1);
		while (gset.pos < 8)
		{
		}
		str[i] = gset.ch;
		printf("%c\n", str[i]);
		i ++;
	}
	str[i] = 0;
	printf("%s\n", str);
	free(str);*/
}