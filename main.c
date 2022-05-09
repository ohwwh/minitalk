#include <signal.h>
#include <sys/type.h>

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
			return (-1)
		c = c << 1;
		i ++;
		
	}
	return (0)
}

int main(void)
{
	char str[6] = "Hello";
	int	pid = 10;
	int	i;

	while (1)
	{
		i = 0;
		while (str[i])
		{
			if (send_char(pid, str[i]) == -1)
			
			i ++;
		}
		send_char(pid, str[i]);
	}
}