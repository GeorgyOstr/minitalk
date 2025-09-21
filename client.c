/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:44:34 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 18:26:38 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void	sendbit(int pid, unsigned char a)
{
	if ((a & 1) == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(1);
}

void	sendchar(int pid, unsigned char a)
{
	int	i;

	i = 0;
	while (i < CHAR_BIT)
	{
		sendbit(pid, a & 1);
		i++;
		a >>= 1;
	}
}

void	sendstr(int pid, char *str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		sendchar(pid, (unsigned char)str[i]);
		i++;
	}
	sendchar(pid, 0);
}

int	main(int argc, char **argv)
{
	int		i;

	if (argc != 3)
		return (0);
	i = 0;
	sendstr(atoi(argv[1]), argv[2]);
	return (0);
}
