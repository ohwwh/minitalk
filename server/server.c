/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:07:21 by hoh               #+#    #+#             */
/*   Updated: 2022/05/30 22:07:22 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_global_set	g_set;

static void	kill_fail(void)
{
	ft_printf("kill failed - code: %d\n", g_set.erno);
	g_set.state = -2;
}

void	char_process(void)
{
	const char	c = g_set.ch;

	write(1, &c, 1);
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
		g_set.erno = errno;
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

	ptr = 0;
	if (g_set.state == -2)
		return ;
	if (g_set.state == -1)
	{
		g_set.pid = sip->si_pid;
		ft_printf("[Client %d]: ", g_set.pid);
	}
	else if (g_set.pid == sip->si_pid) //pid = 0 swapper mac os 에서만, 
	{
		bit = 0x80;
		g_set.ch *= 2;
		if (signum == SIGUSR1)
		g_set.ch += 1;
	}
	g_set.state ++;
	if (g_set.state == 8)
		char_process();
	g_set.k = kill(g_set.pid, SIGUSR1);
	g_set.erno = errno;
}

int	main(void)
{
	const int			pid = getpid();
	struct sigaction	act;

	ft_printf("[Server PID: %d]\n", pid);
	while (1)
	{
		g_set.pid = 0;
		g_set.ch = 0;
		g_set.old = SIGUSR1;
		g_set.state = -1;
		sigemptyset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO | SA_NODEFER;
		act.sa_sigaction = &get_whole;
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
		while (g_set.state != -2)
		{
			if (!usleep(1000000))
				get_again();
		}
		write(1, "\n", 1);
	}
}
