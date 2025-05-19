/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:59:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/19 21:07:30 by lenakach         ###   ########.fr       */
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
	j = i;
	while (stash[i])
		i++;
	if (j == i)
		return (stash[0] = 0, stash);
	new = ft_substr(stash, j + 1, i);
	if (!new)
		return (free(stash), stash = 0, NULL);
	return (free(stash), stash = 0, new);
}

char	*ft_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
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
	int		res;

	if (!stash)
		return (NULL);
	res = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), NULL);
	while ((ft_strchr(stash, '\n') == NULL) && res > 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res < 0)
			return (free(buffer), free(stash), NULL);
		buffer[res] = '\0';
		if (res == 0 && *stash)
			return (free(buffer), stash);
		if (res == 0)
			return (free(buffer), free(stash), NULL);
		stash = ft_strjoin(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = ft_fill(fd, stash);
	if (!stash)
		return (free(stash), stash = NULL, NULL);
	line = ft_line(stash);
	if (!line)
		return (free (stash), stash = NULL, NULL);
	stash = ft_clean(stash);
	if (!stash)
		return (free(line), free(stash), NULL);
	if (stash && *stash == 0)
	{
		free(stash);
		stash = 0;
	}
	return (line);
}

// int	main(void)
// {
// 	int		file_fd;
// 	char	*line;

// 	file_fd = open("test.txt", O_RDONLY);
// 	if (file_fd == -1)
// 	{
// 		write(2, "Cannot read file.\n", 18);
// 		return (1);
// 	}
// 	line = get_next_line(file_fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(file_fd);
// 		if (line == NULL)
// 		{
// 			printf("%s", line);
// 			free(line);
// 			line = get_next_line(file_fd);
// 		}
// 	}
// 	close(file_fd);
// 	return (0);
// }
