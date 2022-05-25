#include "minitalk.h"

//long sentence can't be sent

typedef struct global_set {
	int length;
	int	ch;
	int old;
	int	state;
	int	pid;
	char	*str;
}global_set;

global_set gset;

void	write_debug(char b, int state)
{
	write(1, "b is ", 5);
	write(1, &b, 1);
	write(1, ", state is ", 11);
	ft_putnbr_fd(state, 1);
	write(1, "\n", 1);
}

void	get_again(void)
{
	int	i;

	i = 0;
	while (i ++ < 15)
	{	if (sleep(1))
			break ;
		kill(gset.pid, gset.old);
		write(1, "Transmission is delayed......\n", 30);
	}
	if (i == 15)
	{
		write(1, "Transmission is delayed too much. FAIL\n", 39);
		gset.state = -2;
	}
		
}

void	get_whole(int signum, siginfo_t *sip, void *ptr)
{
	static int n;

	long    bit;
	char	b = '0';
	
	if (gset.state != -2)
	{
		if (gset.state == -1)
		{
			gset.pid = sip->si_pid;
			ft_putnbr_fd(gset.pid, 1);
			write(1, ": ", 2);
		}
		else if(gset.pid == sip->si_pid)
		{
			bit = 0x80;
			if (signum == SIGUSR1)
			{
				gset.ch = gset.ch + (bit >> gset.state);
				b = '1';
			}
		}
		//write_debug(b, gset.state);
		gset.state ++;
		if (gset.state == 8)
		{
			write(1, &gset.ch, 1);
			if (gset.ch == '\0')
				gset.state = -2;
			else
			{
				gset.ch = 0;
				gset.state = 0;
			}
		}
		kill(gset.pid, SIGUSR1);
	}
}

int main(void)
{
	char	*str;
	int		i;
	int		s;
	int 	pid = getpid();
	printf("%d\n", pid);

	while (1)
	{
		i = 0;
		gset.pid = 0;
		gset.ch = 0;
		gset.old = SIGUSR1;
		struct sigaction act1, oact1;
		gset.state = -1;
		act1.sa_flags = SA_NODEFER | SA_SIGINFO;
		act1.sa_sigaction = &get_whole;
		sigaction(SIGUSR1, &act1, NULL);
		sigaction(SIGUSR2, &act1, NULL);
		pause();
		while (gset.state != -2)
		{
			get_again();
		}
		write(1, "\n", 1);
	}
}