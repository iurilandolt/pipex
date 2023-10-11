/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:38:04 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/11 20:40:22 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipe_node {
	int			fd[2];
	pid_t		p_id;
	t_pipe_node *next;
}	t_pipe_node;

////// STRINGS //////

char	**ft_split(const char *str, char c);
void	*clear(char **array);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *str1, char const *str2);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);

////// ERRORS //////

void	ft_putendl_fd(char *str, int fd);
void	ft_error(void);
void	path_error(char *str);

#endif
