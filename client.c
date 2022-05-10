#include <signal.h>
//#include <sys/type.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int	send_int(int n, int pid)
{
	long	bit;
	int	i;
	int	ret;

	bit = 0x80000000;
	i = 0;
	while (i < 32)
	{
		usleep(100);
		if ((n & bit))
			ret = kill(pid, SIGUSR1); //1보내기
		else
			ret = kill(pid, SIGUSR2); //0보내기
		if (ret == -1)
			return (-1);
		//pause();
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

	bit = 0x80;
	i = 0;
	while (i < 8)
	{
		if ((c & bit))
			ret = kill(pid, SIGUSR1); //1보내기
		else
			ret = kill(pid, SIGUSR2); //0보내기
		if (ret == -1)
			return (-1);
		//pause();
		c = c << 1;
		i ++;
		
	}
	return (0);
}

int main(int argc, char *argv[])
{
	char str[6] = "Hello";
	int	pid = 10;
	int	i;

	scanf("%d", &pid);
	i = 0;
	send_int(27, pid);
	//00000000000000000000000000000110
	/*while (str[i])
	{
		if (send_char(pid, str[i]) == -1)
			return (printf("You can't send\n"));
		i ++;
	}
	send_char(pid, str[i]);*/
	
}