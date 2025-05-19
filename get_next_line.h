/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:36:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/19 19:45:01 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

//Inclusion des librairies

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <fcntl.h>

//Macro

# ifndef BUFFER_SIZE
#	define BUFFER_SIZE 10
# endif

//Utils
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, const char *src);
void	ft_putstr(char *s);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);

//GNL
char	*get_next_line(int fd);

#endif