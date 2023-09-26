/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:41:56 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 11:48:24 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	pos;

	pos = 0;
	while (*s++)
		pos++;
	return (pos);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((char *)str + i) = c;
		i++;
	}
	return (str);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*mblock;

	mblock = (void *)malloc(size * nitems);
	if (!mblock)
	{
		free(mblock);
		return (NULL);
	}
	ft_memset(mblock, 0, size * nitems);
	return (mblock);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;

	if (!str1 || !str2)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = -1;
	j = 0;
	while (*(str1 + ++i))
		*(dest + i) = *(str1 + i);
	while (str2[j])
		*(dest + i++) = *(str2 + j++);
	*(dest + i) = '\0';
	return (dest);
}
