/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoh <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 22:07:10 by hoh               #+#    #+#             */
/*   Updated: 2022/05/30 22:07:12 by hoh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

global_set	g_set;

static int	isdigit_string(char *str)
{
	while (*str)
	{
		if (0 + '0' > *str | 9 + '0' < *str)
			return (0);
		str ++;
	}
	return (1);
}

static void	kill_fail(void)
{
	ft_printf("kill failed - code: %d\n", g_set.erno);
	free(g_set.str);
	exit(1);
}

void	send_again(void)
{
	int	i;

	i = 0;
	while (i ++ < 5)
	{	
		if (g_set.k != 0)
			kill_fail();
		if (usleep(1000000))
			break ;
		g_set.k = kill(g_set.pid, g_set.old);
		write(1, "Transmission is delayed......\n", 30);
	}
	if (i == 5)
	{
		write(1, "Transmission is delayed. Send the message again plz\n", 61);
		free(g_set.str);
		exit(-1);
	}
}

void	send_whole(int signum, siginfo_t *sip, void *ptr)
{
	long		bit;

	signum = 1;
	ptr = 0;
	sip = 0;
	if (g_set.state < 8 * (g_set.length + 1))
	{
		if ((g_set.state) % 8 == 0)
		{
			g_set.ch = g_set.str[g_set.state / 8];
		}
		bit = 0x80;
		if ((g_set.ch & bit))
			g_set.old = SIGUSR1;
		else
			g_set.old = SIGUSR2;
		g_set.ch = g_set.ch << 1;
		g_set.state ++;
		g_set.k = kill(g_set.pid, g_set.old);
		g_set.erno = errno;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act1;

	if ((argc != 3) | (!isdigit_string(argv[1])))
	{
		ft_printf("Invalid arguments\n");
		return (-1);
	}
	g_set.str = (char *)malloc(ft_strlen(argv[2]) + 1);
	ft_strlcpy(g_set.str, argv[2], ft_strlen(argv[2]) + 1);
	g_set.pid = ft_atoi(argv[1]);
	g_set.state = 0;
	g_set.length = ft_strlen(g_set.str);
	g_set.old = SIGUSR1;
	act1.sa_flags = SA_NODEFER | SA_SIGINFO;
	act1.sa_sigaction = &send_whole;
	sigaction(SIGUSR1, &act1, 0);
	sigaction(SIGUSR2, &act1, 0);
	g_set.k = kill(g_set.pid, g_set.old);
	g_set.erno = errno;
	while (g_set.state < 8 * (g_set.length + 1))
	{
		if (!usleep(999999))
			send_again();
	}
	free(g_set.str);
}
