#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 11 = 1; 22 = 0; 12 = end; 21 = error
void sendbit(int pid, char a)
{
	if (a == 0)
	{
		kill(pid, SIGUSR1);
		usleep(1);
		kill(pid, SIGUSR1);
	}
	else if (a == 0)
	{
		kill(pid, SIGUSR2);
		usleep(1);
		kill(pid, SIGUSR2);
	}
	else if (a == 2)
	{
		kill(pid, SIGUSR1);
		usleep(1);
		kill(pid, SIGUSR2);
	}
	usleep(1);
}

void sendchar()
{
}

int main(int argc, char **argv)
{
	char	*s;
	int		i;

	if (argc != 3)
		return (0);
	size_t len = strlen(argv[2]);
	printf("%d, %ld\n", atoi(argv[1]), len);
	i = 0;
	while (i < 4)
	{
		sendbit(atoi(argv[1]), len);
		i++;
		len /= 2;
	}
	kill(atoi(argv[1]), SIGUSR1);
	return(0);
}
