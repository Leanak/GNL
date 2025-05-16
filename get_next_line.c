/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:59:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/16 19:18:11 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_delete(char *stash)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	while (stash[i])
	{
		stash[j] = stash[i + j];
		j++;
	}
	return (stash);
}

char	*ft_readstash(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_strdup("");
	while (stash[i])
	{
		while (stash[i] != '\n')
		{	
			line [i] = stash[i];
			i++;
		}
		line[i] = '\0';
		return (line);
	}
	return ("Erreur");
}


void	ft_get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;
	int			res;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(buffer), free(stash), stash = NULL));
	res = read(fd, buffer, BUFFER_SIZE);
	buffer[res] = '\0';
	if (!stash)
		stash = ft_strdup("");
	stash = ft_strjoin(stash, buffer);
	line = ft_readstash(stash);
	ft_putstr(line);
	ft_delete(stash);
}

int	main(void)
{
	int	file_fd;

	file_fd = open("text.txt", O_RDONLY);
	if (file_fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	ft_get_next_line(file_fd);
	close(file_fd);
	return (0);
}