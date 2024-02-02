/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:16:55 by jsarda            #+#    #+#             */
/*   Updated: 2024/02/02 18:37:12 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define BUFFER_SIZE 100

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;
	static char	*str = NULL;
	static int	str_size = 0;
	static int	str_capacity = 0;

	(void)context;
	(void)info;
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
	kill(info->si_pid, SIGUSR2);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	while (argc == 1)
	{
		pause();
	}
	return (0);
}
