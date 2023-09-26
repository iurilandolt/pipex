/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:38:41 by rlandolt          #+#    #+#             */
/*   Updated: 2023/09/26 16:35:05 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	(void)envp;
	(void)argv;
	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("Error:");
			exit(1);
		}

		pid1 = fork();
		if (pid1 < 0)
		{
			perror("Error:");
			exit(1);
		}

		if (pid1 == 0)
			printf("Hello from the child process!\n");
			//wait for child proc end
			//start parent proc
		else
		{
			printf("Hello from the parent process!\n");
		}
	}
	return (0);
}

/*
	(void)argc;
	(void)argv;
	for (int i = 0; envp[i] != NULL; i++)
	{
		printf("%s\n", envp[i]);
	}
*/
