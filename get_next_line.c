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
	int		readd;

	if (!buffer || !*buffer)
		buffer = ft_strdup("");
	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	temp[0] = '\0';
	readd = 1;
	while (readd > 0 && !ft_strchr(temp, '\n'))
	{
		readd = read(fd, temp, BUFFER_SIZE);
		if (readd < 0)
			return (free(temp), free(buffer), NULL);
		temp[readd] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	if (temp)
		free(temp);
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
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	temp = ft_substr(buffer, i, ft_strlen(buffer) - i);
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_next(buffer);
	return (line);
}
