/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/05 19:38:52 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t	g_ack = 0;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	handle_error(volatile sig_atomic_t pid, volatile sig_atomic_t ssi_pid)
{
	if (pid <= 0)
		exit (201);
	if (pid != ssi_pid)
	{
		kill(pid, SIGUSR2);
		kill(ssi_pid, SIGUSR2);
		exit(127);
	}
}

void	action(int sig, siginfo_t *info, void *context)
{
	static volatile sig_atomic_t	pid = -1;
	static volatile sig_atomic_t	bitnum = 0;
	static volatile sig_atomic_t	uchar = 0;

	g_ack = 1;
	if (pid == -1)
		pid = info->si_pid;
	handle_error(pid, info->si_pid);
	bitnum++;
	uchar >>= 1;
	uchar |= 128 * (sig == SIGUSR1);
	if (bitnum == 8)
	{
		if (uchar == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(127);
			pid = -1;
		}
		ft_putchar((char)uchar);
		bitnum = 0;
		uchar = 0;
	}
	(void)context;
	if (pid <= 0)
		return ;
	if (kill(pid, SIGUSR1) == -1)
		exit(127);
}

int	main(void)
{
	const int			pid = getpid();
	int					log_fd;
	struct sigaction	sa;

	printf("%d\n", pid);
	log_fd = open("log", O_CREAT | O_RDWR, 0644);
	dprintf(log_fd, "%d\n", pid);
	close(log_fd);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = action;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		g_ack = 0;
		size_t	i = 0;
		while (g_ack == 0 && i < 100000)
		{
			usleep(100);
			i++;
		}
	    if (g_ack == 0)
        	exit(1);
	}
	return (0);
}
