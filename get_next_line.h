/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:36:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/16 18:56:28 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//Macro

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

//Inclusion des librairies

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>

//Utils
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, const char *src);
void	ft_putstr(char *s);

//GNL
void	ft_get_next_line(int fd);

#endif