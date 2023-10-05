/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:38:41 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/05 15:46:23 by rlandolt         ###   ########.fr       */
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
			printf("%s\n", program);
			clear(paths);
			return (program);
		}
		free(program);
		i++;
	}
	return (clear(paths));
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	char *cmd;
	char *path;

	cmd = argv[1];
	path = find_path(envp, cmd);
	execve(path, &cmd, envp);
	free(path);
	return (0);
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
