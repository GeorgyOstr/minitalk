/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 15:47:46 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minitalk.h"

t_data	g_val;

void	handler(int signal)
{
	printf("Income signal: SIGUSR%d  \n", 2 - (signal == SIGUSR1));
	g_val.c += 1;
	g_val.data <<= 1;
	g_val.data |= (signal == SIGUSR1);
}

int	main(void)
{
	const long	t = getpid();
	int			i;

	g_val.c = 0;
	g_val.data = 0;
	printf("%ld\n", t);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	i = 0;
	while (1)
	{
		i++;
		pause();
		printf("g_val.data = %d, g_val.c = %d\n", g_val.data, g_val.c);
		if (g_val.c == 8)
			exit(0);
	}
	return (0);
}
