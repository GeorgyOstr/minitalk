/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/28 14:24:57 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minitalk.h"

t_data	g_val;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	handler(int signal)
{
	g_val.c += 1;
	g_val.data >>= 1;
	g_val.data |= 128 * (signal == SIGUSR1);
}

int	receivechr(int pid_client)
{
	if (g_val.c == CHAR_BIT)
	{
		ft_putchar((char)g_val.data);
		g_val.c = 0;
		if (!g_val.data)
			return (0);
	}
	//kill(pid_client, SIGUSR1);
	//usleep(100);
	return (1);
}

void	receivepid(int *pid, int i)
{
	unsigned char	*c;

	c = (unsigned char *)pid;
	if (g_val.c == CHAR_BIT)
	{
		c[i / 8] = (unsigned char)g_val.data;
		g_val.c = 0;
	}
}

int	main(void)
{
	const int	pid = getpid();
	int			pid_client;
	int			pid_client1;
	int			i;

	g_val.c = 0;
	g_val.data = 0;
	printf("%d\n", pid);
//	log_fd = open("log");
//	dprintf(log_fd, "%lu\n", t);
//	close(log_fd);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	pid_client = 0;
	pid_client1 = 0;
	while (1)
	{
		i = 0;
		while (i < 32)
		{
			pause();
			receivepid(&pid_client, i++);
		}
		i = 0;
		while (i < 32)
		{
			pause();
			receivepid(&pid_client1, i++);
		}
		if (pid_client1 != pid_client)
			return (125);
		pause();
		while (receivechr(pid_client))
			pause();
	}
	return (0);
}
