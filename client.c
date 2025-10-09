/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:06:46 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/07 16:32:26 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_sig_atomic_data	g_data = {0};

static void	check_server_pid(pid_t pid, pid_t data_pid)
{
	char	i;

	if (pid != data_pid)
	{
		i = 0;
		while (i < 16)
		{
			save_kill(pid, SIGUSR2);
			i++;
		}
		exit(PID_ERROR);
	}
}

static void	sendbit(unsigned char a)
{
	static pid_t	pid = -1;
	size_t			i;

	if (pid == -1)
		pid = g_data.pid;
	check_server_pid(pid, g_data.pid);
	g_data.sig = 0;
	if ((a & 1) == 1)
		save_kill(pid, SIGUSR1);
	else
		save_kill(pid, SIGUSR2);
	i = 0;
	while (g_data.sig == 0 && i < TIMEOUT_COUNT)
		i++;
	if (g_data.sig == SIGUSR2)
		exit(0);
	if (g_data.sig == 0)
		exit(TIMEOUT_ERROR);
}

static void	sendchar(unsigned char a)
{
	char	i;

	i = 0;
	while (i < 8)
	{
		sendbit(a & 1);
		i++;
		a >>= 1;
	}
}

static void	sendstr(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		sendchar((unsigned char)str[i]);
		i++;
	}
	sendchar(0);
}

int	main(int argc, char **argv)
{
	g_data.pid = validate(argc, argv);
	action_init();
	sendstr(argv[2]);
	return (0);
}
