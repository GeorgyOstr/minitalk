/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:44:34 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 17:18:25 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
	while (i < 8)
	{
		sendbit(pid, a & 1);
		i++;
		a >>= 1;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	size_t	len;

	if (argc != 3)
		return (0);
	len = strlen(argv[2]);
	i = 0;
	sendchar(atoi(argv[1]), atoi(argv[2]));
	return (0);
}
