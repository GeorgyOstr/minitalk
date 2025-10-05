/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:46:20 by gostroum          #+#    #+#             */
/*   Updated: 2025/10/05 21:56:54 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define TIMEOUT	10

# define TIMEOUT_ERROR 10
# define INTERRUPT_ERROR 120
# define FAIL_KILL_ERROR 127

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct s_sig_atomic_data
{
	volatile sig_atomic_t	pid;
	volatile sig_atomic_t	sig;
}	t_sig_atomic_data;

#endif