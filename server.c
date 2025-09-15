#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int signal)
{
	printf("%d\n", signal==SIGUSR1);
}
void handler2(int signal)
{
	printf("%d\n", signal);
}

int	main(void)
{
	const long t = getpid();
	printf("%ld\n", t);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	int i = 0;
	while(1)
	{
		i++;
		pause();
		//printf("%d\n", i);
	}	
	return (0);
}
