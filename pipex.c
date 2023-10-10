/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:38:41 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/10 11:19:18 by rlandolt         ###   ########.fr       */
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
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i], ':');
	i = 0;
	while (*(paths + i))
	{
		path = ft_strjoin(paths[i], "/");
		program = ft_strjoin(path, cmd);
		free(path);
		if (access(program, F_OK) == 0)
		{
			printf("cmd found at: %s\n", program);
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
		return ;
	path = find_path(envp, *cmd);
	execve(path, cmd, envp);
	free(path);
	clear(cmd);
}

void	child_proc(int *fd, char **argv, char **envp)
{
	int		filein;
	char	buffer[BUFFER_SIZE];
	int		n;

	filein = open(argv[1], O_RDONLY);
	if (filein == -1)
		ft_error();
	close(fd[0]);
	while ((n = read(filein, buffer, BUFFER_SIZE)) > 0)
		write(fd[1], buffer, n);
	close(filein);
	close(fd[1]);
	execute(argv[2], envp);
}

void parent_proc(int *fd, char **argv, char**envp)
{
	int		fileout;
	char	buffer[BUFFER_SIZE];
	int		n;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		ft_error();
	close(fd[1]);
	while ((n = read(fd[0], buffer, BUFFER_SIZE)) > 0)
		write(fileout, buffer, BUFFER_SIZE);
	close(fileout);
	close(fd[0]);
	execute(argv[3], envp);
}


int main(int argc, char **argv, char **envp)
{
	int	fd[2];
	pid_t proc_id;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return (1);
		proc_id = fork();
		if (proc_id == 0)
			child_proc(fd, argv, envp);
		waitpid(proc_id, NULL, 0);
		parent_proc(fd, argv, envp);
	}
	else
		ft_error();
}


/*


	void forkexample()
{
    int x = 1;

    if (fork() == 0)
        printf("Child has x = %d\n", ++x);
    else
        printf("Parent has x = %d\n", --x);
}
int main()
{
    forkexample();
    return 0;
}

	(void)argc;
	(void)argv;
	for (int i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}

	void	child_proc(char ** argv, char **envp, int *fd)
{
	int filein;

	filein = open(argv[1], O_RDONLY, 0551);
	if (filein == -1)
	{
		perror("Error:");
		exit(1);
	}
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[0]);
	//execute
}
*/
