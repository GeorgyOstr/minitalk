/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:02:31 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/28 23:04:18 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include "minitalk.h"

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    action(int sig, siginfo_t *info, void *context)
{
    static volatile sig_atomic_t pid = -1;
    static volatile sig_atomic_t bitnum = 0;
    static volatile sig_atomic_t uchar = 0;

    if (pid == -1)
        pid = info->si_pid;
    if (pid != info->si_pid || pid <= 0)
        return ;
    bitnum++;
    uchar >>= 1;
    uchar |= 128 * (sig == SIGUSR1);
    if (bitnum == 8)
    {
        if (uchar == 0)
            pid = -1;
        ft_putchar((char) uchar);
        bitnum = 0;
        uchar = 0;
    }
    (void) context;    
    if (kill(pid, SIGUSR1) == -1)
        exit (127);
}

int    main(void)
{
    const int            pid = getpid();
    int                    log_fd;
    struct sigaction    sa;

    printf("%d\n", pid);
    log_fd = open("log", O_CREAT | O_RDWR, 0644);
    dprintf(log_fd, "%d\n", pid);
    close(log_fd);
    
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = action;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    while (1)
        pause();
    return (0);
}
