/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:44:34 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/28 14:21:19 by gostroum         ###   ########.fr       */
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
	usleep(100);
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
		sendchar(pid, (unsigned char)str[i++]);
	sendchar(pid, 0);
}

void	sendint(int pid, int num)
{
	int					i;
	const unsigned char	*p = (const unsigned char *)&num;

	i = 0;
	while (i < 4)
		sendchar(pid, p[i++]);
}

int	main(int argc, char **argv)
{
	int			i;
	const int	pid = getpid();

	i = 0;
	if (argc != 3)
		return (0);
	i = 0;
	sendint(atoi(argv[1]), pid);
	sendint(atoi(argv[1]), pid);
	//signal(SIGUSR1, handler);
	sendstr(atoi(argv[1]), argv[2]);
	return (0);
}
