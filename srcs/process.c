/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:13:45 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/15 23:11:23 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_error();
	path = find_path(envp, *cmd);
	if (!path)
		path_error(argv);
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		clear(cmd);
		ft_error();
	}
}

void	child(char *argv, char **envp)
{
	int		fd[2];
	pid_t	proc_id;

	if (pipe(fd) == -1)
		ft_error();
	proc_id = fork();
	if (proc_id == -1)
		ft_error();
	if (proc_id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		waitpid(proc_id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	get_line(char **line)
{
	int		i;
	int		b_read;
	char	*buffer;

	i = 0;
	buffer = (char *)malloc(1024 * sizeof(char));
	b_read = read(0, buffer + i, 1);
	while (b_read > 0)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
			break ;
		i++;
		b_read = read(0, buffer + i, 1);
	}
	if (b_read > 0)
	{
		buffer[i + 1] = '\0';
		*line = buffer;
	}
	return (b_read);
}

void	call_doc(char **argv)
{
	pid_t	proc_id;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		ft_error();
	proc_id = fork();
	if (proc_id == -1)
		ft_error();
	if (proc_id == 0)
	{
		while (get_line(&line) > 0)
		{
			if (ft_strnstr(line, argv[2], ft_strlen(line)) != 0)
				exit(0);
			ft_putstr_fd(line, fd[1]);
		}
	}
	else
	{
		waitpid(proc_id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}
