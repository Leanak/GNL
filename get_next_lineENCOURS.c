/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:59:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/22 15:15:10 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean(char *stash)
{
	int		i;
	char	*new;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	new = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	return (free(stash), new);
}

char	*ft_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
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

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	res = 1;
	while ((ft_strchr(stash, '\n') == NULL) && res > 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res < 0)
			return (free(buffer), free(stash), NULL);
		buffer[res] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		/*if (res == 0)
		{
			free(buffer);
			if (stash && stash[0] != '\0')
				return (stash);
			return (free(stash), NULL);
		}*/
		if (!stash)
			return (free(buffer), free(tmp), NULL);
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = ft_fill(fd, stash);
	if (!stash || stash[0] == '\0')
		return (free(stash), stash = NULL, NULL);
	line = ft_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = ft_clean(stash);
	return (line);
}

/* int	main(void)
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
} */