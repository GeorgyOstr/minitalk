/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:44:34 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 15:42:37 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 11 = 1; 22 = 0; 12 = end; 21 = error
void	sendbit(int pid, char a)
{
	if ((a & 1) == 1)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(100);
}

void	sendchar(int pid, char a)
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
	sendchar(atoi(argv[1]), 25);
	return (0);
}
