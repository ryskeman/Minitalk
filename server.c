/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:59:08 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/26 23:22:45 by fernando         ###   ########.fr       */
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
void	handle_str_end(char c)
{
	if (c == '\0')
	{
		ft_printf("%s\n", g_cli_str);
		free(g_cli_str);
		g_cli_str = NULL;
	}
	else
		malloc_exp(c);
}

/* Decodes the bit. SIGUSR2 is '1' and SIGUSR1 is '0'. */
void	sig_server_handler(int signal)
{
	static char	c;
	static int	bit;

	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		handle_str_end(c);
		c = 0;
		bit = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf ("Server PID: %d\n", getpid());
	g_cli_str = NULL;
	sa.sa_handler = sig_server_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sleep(1);
	while (1)
		pause();
	return (0);
}
