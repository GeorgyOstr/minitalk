/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/28 23:04:18 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minitalk.h"

void	action(int sig, siginfo_t *info, void *context)
{
	int pid = info->si_pid;

	(void) context;	
	
	if (sig == SIGUSR1)
		sendsignal()
	info->si_pid;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	main(void)
{
	const int			pid = getpid();
	int					log_fd;
	struct sigaction	sa;

	printf("%d\n", pid);
	log_fd = open("log");
	dprintf(log_fd, "%d\n", pid);
	close(log_fd);
	
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_action = action;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	//signal(SIGUSR2, handler);
	while (1)
	{
		pause();
		g_val.c += 1;
		g_val.data >>= 1;
		g_val.data |= (g_signal == SIGUSR1) << 7;
		if (g_val.c == CHAR_BIT)
		{
			if (g_val.data == 0)
				exit (0);
			ft_putchar((char)g_val.data);
			g_val.c = 0;
			g_val.data = 0;
		}
	}
	return (0);
}
