/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:59:51 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/21 17:44:42 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_clean(char *stash)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	j = i;
	while (stash[i])
		i++;
	if (j == i)
		return (stash[0] = 0, stash);
	new = ft_substr(stash, j + 1, i);
	if (!new)
		return (free(stash), NULL);
	return (free(stash), new);
}

char	*ft_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	if (!stash || !*stash)
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
	int		res;

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
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	stash[fd] = ft_fill(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = ft_line(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	stash[fd] = ft_clean(stash[fd]);
	if (!stash[fd])
		return (free(line), NULL);
	return (line);
}

/*  int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt",O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		write(2, "Cannot read one of the files.\n", 30);
		if (fd1 != -1)
			close(fd1);
		if (fd2 != -1)
			close(fd2);
		return (1);
	}

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		if (!line1 && !line2)
			break ;
		if (line1)
		{
			printf("%s\n", line1);
			free(line1);
		}
		if (line2)
		{
			printf("%s\n", line2);
			free(line1);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
} */

int main(void)
{
	int		fd1, fd2;
	char	*line1, *line2;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		write(2, "Cannot open one of the files.\n", 30);
		if (fd1 != -1)
			close(fd1);
		if (fd2 != -1)
			close(fd2);
		return (1);
	}

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);

		if (!line1 && !line2)
			break ;

		if (line1)
		{
			printf("[FD1] %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("[FD2] %s", line2);
			free(line2);
		}
	}

	close(fd1);
	close(fd2);
	return (0);
}