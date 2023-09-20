/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:49:38 by blax              #+#    #+#             */
/*   Updated: 2023/09/20 20:01:11 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

volatile size_t	g_bit_received;

bool	send_char(char c, int server_pid)
{
	int	i;
	int	bit;

	i = 7;
	while (i >= 0)
	{
		g_bit_received = 0;
		bit = (c >> i) & 1;
		if (bit == 0)
		{
			if (kill(server_pid, SIGUSR1) < 0)
				return (false);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) < 0)
				return (false);
		}
		while (g_bit_received == 0)
		{
		}
		i--;
	}
	return (true);
}

void	handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)info;
	if (sig == SIGUSR1)
		g_bit_received++;
}

void	send_total_len_buffer(int len_string, int server_pid)
{
	char	*char_len_string;
	int		total_len_buffer;
	int		i;

	i = 0;
	char_len_string = ft_itoa(len_string);
	if (!char_len_string)
		exit(1);
	total_len_buffer = ft_strlen(char_len_string);
	while (i < total_len_buffer)
	{
		if (!send_char(char_len_string[i], server_pid))
		{
			free(char_len_string);
			write(1, "Error: client can't send char to server !\n", 43);
			exit(1);
		}
		i++;
	}
	send_char(';', server_pid);
	free(char_len_string);
	char_len_string = NULL;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				*string;
	int					server_pid;
	int					len_string;
	int					i;

	if (argc != 3)
		return (0);
	i = 0;
	server_pid = ft_atoi_pid(argv[1]);
	if (server_pid == -1)
		exit_client();
	string = argv[2];
	len_string = ft_strlen(string);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = &handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	send_total_len_buffer(len_string, server_pid);
	while (i < len_string)
	{
		send_char(string[i], server_pid);
		i++;
	}
	send_char('\0', server_pid);
}
