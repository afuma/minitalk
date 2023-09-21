/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 19:38:09 by blax              #+#    #+#             */
/*   Updated: 2023/09/21 15:15:32 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	small_error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	ft_exit(char **buffer)
{
	free(*buffer);
	buffer = NULL;
	exit(1);
}
