/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:49:38 by blax              #+#    #+#             */
/*   Updated: 2023/09/21 15:15:30 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*fill_char_in_string(char c, char *string, int len_string)
{
	int	i;

	i = 0;
	while (i < len_string)
	{
		string[i] = c;
		i++;
	}
	string[i] = '\0';
	return (string);
}

void	stock_in_buffer(char **buffer, char char_buffer, \
	int *buffer_index, int *is_first)
{
	int	len_buffer;

	if (*buffer_index == 0 && !*is_first)
	{
		*buffer = malloc(sizeof(char) * 10);
		if (!*buffer)
			return ;
		*buffer = fill_char_in_string(';', *buffer, sizeof(*buffer));
	}
	if (char_buffer == ';' && *buffer_index <= 10 && !*is_first)
	{
		len_buffer = ft_atoi(*buffer);
		free(*buffer);
		*buffer = NULL;
		if (len_buffer < 0 || len_buffer > 1000000000)
			small_error("Size of the client string is invalid !\n");
		*buffer = malloc(sizeof(char) * (len_buffer + 1));
		if (!*buffer)
			return ;
		*buffer_index = -1;
		*is_first = 1;
	}
	else
		(*buffer)[*buffer_index] = char_buffer;
}

void	print_line(char **buffer, char char_buffer, \
	int *buffer_index, int *is_first)
{
	if (char_buffer == '\0')
	{
		write(1, *buffer, *buffer_index);
		free(*buffer);
		*buffer = NULL;
		*buffer_index = -1;
		*is_first = 0;
	}
}

static void	handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static char	*buffer;
	static int	buffer_index = 0;
	static int	bit_index = 0;
	static char	char_buffer = 0;
	static int	is_first = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		char_buffer = (char_buffer << 1) | 0;
	else if (sig == SIGUSR2)
		char_buffer = (char_buffer << 1) | 1;
	bit_index++;
	if (bit_index == 8)
	{
		stock_in_buffer(&buffer, char_buffer, &buffer_index, &is_first);
		print_line(&buffer, char_buffer, &buffer_index, &is_first);
		buffer_index++;
		bit_index = 0;
		char_buffer = 0;
	}
	if (kill(info->si_pid, SIGUSR1) < 0)
		ft_exit(&buffer);
}

int	main(void)
{
	struct sigaction	sa;
	char				*string_pid;
	pid_t				my_pid;

	my_pid = getpid();
	string_pid = ft_itoa(my_pid);
	if (string_pid == NULL)
		small_error("Memory for pid of malloc failed !\n");
	write(1, "PID du serveur : ", 18);
	write(1, string_pid, ft_strlen(string_pid));
	write(1, "\n", 1);
	free(string_pid);
	string_pid = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = &handle_sig;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
