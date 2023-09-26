/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:43:47 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 11:51:41 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

char	*ft_join(char *buff1, char *buff2)
{
	char	*temp;

	temp = ft_strjoin(buff1, buff2);
	free(buff1);
	return (temp);
}

char	*ft_read(int fd, char *buffer)
{
	char	*temp;
	int		rlen;

	temp = ft_calloc(BUFFER_SIZE + 1, 1);
	rlen = read(fd, temp, BUFFER_SIZE);
	while (rlen > 0)
	{
		if (!buffer)
			buffer = ft_calloc(1, 1);
		*(temp + rlen) = '\0';
		buffer = ft_join(buffer, temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		rlen = read(fd, temp, BUFFER_SIZE);
	}
	free (temp);
	if (rlen < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*ft_getline(char *buffer)
{
	char	*line;
	int		i;
	int		term;

	i = 0;
	term = 1;
	if (!*(buffer + i))
		return (NULL);
	while (*(buffer + i) && *(buffer + i) != '\n')
		i++;
	if (*(buffer + i) == '\n')
		term = 2;
	line = ft_calloc(i + term, 1);
	i = 0;
	while (*(buffer + i) && *(buffer + i) != '\n')
	{
		*(line + i) = *(buffer + i);
		i++;
	}
	if (*(buffer + i) && *(buffer + i) == '\n')
		*(line + i) = '\n';
	return (line);
}

char	*ft_getremain(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (*(buffer + i) && *(buffer + i) != '\n')
		i++;
	if (!*(buffer + i))
	{
		free (buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	i++;
	j = 0;
	while (*(buffer + i))
		*(line + j++) = *(buffer + i++);
	free (buffer);
	*(line + j + 1) = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_getline(buffer[fd]);
	buffer[fd] = ft_getremain(buffer[fd]);
	return (line);
}
