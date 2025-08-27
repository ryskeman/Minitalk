/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 23:57:01 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/27 17:26:22 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

/* Use this pointer to storage the message*/
static char	*g_cli_str = NULL;

/* Function for managing memory exponencilly in a safety way. */
void	malloc_exp(char c)
{
	char	*new;
	char	str[2];
	char	*old_str;

	str[0] = c;
	str[1] = '\0';
	if (!g_cli_str)
		g_cli_str = ft_strdup("");
	if (!g_cli_str)
	{
		ft_printf("Error! Memory assignation failure.\n");
		exit(EXIT_FAILURE);
	}
	old_str = g_cli_str;
	new = ft_strjoin(g_cli_str, str);
	if (!new)
	{
		ft_printf("Error! Memory assignation failure.\n");
		exit(EXIT_FAILURE);
	}
	g_cli_str = new;
	free(old_str);
}

/* Aux function for clean memory and printing. */
void	handle_str_end(pid_t pid_client, char c)
{
	if (c == '\0')
	{
		if (g_cli_str)
		{
			ft_printf("%s\n", g_cli_str);
			free(g_cli_str);
			g_cli_str = NULL;
		}
		if (kill(pid_client, SIGUSR2) == -1)
		{
			ft_printf("Error! Comunication failed. Signal:_SIGUSR2\n");
			exit(EXIT_FAILURE);
		}
		return ;
	}
	malloc_exp(c);
}

/* Decodes the bit. SIGUSR2 is '1' and SIGUSR1 is '0'. */
void	sig_server_handler(int signal, siginfo_t *info, void *context)
{
	static char		c;
	static int		bit;
	static pid_t	pid_client;

	(void)context;
	if (info->si_pid != 0)
		pid_client = info->si_pid;
	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		bit = 0;
		handle_str_end(pid_client, c);
		c = 0;
	}
	if (kill(pid_client, SIGUSR1) == -1)
	{
		ft_printf("Error! Comunitacion failed. Signal:_SIGUSR1\n");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	sa.sa_sigaction = sig_server_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sleep(1);
	while (1)
		pause();
	return (0);
}
