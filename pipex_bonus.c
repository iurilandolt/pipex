/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:04:56 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/11 20:56:54 by rlandolt         ###   ########.fr       */
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
		ft_error();
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		clear(cmd);
		ft_error();
	}
}

t_pipe_node *build_pipe(void)
{
	t_pipe_node *new;

	new = (t_pipe_node *)malloc(sizeof(t_pipe_node));
	if (!new)
		exit(0);
	return (new);
}

t_pipe_node *pipeline(int argc)
{
	t_pipe_node *first;
	t_pipe_node *new;
	t_pipe_node *last;
	int i;

	i = 0;
	while (i < argc - 3)
	{
		if (i == 0)
		{
			first = build_pipe();
			last = first;
		}
		else
		{
			new = build_pipe();
			last->next = new;
			last = new;
		}
	}
	return(new);
}

int main(int argc, char **argv, char **envp)
{
	t_pipe_node *pipe;
	(void)argv;
	(void)envp;

	if (argc >= 5)
	{
		pipe = pipeline(argc);

	}
	else
		ft_putendl_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	return (0);
}


/*
int main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		infile;
	int		outfile;
	int		i;
	pid_t	proc_id;


	if (argc >= 5)
	{
		infile = open(argv[1], O_RDONLY);
		outfile = open(argv[argc - 1], O_WRONLY, O_CREAT, 0644);
		if (infile == -1 || outfile == -1)
			ft_error();
		i = 2;
		dup2(infile, STDIN_FILENO);
		close(infile);
		while (i < argc - 1)
		{
			if (pipe(fd) == -1)
				ft_error();
			proc_id = fork();
			if (proc_id == -1)
				ft_error();
			if (proc_id == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				execute(argv[i], envp);
			}
			if (waitpid(proc_id, NULL, 0) == -1)
				ft_error();
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			i++;
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
		execute(argv[i], envp);
	}
	else
		ft_putendl_fd("\033[31mError: Bad arguments\n\e[0m", 2);
	return (0);
}
*/
