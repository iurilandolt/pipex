/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:13:45 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/17 16:19:06 by rlandolt         ###   ########.fr       */
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

void	close_and_send(int *id, int *fd)
{
	waitpid(*id, NULL, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
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
		close_and_send(&proc_id, fd);
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
			ft_putstr_fd(line, fd[1]);
			if (ft_strnstr(line, argv[2], ft_strlen(line)) != 0)
				exit(0);
			free(line);
		}
	}
	else
		close_and_send(&proc_id, fd);
}
