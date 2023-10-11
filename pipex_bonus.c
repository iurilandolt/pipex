/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:04:56 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/12 00:35:08 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

char	*find_path(char **envp, char *cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*program;

	i = 0;
	if (ft_strnstr(cmd, "/usr/bin/", 9) != 0)
		cmd = cmd + 9;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
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

void	execute(char *argv, char **envp)
{
	char **cmd;
	char *path;

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

void	child_process(char *argv, char **envp)
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
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(proc_id, NULL, 0);
	}
}

int main(int argc, char **argv, char **envp)
{
	int		filein;
	int		fileout;
	int		i;

	if (argc >= 5)
	{
		i = 2;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		filein = open(argv[1], O_RDONLY , 0644);
		if (filein == -1 || fileout == -1)
			ft_error();
		dup2(filein, STDIN_FILENO);
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	else
	{
		ft_putendl_fd("ambiguous redirect", 2);
		ft_putendl_fd("Try ./pipex file1 'cmd1' 'cmd2' file2", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

