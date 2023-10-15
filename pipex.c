/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:45:27 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/15 21:40:43 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

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
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(proc_id, NULL, 0);
	}
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
			write(fd[1], line, ft_strlen(line));	//mby use fd_putstr?
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	pipe_sequence(int argc, char **argv, char **envp)
{
	int		filein;
	int		fileout;
	int		i;

	if (ft_strnstr(argv[1], "here_doc", 8) != 0 && argc > 5)
	{
		i = 3;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fileout == -1)
			ft_error();
		call_doc(argv); // i = call doc return int
	}
	else
	{
		i = 2;
		fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		filein = open(argv[1], O_RDONLY , 0644);
		if (filein == -1 || fileout == -1)
			ft_error();
		dup2(filein, STDIN_FILENO);
		// i = call parent return int
	}
	while (i < argc - 2)
		child(argv[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}

int main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		pipe_sequence(argc, argv, envp);
	else
	{
		ft_putendl_fd("ambiguous redirect", 2);
		ft_putendl_fd("Try ./pipex file1 'cmd1' 'cmd2' file2", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}

