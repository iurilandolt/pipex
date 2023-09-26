/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:44:04 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 13:54:49 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *str1, char const *str2);
void	*ft_calloc(size_t nitems, size_t size);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_join(char *buff1, char *buff2);
char	*ft_read(int fd, char *buffer);
char	*ft_getline(char *buffer);
char	*ft_getremain(char *buffer);
char	*get_next_line(int fd);

#endif
