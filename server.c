/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:52:00 by sdukic            #+#    #+#             */
/*   Updated: 2022/11/13 00:41:44 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"
#include "libft/libft.h"
#include <signal.h>

void	recive_ack(char *c, int pid)
{
	static int	end;

	if (*c)
		end = 1;
	else
	{
		if (end == 1)
			kill(pid, SIGUSR2);
		end = 0;
	}
}

void	handle_bin(int bin, int pid)
{
	static unsigned int	bits;
	static char			c;

	if (!c)
		c = 0;
	c *= 2;
	if (bin)
		c += 1;
	if (bits == 7)
	{
		write(1, &c, 1);
		recive_ack(&c, pid);
		c = 0;
		bits = 0;
		kill(pid, SIGUSR1);
	}
	else
		bits++;
}

void	handle_sig(int signal, siginfo_t *info, void *context)
{
	(void)(context);
	if (signal == SIGUSR1)
	{
		handle_bin(1, info->si_pid);
	}
	if (signal == SIGUSR2)
	{
		handle_bin(0, info->si_pid);
	}
}

int	main(void)
{
	struct sigaction sa;
	int		pid;

	pid = getpid();
	sa.sa_sigaction = &handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("ServerID: %d\n", pid);
	while (1)
		pause();
	return (0);
}
