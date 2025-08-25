/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:59:08 by fernafer          #+#    #+#             */
/*   Updated: 2025/08/26 00:24:07 by fernando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>

/* Use this pointer to storage the message*/
static char	*g_cli_str = NULL;

/* Function for managing memory in a safety way. */
char	*ft_realloc_str(char *old_str, int mssge_len)
{
	char	*new_str;

	new_str = (char *)malloc(mssge_len + 2);
	if (!new_str)
	{
		ft_printf("Error! Memory assignation failure.\n");
		exit (EXIT_FAILURE);
	}
	if (old_str)
	{
		ft_memcpy(new_str, old_str, mssge_len);
		free (old_str);
	}
	return (new_str);
}

/* Aux function for clean memory and printing. */
void	handle_message_end(char current_char, int *mssge_len)
{
	if (current_char == '\0')
	{
		ft_printf("%s\n", g_cli_str);
		free(g_cli_str);
		g_cli_str = NULL;
		*mssge_len = 0;
	}
	else
	{
		g_cli_str = ft_realloc_str(g_cli_str, *mssge_len);
		g_cli_str[*mssge_len] = current_char;
		g_cli_str[*mssge_len + 1] = '\0';
		(*mssge_len)++;
	}
}

/* Decodes the bit. SIGUSR2 is '1' and SIGUSR1 is '0'. */
void	signal_handler(int signum)
{
	static char	current_char;
	static int	bit_count;
	static int	mssge_len;

	if (signum == SIGUSR2)
		current_char |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		handle_message_end(current_char, &mssge_len);
		current_char = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf ("Server PID: %d\n", getpid());
	g_cli_str = NULL;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sleep(1);
	while (1)
		pause();
	return (0);
}
