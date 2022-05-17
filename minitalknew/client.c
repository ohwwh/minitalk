#include <signal.h>
//#include <sys/type.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct global_set {
	int length;
	int	ch;
	int	oc;
	int pos;
	int	pid;
	int	flag;
}global_set;

global_set gset;

void	well_recieved(int signum)
{
	//printf("well received!\n");
	return ;
}

int	send_pid(int n, int pid)
{
	long	bit;
	int	i;
	int	ret;

	bit = 0x80000000;
	i = 0;
	while (i < 32)
	{
		usleep(1000);
		if ((n & bit))
			ret = kill(pid, SIGUSR1); //1보내기
		else
			ret = kill(pid, SIGUSR2); //0보내기
		if (ret == -1)
			return (-1);
		n = n << 1;
		i ++;
		
	}
	return (0);
}

void	send_int(int signum)
{
	long	bit;
	static int	n;

	bit = 0x80000000;
	if (gset.pos < 32)
	{
		if ((gset.length & bit))
			kill(gset.pid, SIGUSR1); //1보내기
		else
			kill(gset.pid, SIGUSR2); //0보내기
		gset.length = gset.length << 1;
		gset.pos ++;
		signal(SIGUSR1, send_int);
		printf("%d int ack called, pos is %d\n", n ++, gset.pos);
	}
}

void	send_char(int signum)
{
	int	bit;
	static int	n;

	bit = 0x80;
	if (gset.pos < 8)
	{
		if ((gset.ch & bit))
			kill(gset.pid, SIGUSR1); //1보내기
		else
			kill(gset.pid, SIGUSR2); //0보내기
		printf("%d char %c ack called, pos is %d\n", n ++, gset.ch ,gset.pos);
		gset.ch = gset.ch << 1;
		gset.pos ++;
		signal(SIGUSR1, send_char);
	}
}

int	send_char_old(char c, int pid)
{
	int	bit;
	int	i;
	int	ret;
	char	oc;

	oc = c;
	bit = 0x80;
	i = 0;
	while (i < 8)
	{
		if ((c & bit))
			ret = kill(pid, SIGUSR1); //1보내기
		else
			ret = kill(pid, SIGUSR2); //0보내기
		//usleep(1000);
		pause();
		if (ret == -1)
			return (-1);
		c = c << 1;
		i ++;
		printf("not stop in %d phase of the char %c\n", i, oc);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	char str[100] = "This is random why not working";
	//char str[100] = "Hello";
	int	pid = 10;
	int	i;

	gset.pos = 0;
	gset.length = strlen(str);
	signal(SIGUSR1, send_int);
	int mypid = getpid();
	scanf("%d", &gset.pid);
	i = 0;
	kill(gset.pid, SIGUSR1);
	

	while (gset.pos < 32){}



	signal(SIGUSR1, send_char);
	gset.pos = 0;
	gset.ch = str[i];
	while (gset.pos < 8){}
	/*while (str[i])
	{
		gset.pos = 0;
		gset.ch = str[i];
		gset.oc = str[i];
		//printf("%c\n", str[i]);
		while (gset.pos < 8){}
		i ++;
	}*/
}