/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 18:26:35 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "minitalk.h"

t_data	g_val;

void	handler(int signal)
{
	g_val.c += 1;
	g_val.data >>= 1;
	g_val.data |= 128 * (signal == SIGUSR1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
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
		if (g_val.c == CHAR_BIT)
		{
			if (g_val.data == 0)
				exit (0);
			ft_putchar((char)g_val.data);
			g_val.c = 0;
		}
	}
	return (0);
}
