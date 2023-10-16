/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:38:04 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/16 15:23:11 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

////// STRINGS //////

char	**ft_split(const char *str, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *str1, char const *str2);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		get_line(char **line);
void	*clear(char **array);

////// ERROR //////

void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_error(void);
void	path_error(char *str);

////// PATH //////

char	*find_path(char **envp, char *cmd);
void	validate_path(char **paths, char **cmd);

///// PROCESS /////

void	execute(char *argv, char **envp);
void	child(char *argv, char **envp);
int		get_line(char **line);
void	call_doc(char **argv);

#endif
