#include "minitalk.h"

typedef struct global_set {
	int length;
	int	it;
	int	ch;
	int	oc;
	int pos;
	int	state;
	int	pid;
	int	flag;
	char	*str;
}global_set;

global_set gset;

void	send_whole(int signum, siginfo_t *sip, void *ptr)
{
	long	bit;
	static int	n;

	int	b = 0;
	if (gset.state < 32)
	{
		bit = 0x80000000;
		if ((gset.it & bit))
		{
			kill(gset.pid, SIGUSR1);
			b = 1; //1보내기
		}
		else
			kill(gset.pid, SIGUSR2); //0보내기
		gset.it = gset.it << 1;
		gset.state ++;
		//printf("%d int ack called, state is %d, bit is %d\n", n ++, gset.state, b);
	}
	else if (gset.state >= 32 && gset.state < 32 + 8 * (gset.length))
	{
		if ((gset.state - 32) % 8 == 0)
		{
			gset.ch = gset.str[(gset.state - 32) / 8];
			//printf("%c\n", gset.str[(gset.state - 32) / 8]);
		}
		bit = 0x80;
		if ((gset.ch & bit))
		{
			kill(gset.pid, SIGUSR1);
			b = 1; //1보내기
		}
		else
			kill(gset.pid, SIGUSR2); //0보내기
		//printf("%d char %c ack called, state is %d, bit is %d\n", n ++, gset.ch ,gset.state, b);
		gset.ch = gset.ch << 1;
		gset.state ++;
	}
}

int main(int argc, char *argv[])
{
	int	pid = 10;
	int	i = 0;
	struct sigaction act1, oact1;

	gset.str = (char *)malloc(ft_strlen(argv[2]) + 1);
	strcpy(gset.str, argv[2]);
	gset.pid = ft_atoi(argv[1]);
	gset.state = 0;
	gset.length = ft_strlen(gset.str);
	gset.it = gset.length;
	act1.sa_flags = SA_SIGINFO;
	act1.sa_sigaction = &send_whole;
	sigaction(SIGUSR1, &act1, &oact1);
	int mypid = getpid();
	i = 0;
	kill(gset.pid, SIGUSR1);

	while (gset.state < 32 + 8 * (gset.length)){
	}
	free(gset.str);
}