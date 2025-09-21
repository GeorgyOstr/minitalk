/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 14:03:45 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	handler(int signal)
{
	printf("%d\n", signal == SIGUSR1);
}

void	handler2(int signal)
{
	printf("%d\n", signal);
}

int	main(void)
{
	const long	t = getpid();
	int			i;

	printf("%ld\n", t);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	i = 0;
	while (1)
	{
		i++;
		pause();
		//printf("%d\n", i);
	}
	return (0);
}
