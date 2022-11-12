/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:52:00 by sdukic            #+#    #+#             */
/*   Updated: 2022/11/12 21:21:19 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"
#include "libft/libft.h"
#include <signal.h>

static volatile int signalPid = -1;

void	handle_bin(int bin)
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
		ft_printf("%c", c);
		c = 0;
		bits = 0;
		kill(signalPid, SIGUSR1);
	}
	else
	{
		bits++;
	}
}

void	handle_sig(int signal, siginfo_t *info, void *context)
{
	signalPid = info->si_pid;
	(void)(context);

	if (signal == SIGUSR1)
	{
		handle_bin(1);
	}
	if (signal == SIGUSR2)
	{
		handle_bin(0);
	}
}

int	main(void)
{
	struct sigaction sa = { 0 };
	int	pid;

	pid = getpid();
	sa.sa_sigaction = &handle_sig;
	ft_printf("ServerID: %d\n", pid);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	return (0);
}
