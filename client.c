#include "minitalk.h"

typedef struct global_set {
	int length;
	int	ch;
	int old;
	int	state;
	int	pid;
	char	*str;
}global_set;

global_set gset;

void	send_again()
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
		write(1, "Transmission is delayed too much. Send the message again plz\n", 61);
		free(gset.str);
		exit(-1);
	}
		
}

void	send_whole(int signum, siginfo_t *sip, void *ptr)
{
	long	bit;
	static int	i;

	char	b = '0';

	if (gset.state < 8 * (gset.length + 1))
	{
		if ((gset.state) % 8 == 0)
		{
			gset.ch = gset.str[gset.state / 8];
		}
		bit = 0x80;
		if ((gset.ch & bit))
		{
			gset.old = SIGUSR1;
			b = '1';//1보내기
		}
		else
			gset.old = SIGUSR2; //0보내기
		/*write(1, &b, 1);
		write(1, "\n", 1);*/
		gset.ch = gset.ch << 1;
		gset.state ++;
		kill(gset.pid, gset.old);
	}
}



int main(int argc, char *argv[])
{
	int	pid = 10;
	struct sigaction act1, act2;

	gset.str = (char *)malloc(ft_strlen(argv[2]) + 1);
	strcpy(gset.str, argv[2]);
	gset.pid = ft_atoi(argv[1]);
	gset.state = 0;
	gset.length = ft_strlen(gset.str);
	gset.old = SIGUSR1;
	act1.sa_flags = SA_NODEFER | SA_SIGINFO;
	act1.sa_sigaction = &send_whole;
	sigaction(SIGUSR1, &act1, 0);
	sigaction(SIGUSR2, &act1, 0);
	int mypid = getpid();
	printf("%d\n", mypid);
	kill(gset.pid, gset.old);
	send_again();
	while (gset.state < 8 * (gset.length + 1))
	{
		send_again();
	}
	free(gset.str);
}