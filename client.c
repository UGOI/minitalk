/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:39:39 by sdukic            #+#    #+#             */
/*   Updated: 2022/11/10 18:12:30 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"
#include "libft/libft.h"
#include <signal.h>

int	main(int argc, char *argv[])
{
	char	*serverid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("usage: client [serverid] [messsage]\n");
		return (0);
	}
	serverid = argv[1];
	message = argv[2];
	ft_printf("ServerID: %s\n", serverid);
	ft_printf("message: %s\n", message);
	return (0);
}
