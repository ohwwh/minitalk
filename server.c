#include "minitalk.h"

typedef struct global_set {
	int length;
	int	ch;
	int pos;
	int	state;
	int	pid;
	int	flag;
	char	*str;
	//struct sigaction act1, oact1, act2, oact2;
}global_set;

global_set gset;

void    get_length(int signum)
{
	static int n;

	long    bit = 0x80000000;
	int	b = 0;
	if (gset.state < 32)
	{
		if (signum == SIGUSR1)
		{
			gset.length = gset.length + (bit >> gset.state);
			b = 1;
		}
			
		gset.state ++;
		signal(SIGUSR1, get_length);
		signal(SIGUSR2, get_length);
		kill(gset.pid, SIGUSR1);
		printf("%d int ack called, pos is %d, length is %d, bit is %d\n", n ++, gset.state, gset.length, b);
	}
}

void    get_char(int signum)
{
	int	bit = 0x80;
	static int	n;
	int	b = 0;

	if (gset.state < 8)
	{
		if (signum == SIGUSR1)
		{
			gset.ch = gset.ch + (bit >> gset.state);
			b = 1;
		}
		//printf("%d ack called, pos is %d, bit is %d\n", n ++, gset.state, b);
		gset.state ++;
		signal(SIGUSR1, get_char);
		signal(SIGUSR2, get_char);
		kill(gset.pid, SIGUSR1);
	}
}

void	get_whole(int signum, siginfo_t *sip, void *ptr)
{
	static int n;

	long    bit;
	int	b = 0;
	
	if (gset.pid != sip->si_pid)
		return ;
	//printf("%d = %d\n", gset.pid, sip->si_pid);
	if (gset.state < 32)
	{
		bit = 0x80000000;
		if (signum == SIGUSR1)
		{
			gset.length = gset.length + (bit >> gset.state);
			b = 1;
		}
			
		gset.state ++;
		kill(gset.pid, SIGUSR1);
		//printf("%d int ack called, pos is %d, length is %d, bit is %d\n", n ++, gset.state, gset.length, b);
	}
	else if (gset.state < 32 + 8 * (gset.length))
	{
		if (gset.state == 32)
			gset.str = (char *)malloc(sizeof(char) * gset.length);
		bit = 0x80;
		if (signum == SIGUSR1)
		{
			gset.ch = gset.ch + (bit >> gset.pos);
			b = 1;
		}	
		kill(gset.pid, SIGUSR1);
		gset.pos ++;
		//printf("%d char ack called, state is %d, bit is %d\n", n ++, gset.state, b);
		gset.state ++;
		if ((gset.state - 32) % 8 == 0 && gset.state != 32)
		{
			gset.str[((gset.state - 32) / 8) - 1] = gset.ch;
			//printf("%c\n", gset.str[(gset.state - 32) / 8]);
			gset.ch = 0;
			gset.pos = 0;
		}
	}
}

void	get_pid(int signum, siginfo_t *sip, void *ptr)
{
	gset.pid = sip->si_pid;
}

int main(void)
{
	char	*str;
	int		i;

	while (1)
	{
		i = 0;
		gset.length = 0;
		gset.str = 0;
		gset.state = 0;
		gset.pid = 0;
		gset.ch = 0;
		gset.flag = 0;
		int pid = getpid();
		printf("%d\n", pid);
		struct sigaction act1, oact1;
		act1.sa_flags = SA_SIGINFO;
		act1.sa_sigaction = &get_pid;
		sigaction(SIGUSR1, &act1, NULL);
		pause();



		gset.state = 0;
		act1.sa_sigaction = &get_whole;
		sigaction(SIGUSR1, &act1, NULL);
		sigaction(SIGUSR2, &act1, NULL);
		kill(gset.pid, SIGUSR1);
		while (gset.state < 32 + 8 * (gset.length))
		{
		}
		printf("%d\n", gset.pid);
		printf("%s\n", gset.str);
		free(gset.str);
	}
}