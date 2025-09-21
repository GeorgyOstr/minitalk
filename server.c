/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 22:03:26 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minitalk.h"

volatile t_data		g_val;
volatile sig_atomic_t	g_signal;

void	handler(int signal)
{
	g_val.c += 1;
	g_val.data >>= 1;
	g_val.data |= (signal == SIGUSR1) << 7;
}

void 	handl(int signal)
{
	g_signal = signal;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

#include <assert.h>

int	main(void)
{
	const long	t = getpid();

	g_val.c = 0;
	g_val.data = 0;
	printf("%ld\n", t);
//	log_fd = open("log");
//	dprintf(log_fd, "%lu\n", t);
//	close(log_fd);
	//signal(SIGUSR1, handler);
	struct sigaction sa;
	sa.sa_handler = handl;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	//signal(SIGUSR2, handler);
	while (1)
	{
		pause();
		g_val.c += 1;
		g_val.data >>= 1;
		g_val.data |= (g_signal == SIGUSR1) << 7;
		assert(g_val.c <= CHAR_BIT);
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
