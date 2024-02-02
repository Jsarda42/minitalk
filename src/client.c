/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:17:02 by jsarda            #+#    #+#             */
/*   Updated: 2024/02/02 18:37:19 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int			received = 0;

static void	ft_confirm(int signal)
{
	if (signal == SIGUSR2)
	{
		received = 1;
	}
}

#include <stdio.h>

void	send_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		received = 0;
		if ((c & (0b00000001 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (received == 0)
			usleep(100);
		fflush(stdout);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	printf("%d", getpid());
	fflush(stdout);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		signal(SIGUSR2, ft_confirm);
		while (argv[2][i])
		{
			send_bits(pid, argv[2][i]);
			i++;
		}
		send_bits(pid, '\0');
		send_bits(pid, '\n');
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[32mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
}
