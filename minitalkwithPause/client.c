#include <signal.h>
//#include <sys/type.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

int	send_int(int n, int pid)
{
	long	bit;
	int	i;
	int	ret;

	bit = 0x80000000;
	i = 0;
	while (i < 32)
	{
		if ((n & bit))
			ret = kill(pid, SIGUSR1); //1보내기
		else
			ret = kill(pid, SIGUSR2); //0보내기
		//usleep(1000);
		pause();
		if (ret == -1)
			return (-1);
		n = n << 1;
		i ++;
	}
	return (0);
}

int	send_char(char c, int pid)
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

	signal(SIGUSR1, well_recieved);
	int mypid = getpid();
	scanf("%d", &pid);
	i = 0;
	kill(pid, SIGUSR1);
	pause();
	
	//usleep(1000);


	printf("not stop in pid\n");
	send_int(strlen(str), pid);
	printf("not stop in length\n");
	while (str[i])
	{
		//usleep(1000);
		pause();
		send_char(str[i], pid);
		i ++;
	}
	printf("not stop in char\n");
}