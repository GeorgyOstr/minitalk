/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:23:55 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/07 19:34:15 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static pid_t	pid_atoi(char *str)
{
	int		i;
	long	ans;

	i = 0;
	ans = 0;
	while (str[i] && i < 20)
	{
		if ('0' > str[i] || str[i] > '9')
			exit (ATOI_ERROR);
		ans = 10 * ans + (str[i] - '0');
		i++;
	}
	if (!ans)
		exit (ARGS_ERROR);
	return (ans);
}

pid_t	validate(int argc, char **argv)
{
	if (argc != 3)
		exit (ARGS_ERROR);
	return (pid_atoi(argv[1]));
}
