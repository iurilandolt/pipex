/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:25:13 by rlandolt          #+#    #+#             */
/*   Updated: 2024/02/19 11:54:26 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	validate_path(char **paths, char **cmd)
{
	int		i;
	char	*ptr;

	i = 0;
	while (*(paths + i))
	{
		if (ft_strnstr(*cmd, *(paths + i), ft_strlen(*(paths + i))) != 0)
		{
			ptr = *cmd;
			while (*ptr)
			{
				if (*ptr == '/')
					*cmd = ptr + 1;
				ptr++;
			}
			return ;
		}
		i++;
	}
	return ;
}

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*program;

	i = 0;

	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	validate_path(paths, &cmd);
	i = 0;
	while (*(paths + i))
	{
		path = ft_strjoin(paths[i], "/");
		program = ft_strjoin(path, cmd);
		free(path);
		if (access(program, F_OK | X_OK) == 0)
		{
			clear(paths);
			return (program);
		}
		free(program);
		i++;
	}
	return (clear(paths));
}
