/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 23:47:09 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/27 17:26:18 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

/* Static variable for handling signal confirmation. */
static volatile int	g_signal_ack = 0;

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
		usleep(1000);
		while (g_signal_ack == 0)
			pause();
		g_signal_ack = 0;
		bit++;
	}
}

void	sig_cli_handler(int signal)
{
	if (signal == SIGUSR1)
	{
		g_signal_ack = 1;
	}
	else if (signal == SIGUSR2)
	{
		ft_printf("Message sent successfully!!\n");
		exit(EXIT_SUCCESS);
	}
}

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
	}
	else
	{
		ft_printf("Error! Use: ./client <PID server> <message>\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
