/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:23:06 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/19 00:43:34 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

/* Global static volatile for confirmation.(ACK) */
static volatile int	g_ack = 0;

/* Signal handler for client. It's activate when server sent confirmation.*/
void	client_handler(int signum)
{
	(void)signum;
	g_ack = 1;
}

/* Send only a bit and wait for confirmation. */
void	send_bit(int pid, int bit)
{
	g_ack = 0;
	if (bit)
	{
		if (kill(pid, SIGUSR2) == -1)
		{
			ft_printf("Error! Failed to send signal to PID %d\n", pid);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
		{
			ft_printf("Error! Failed to send signal to PID %d\n", pid);
			exit(EXIT_FAILURE);			
		}
	}
	// Wait for confirmation signal
	while (g_ack == 0)
		pause();
}


/* Fuction for send a character bit to bit. SIGUSR1 = 0, SIGUSR2 = 1. */
void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_bit(pid, (c >> i) & 1);
		i++;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;
	int		pid_server;
	char	*message;

	if (ac != 3)
	{
		ft_printf("Error! Uso: ./client <PID server> <message>\n");
		exit(EXIT_FAILURE);
	}
	// Configurates signal handler.
	sa.sa_handler = client_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	pid_server = ft_atoi(av[1]);
	message = av[2];
	usleep(100);
	while (*message)
	{
		send_char(pid_server, *message);
		message++;
	}
	send_char (pid_server, '\0');
	while (g_ack == 0)
	{
		pause();
	}
	ft_printf("Message sent succesfully!!\n");
	return (EXIT_SUCCESS);
}
