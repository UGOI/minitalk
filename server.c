/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:52:00 by sdukic            #+#    #+#             */
/*   Updated: 2022/11/10 18:39:26 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"
#include "libft/libft.h"

void	handle_signal(int signal)
{
	ft_printf("Received Signal\n");
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("ServerID: %d\n", pid);
	return (0);
}
