/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:44:34 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/05 21:55:25 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = 0;

void	sendbit(int pid, unsigned char a)
{
	int		res;
	size_t	i;

	g_ack = 0;
	i = 0;
	if ((a & 1) == 1)
		res = kill(pid, SIGUSR1);
	else
		res = kill(pid, SIGUSR2);
	if (res == -1)
		exit(200);
	while (g_ack == 0)
	{
		usleep(100);
		i++;
	}
	if (g_ack == 0)
		exit(1);
}

void	sendchar(int pid, unsigned char a)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		sendbit(pid, a & 1);
		i++;
		a >>= 1;
	}
}

void	sendstr(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		sendchar(pid, (unsigned char)str[i]);
		i++;
	}
	sendchar(pid, 0);
}

void	handler(int sig)
{
	(void)sig;
}

void	action(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1 && g_ack == 0)
		g_ack = 1;
	else if (sig == SIGUSR1 && g_ack == 1)
		exit (205);
	if (sig == SIGUSR2)
		exit (201);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = action;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3 || atoi(argv[1]) <= 0)
		return (0);
	sendstr(atoi(argv[1]), argv[2]);
	return (0);
}
