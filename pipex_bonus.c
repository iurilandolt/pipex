/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:04:56 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/10 17:41:09 by rlandolt         ###   ########.fr       */
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
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (*(paths + i))
	{
		path = ft_strjoin(paths[i], "/");
		program = ft_strjoin(path, cmd);
		free(path);
		if (access(program, F_OK) == 0)
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
		ft_error();
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		clear(cmd);
		ft_error();
	}
}

void	child_proc(int *fd, char *argv, char **envp)
{
	int		filein;

	filein = open(argv, O_RDONLY);
	if (filein == -1)
		ft_error();
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	dup2(filein, STDIN_FILENO);
	//close(filein);
	execute(argv, envp);
}

void parent_proc(int *fd, char *argv, char**envp)
{
	int		fileout;

	fileout = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		ft_error();
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	execute(argv, envp);
}

int main(int argc, char **argv, char **envp)
{
	int fd[2];
	int argument;
	int proc_id;

	argument = 2;
	if (argc >= 5)
	{
		while (argument < argc - 3)
		{
			if (pipe(fd) == -1)
				ft_error();
			proc_id = fork();
			if (proc_id == -1)
				ft_error();
			if (proc_id == 0)
				child_proc(fd, argv[argument], envp);
			if (waitpid(proc_id, NULL, 0) == -1)
				ft_error();
			parent_proc(fd, argv[argument + 1], envp);
			argument++;
		}
	}
	else
		ft_putendl_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	return (0);
}
