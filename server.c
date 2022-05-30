#include "minitalk.h"

global_set	g_set;

void	check(int signum)
{
	if (g_set.state == 1 && signum != SIGUSR2)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 2 && signum != SIGUSR1)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 3 && signum != SIGUSR1)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 4 && signum != SIGUSR2)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 5 && signum != SIGUSR2)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 6 && signum != SIGUSR2)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 7 && signum != SIGUSR2)
		write(1, "\nwrong!\n", 8);
	else if (g_set.state == 8 && signum != SIGUSR1)
		write(1, "\nwrong!\n", 8);

}

/*void	check_ch(void)
{
	int	bit = 0x80;

	//write(1, "\n", 1);
	if (g_set.state == 1 && g_set.ch != 0)
	{
		printf("%d += %d\n", 0, 0);
		printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 2 && g_set.ch != 64)
	{
		printf("%d += (%d >> %d = %d)\n", 0, bit, 1, bit >> 1);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 3 && g_set.ch != 96)
	{
		  printf("%d += (%d >> %d = %d)\n", 64, bit, 2, bit >> 2);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 4 && g_set.ch != 96)
	{
		  printf("%d += %d\n", 96, 0);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 5 && g_set.ch != 96)
	{
		 printf("%d += %d\n", 96, 0);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 6 && g_set.ch != 96)
	{
		  printf("%d += %d\n", 96, 0);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 7 && g_set.ch != 96)
	{
		 printf("%d += %d\n", 96, 0);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
	else if (g_set.state == 8 && g_set.ch != 97)
	{
		 printf("%d += (%d >> %d = %d)\n", 96, bit, 8, bit >> 8);
		 printf("%d += (%d >> %d = %d)\n\n", g_set.oldch, bit, g_set.state - 1, bit >> (g_set.state - 1));
	}
}*/

void	check_ch(void)
{
	int	bit = 0x80;

	//write(1, "\n", 1);
	if (g_set.state == 1 && g_set.ch != 0)
	{
		printf("\nexpected = %d, result = %d\n", 0, g_set.ch);
	}
	else if (g_set.state == 2 && g_set.ch != 64)
	{
		printf("\nexpected = %d, result = %d\n", 64, g_set.ch);
	}
	else if (g_set.state == 3 && g_set.ch != 96)
	{
		printf("\nexpected = %d, result = %d\n", 96, g_set.ch);
	}
	else if (g_set.state == 4 && g_set.ch != 96)
	{
		printf("\nexpected = %d, result = %d\n", 96, g_set.ch);
	}
	else if (g_set.state == 5 && g_set.ch != 96)
	{
		printf("\nexpected = %d, result = %d\n", 96, g_set.ch);
	}
	else if (g_set.state == 6 && g_set.ch != 96)
	{
		  printf("\nexpected = %d, result = %d\n", 96, g_set.ch);
	}
	else if (g_set.state == 7 && g_set.ch != 96)
	{
		 printf("\nexpected = %d, result = %d\n", 96, g_set.ch);
	}
	else if (g_set.state == 8 && g_set.ch != 97)
	{
		printf("\nexpected = %d, result = %d\n", 97, g_set.ch);
	}
}

static void	kill_fail(void)
{
	ft_printf("kill failed - code: %d\n", errno);
	g_set.state = -2;
}

static void	char_process(void)
{
	write(1, &g_set.ch, 1);
	if (g_set.ch == '\0')
		g_set.state = -2;
	else
	{
		g_set.ch = 0;
		g_set.state = 0;
	}
}

static void	get_again(void)
{
	int	i;

	i = 0;
	while (i ++ < 5)
	{	
		if (g_set.k != 0)
		{
			kill_fail();
			return ;
		}
		if (usleep(1000000))
			break ;
		g_set.k = kill(g_set.pid, g_set.old);
		write(1, "\nTransmission is delayed......\n", 31);
	}
	if (i == 5)
	{
		write(1, "\nTransmission is delayed too much. FAIL\n", 40);
		g_set.state = -2;
	}
}

void	get_whole(int signum, siginfo_t *sip, void *ptr)
{
	int	bit;
	int	old;

	if (g_set.state == -2)
		return ;
	if (g_set.state == -1)
	{
		g_set.pid = sip->si_pid;
		ft_printf("[Client %d]: ", g_set.pid);
	}
	else if (g_set.pid == sip->si_pid)
	{
		bit = 0x80;
		if (signum == SIGUSR1)
			g_set.ch += (bit >> g_set.state); 
	}
	g_set.state ++;
	check_ch();
	if (g_set.state == 8)
	{
		write(1, &g_set.ch, 1);
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
			/*if (g_set.k != 0)
			{
				kill_fail();
			}*/
			if (!usleep(1000000))
				get_again();
		}
		write(1, "\n", 1);
	}
}
