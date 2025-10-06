/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:46:20 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/06 22:53:39 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define TIMEOUT_TIME	0
# define TIMEOUT_COUNT	100000000

# define TIMEOUT_ERROR 1
# define INTERRUPT_ERROR 2
# define FAIL_KILL_ERROR 3
# define ACTION_INIT_ERROR 4
# define ARGS_ERROR 5
# define ATOI_ERROR 6
# define PID_ERROR 7
# define PID_NEGATIVE_ERROR 8

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>

typedef struct s_sig_atomic_data
{
	volatile sig_atomic_t	pid;
	volatile sig_atomic_t	sig;
}	t_sig_atomic_data;

int	ft_putchar(char c);
int	ft_putnbr(long n);
void	save_kill(pid_t pid, int sig);
void	action_init(void);

#endif
