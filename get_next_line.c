/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdalmaz <bdalmaz@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-09-08 17:35:25 by bdalmaz           #+#    #+#             */
/*   Updated: 2025-09-08 17:35:25 by bdalmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *buffer)
{
	char	*temp;
	size_t	readd;

	if (!buffer || !*buffer)
	{
		buffer = malloc(sizeof(char) + 1);
		buffer[0] = '\0';
	}
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	readd = 1;
	while (readd > 0 && !ft_strchr(temp, '\n'))
	{
		readd = read(fd, temp, BUFFER_SIZE);
		temp[readd] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	return (buffer);
}

char	*ft_get_line(char *buffer)
{
	int		i;
	char	*temp;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	temp = ft_substr(buffer, 0, i);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	char	*temp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	temp = ft_substr(buffer, i, ft_strlen(buffer) - i);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	buffer = ft_read_file(fd, buffer);
	line = ft_get_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text", O_RDONLY, 0777);
	line = "";
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
}
