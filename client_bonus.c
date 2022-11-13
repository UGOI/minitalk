/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:39 by sdukic            #+#    #+#             */
/*   Updated: 2022/11/13 00:39:44 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"
#include "libft/libft.h"
#include <signal.h>

int	g_ack;

void	handle_sig(int signal)
{
	if (signal == SIGUSR1)
	{
		g_ack = 1;
	}
	else if (signal == SIGUSR2)
		ft_printf("Message Received!\n");
}

void	send_zero(int serverid)
{
	while (!g_ack)
	{
		kill(serverid, SIGUSR2);
		usleep(100);
	}
}

void	send_message(int serverid, char *message)
{
	int					sig;
	unsigned int		shift;

	send_zero(serverid);
	while (*message)
	{
		shift = 8;
		while (shift)
		{
			sig = (*message & (1 << --shift)) != 0;
			if (sig)
				kill(serverid, SIGUSR1);
			else
				kill(serverid, SIGUSR2);
			usleep(100);
		}
		message++;
	}
	shift = 8;
	while (shift--)
	{
		kill(serverid, SIGUSR2);
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	int		serverid;
	char	*message;

	signal(SIGUSR1, &handle_sig);
	signal(SIGUSR2, &handle_sig);
	if (argc != 3)
	{
		ft_printf("usage: client [serverid] [messsage]\n");
		return (0);
	}
	serverid = ft_atoi((const char *) argv[1]);
	message = argv[2];
	send_message(serverid, message);
	return (0);
}
