/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:59:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/19 13:33:47 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean(char *stash)
{
	int		i;
	int		j;
	char	*new;


	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new = malloc((ft_strlen(stash) - i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	j = 0;
	while (stash[i])
		new[j++] = stash[i++];
	new[j] = '\0';
	free(stash);
	return (new);
}

char	*ft_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_fill(int fd, char *stash)
{
	char	*buffer;
	char	*tmp;
	int		res;

	res = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n') && res > 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res < 0)
			return (free(buffer), NULL);
		buffer[res] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (free(buffer), free(tmp), tmp = NULL);
		stash = tmp;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = ft_fill(fd, stash);
	if (!stash)
		return (free(stash), stash = NULL, NULL);
	line = ft_line(stash);
	if (!line)
		return (free (stash), stash = NULL, NULL);
	stash = ft_clean(stash);
	return (line);
}

int	main(void)
{
	int		file_fd;
	char	*line;

	file_fd = open("test.txt", O_RDONLY);
	if (file_fd == -1)
	{
		write(2, "Cannot read file.\n", 18);
		return (1);
	}
	line = get_next_line(file_fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(file_fd);
	}
	close(file_fd);
	return (0);
}
