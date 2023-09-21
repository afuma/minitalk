/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 09:12:18 by blax              #+#    #+#             */
/*   Updated: 2023/09/21 14:34:05 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

size_t	ft_strlen(const char *s);
void	small_error(char *msg);
void	ft_exit(char **buffer);
char	*ft_itoa(int n);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		ft_atoi_pid(const char *str);

#endif
