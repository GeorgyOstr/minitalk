/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gostroum <gostroum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 13:44:34 by gostroum          #+#    #+#             */
/*   Updated: 2025/09/21 21:38:18 by gostroum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

volatile sig_atomic_t ack_received = 0;

void    sendbit(int pid, unsigned char a)
{
    int    res;

    ack_received = 0;
    if ((a & 1) == 1)
        res = kill(pid, SIGUSR1);
    else
        res = kill(pid, SIGUSR2);
    if (res == -1)
        exit (200);
    while (!ack_received)
            pause();
}

void    sendchar(int pid, unsigned char a)
{
    int    i;

    i = 0;
    while (i < CHAR_BIT)
    {
        sendbit(pid, a & 1);
        //printf("done");
        i++;
        a >>= 1;
    }
}

void    sendstr(int pid, char *str)
{
    int        i;

    i = 0;
    while (str[i] != 0)
    {
        sendchar(pid, (unsigned char)str[i]);
        i++;
    }
    sendchar(pid, 0);
}

void    action(int sig, siginfo_t *info, void *context)
{

    (void)info;
    (void)context;
    ack_received = 1;
}

int    main(int argc, char **argv)
{
    struct sigaction    sa;

    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = action;
    sigemptyset(&sa.sa_mask);
    
    sigaction(SIGUSR1, &sa, NULL);
    if (argc != 3 || atoi(argv[1]) <= 0)
        return (0);
    sendstr(atoi(argv[1]), argv[2]);
    return (0);
}
