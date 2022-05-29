#include "minitalk.h"

global_set	g_set;

void	write_debug(char b, int state)
{
	write(1, "b is ", 5);
	write(1, &b, 1);
	write(1, ", state is ", 11);
	ft_putnbr_fd(state, 1);
	write(1, "\n", 1);
}

void	kill_fail(void)
{
	ft_printf( "kill failed - code: %d\n", errno);
	g_set.state = -2;
}

void	get_again(void)
{
	int	i;

	i = 0;
	while (i ++ < 15)
	{	
		if (g_set.k != 0)
			kill_fail();
		if (sleep(1))
			break ;
		g_set.k = kill(g_set.pid, g_set.old);
		write(1, "Transmission is delayed......\n", 30);
	}
	if (i == 15)
	{
		write(1, "Transmission is delayed too much. FAIL\n", 39);
		g_set.state = -2;
	}
}

void	get_whole(int signum, siginfo_t *sip, void *ptr)
{
	long	bit;
	char	b = '0';

	if (g_set.state != -2)
	{
		if (g_set.state == -1)
		{
			g_set.pid = sip->si_pid;
			ft_printf("[Client %d]: ", g_set.pid);
		}
		else if (g_set.pid == sip->si_pid)
		{
			bit = 0x80;
			if (signum == SIGUSR1)
			{
				g_set.ch = g_set.ch + (bit >> g_set.state);
				b = '1';
			}
		}
		/*write(1, &b, 1);
		write(1, "\n", 1);*/
		//write_debug(b, g_set.state);
		g_set.state ++;
		if (g_set.state == 8)
		{
			write(1, &g_set.ch, 1);
			/*write(1, "\n", 1);
			printf("%d\n", g_set.ch);*/
			if (g_set.ch == '\0')
				g_set.state = -2;
			else
			{
				g_set.ch = 0;
				g_set.state = 0;
			}
		}
		g_set.k = kill(g_set.pid, SIGUSR1);
	}
}

int	main(void)
{
	const int			pid = getpid();
	struct sigaction	act1;

	ft_printf("[Server PID: %d]\n", pid);
	while (1)
	{
		g_set.pid = 0;
		g_set.ch = 0;
		g_set.old = SIGUSR1;
		g_set.state = -1;
		act1.sa_flags = SA_NODEFER | SA_SIGINFO;
		act1.sa_sigaction = &get_whole;
		sigaction(SIGUSR1, &act1, NULL);
		sigaction(SIGUSR2, &act1, NULL);
		pause();
		while (g_set.state != -2)
		{
			get_again();
		}
		write(1, "\n", 1);
	}
}
