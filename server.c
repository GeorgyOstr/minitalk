/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/05 21:59:29 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = 0;

int	ft_putchar(char c)
{
	int	res;

	res = 0;
	while (res == 0)
		res = write(1, &c, 1);
	if (res < 0)
		return (-100);
	return (res);
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

int	ft_putnbr(long n)
{
	int	ans;

	ans = 0;
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		ans += ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
		ans += ft_putnbr(n / 10);
	ans += ft_putchar(n % 10 + '0');
	return (ans);
}

int	main(void)
{
	const int			pid = getpid();
	struct sigaction	sa;
	size_t				i;
	int					log_fd;

	ft_putnbr(pid);
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
		i = 0;
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
