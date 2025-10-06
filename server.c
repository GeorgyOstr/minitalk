/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/06 22:52:10 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_sig_atomic_data	g_data = {0};

# include <fcntl.h>
# include <stdio.h>

void logger(pid_t pid)
{
	int	log_fd;

	log_fd = open("log", O_CREAT | O_RDWR, 0644);
	dprintf(log_fd, "%d\n", pid);
	close(log_fd);
}

void check_client_pid(pid_t pid, pid_t tpid)
{
	if (pid != tpid)
	{
		save_kill(pid, SIGUSR2);		
		save_kill(tpid, SIGUSR2);
		exit (PID_ERROR);
	}
}

unsigned char receive_bit(pid_t *pid)
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
		usleep(TIMEOUT_TIME);
	}
	i = 0;
	while (sig == 0 && i < TIMEOUT_COUNT)
	{
		tpid = g_data.pid;
		sig = g_data.sig;
		usleep(TIMEOUT_TIME);
		i++;
	}
	check_client_pid(*pid, tpid);
	if (sig == 0)
		exit(TIMEOUT_ERROR);
	g_data.sig = 0;
	save_kill(*pid, SIGUSR1);
	return (sig);
}

unsigned char receive_byte(pid_t *pid)
{
	unsigned char	byte;
	int				i;
	int				bit;

	i = 0;
	byte = 0;
	bit = 0;
	while (i < 8)
	{
		byte >>= 1;
		bit = receive_bit(pid);
		byte |= 128 * (bit == SIGUSR1);
		i++;
	}
	
	return (byte);
}

void receive(void)
{
	static	pid_t	pid = -1;
	unsigned char	byte;

	while (1)
	{
		byte = receive_byte(&pid);
		if (byte == 0)
		{
			pid = -1;
			g_data.pid = -1;
			g_data.sig = 0;
		}	
		else
			ft_putchar(byte);
	}
}

int	main(void)
{
	const pid_t			pid = getpid();
	
	g_data.pid = -1; 
	g_data.sig = 0;
	action_init();
	ft_putnbr(pid);
	ft_putchar('\n');
	logger(pid);
	receive();
	return (0);
}
