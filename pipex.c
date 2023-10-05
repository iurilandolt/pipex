/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:38:41 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/05 13:47:38 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	check_fpermission(const char *filepath)
{
	if (access(filepath, R_OK) != -1) // check READ permission.
		return (1);
	else
		return (0);
}




int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	int i;
	int j;
	char **paths;

	i = 0;
	j = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	printf("this is the path string:\n%s\n", envp[i]);
	paths = ft_split(envp[i], ':');
	printf("these are the splited strings:\n");
	while (*(paths + j))
	{
		printf("%s\n", *(paths + j));
		j++;
	}
	clean(paths, j);
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
