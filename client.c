/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:23:06 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/17 23:15:15 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

/* Fuction for send a character bit to bit. SIGUSR1 = 0, SIGUSR2 = 1. */
void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill (pid, SIGUSR2) == -1)
			{
				ft_printf("Error! Failed to send signal to %d PID.\n", pid);
				exit (EXIT_FAILURE);
			}
		}
		else
		{
			if (kill (pid, SIGUSR1) == -1)
			{
				ft_printf("Error! Failed to send signal to %d PID.\n", pid);
				exit (EXIT_FAILURE);
			}
		}
		bit++;
		usleep(1000);
	}
}

int	main(int ac, char **av)
{
	int		pid_server;
	char	*message;

	if (ac != 3)
	{
		ft_printf("Error! Uso: ./client <PID server> <message>\n");
		exit(EXIT_FAILURE);
	}
	pid_server = ft_atoi(av[1]);
	message = av[2];
	while (*message)
	{
		send_char(pid_server, *message);
		message++;
	}
	send_char (pid_server, '\0');
	ft_printf("Message sent succesfully!!\n");
	return (EXIT_SUCCESS);
}
