/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:08:56 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/07 12:09:02 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern t_sig_atomic_data	g_data;

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

void	save_kill(pid_t pid, int sig)
{
	if (pid < 0)
		exit(PID_NEGATIVE_ERROR);
	if (kill(pid, sig) == -1)
		exit (FAIL_KILL_ERROR);
}

static void	action(int sig, siginfo_t *info, void *context)
{
	(void)context;
	g_data.sig = sig;
	g_data.pid = info->si_pid;
}

void	action_init(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = action;
	if (sigemptyset(&sa.sa_mask) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR1) == -1
		|| sigaddset(&sa.sa_mask, SIGUSR2) == -1
		|| sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (ACTION_INIT_ERROR);
}
