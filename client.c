/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:39 by sdukic            #+#    #+#             */
/*   Updated: 2022/11/12 21:48:46 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"
#include "libft/libft.h"
#include <signal.h>

int	g_ack;

void	handle_sig(int signal, siginfo_t *info, void *context)
{
	(void)(info);
	(void)(context);
	if (signal == SIGUSR1)
	{
		g_ack = 1;
	}
}

void	send_message(int serverid, char *message)
{
	int				sig;
	unsigned int	shift;
	struct sigaction sa = { 0 };

	sa.sa_sigaction = &handle_sig;
	while (!g_ack)
	{
		sigaction(SIGUSR1, &sa, NULL);
		kill(serverid, SIGUSR2);
		usleep(200);
	}
	while (*message)
	{
		shift = 8;
		while (shift)
		{
			sig = (*message & (1 << --shift)) != 0;
			kill(serverid, sig ? SIGUSR1 : SIGUSR2);
			usleep(200);
		}
		message++;
	}
}

int	main(int argc, char *argv[])
{
	int		serverid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("usage: client [serverid] [messsage]\n");
		return (0);
	}
	serverid = ft_atoi((const char*) argv[1]);
	message = argv[2];
	send_message(serverid, message);
	return (0);
}
