/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:16:55 by jsarda            #+#    #+#             */
/*   Updated: 2024/01/31 14:53:30 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define BUFFER_SIZE 100

void	sig_handler(int sig)
{
	static int	bit;
	static int	i;
	static char	*str = NULL;
	static int	str_size = 0;
	static int	str_capacity = 0;

	if (sig == SIGUSR1)
		i |= (0b00000001 << bit);
	bit++;
	if (bit == 8)
	{
		if (str_size == str_capacity)
		{
			str_capacity += BUFFER_SIZE;
			str = realloc(str, str_capacity);
			if (!str)
			{
				free(str);
				exit(EXIT_FAILURE);
			}
		}
		str[str_size] = i;
		str_size++;
		bit = 0;
		i = 0;
	}
	if (str_size > 0 && str[str_size - 1] == '\0')
	{
		ft_printf("%s", str);
		free(str);
		str = NULL;
		str_size = 0;
		str_capacity = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong number of arguments.\033[0m\n");
		ft_printf("\033[32mOnly: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[32mPID\033[0m \033[32m->\033[32m %d\n", pid);
	ft_printf("\033[96mWaiting for a message...\033[96m\n");
	while (argc == 1)
	{
		signal(SIGUSR1, sig_handler);
		signal(SIGUSR2, sig_handler);
		pause();
	}
	return (0);
}
