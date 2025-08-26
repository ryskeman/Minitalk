/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:23:06 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/26 21:15:47 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

/* Fuction for send a character bit to bit. */
void	send_char(int pid, char c)
{
	int	bit;
	int	result;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit & 1) == 1)
			result = kill(pid, SIGUSR1);
		else
			result = kill(pid, SIGUSR2);
		if (result == -1)
		{
			ft_printf("Error! Failed to send signal to %d PID\n", pid);
			exit(EXIT_FAILURE);
		}
		usleep(100);
		bit++;
	}
}

// int	main(int ac, char **av)
// {
// 	int		pid_server;
// 	char	*message;

// 	if (ac != 3)
// 	{
// 		ft_printf("Error! Uso: ./client <PID server> <message>\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid_server = ft_atoi(av[1]);
// 	message = av[2];
// 	while (*message)
// 	{
// 		send_char(pid_server, *message);
// 		message++;
// 	}
// 	send_char (pid_server, '\0');
// 	ft_printf("Message sent succesfully!!\n");
// 	return (EXIT_SUCCESS);
// }

int	main(int ac, char **av)
{
	int					pid;
	int					i;
	struct sigaction	sa;

	if (ac == 3)
	{
		sa.sa_handler = sig_cli_handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		i = 0;
		pid = ft_atoi(av[1]);
		while (av[2][i] != '\0')
			send_char(pid, av[2][i++]);
		send_char(pid, '\0');
		ft_printf("Message sent succesfully!!\n");
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_printf("Error! Use: ./client <PID server> <message>\n");
		exit(EXIT_FAILURE);
	}
}