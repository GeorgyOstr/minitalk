/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/07 16:28:35 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_sig_atomic_data	g_data = {0};

static void	check_client_pid(pid_t pid, pid_t tpid)
{
	if (pid != tpid)
	{
		save_kill(pid, SIGUSR2);
		save_kill(tpid, SIGUSR2);
		exit(PID_ERROR);
	}
}

static unsigned char	receive_bit(pid_t *pid)
{
	size_t	i;
	int		sig;
	pid_t	tpid;

	sig = g_data.sig;
	tpid = g_data.pid;
	while (*pid == -1)
	{
		*pid = g_data.pid;
		tpid = *pid;
		sig = g_data.sig;
	}
	i = 0;
	while (sig == 0 && i < TIMEOUT_COUNT)
	{
		tpid = g_data.pid;
		sig = g_data.sig;
		i++;
	}
	check_client_pid(*pid, tpid);
	if (sig == 0)
		exit(TIMEOUT_ERROR);
	g_data.sig = 0;
	save_kill(*pid, SIGUSR1);
	return (sig);
}

static unsigned char	receive_byte(pid_t *pid)
{
	unsigned char	byte;
	char			i;
	int				sig;

	i = 0;
	byte = 0;
	sig = 0;
	while (i < 8)
	{
		byte >>= 1;
		sig = receive_bit(pid);
		byte |= 128 * (sig == SIGUSR1);
		i++;
	}
	return (byte);
}

static void	receive(void)
{
	static pid_t	pid = -1;
	char			bytes[BUFFER];
	int				i;

	i = 0;
	while (1)
	{
		bytes[i] = receive_byte(&pid);
		if (bytes[i] == 0)
		{
			write(1, bytes, i);
			pid = -1;
			g_data.pid = -1;
			g_data.sig = 0;
			i = -1;
		}
		else if (i == BUFFER - 1)
		{
			write(1, bytes, BUFFER);
			i = -1;
		}
		i++;
	}
}

int	main(void)
{
	const pid_t	pid = getpid();

	g_data.pid = -1;
	g_data.sig = 0;
	action_init();
	ft_putnbr(pid);
	ft_putchar('\n');
	receive();
	return (0);
}
