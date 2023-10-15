/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlandolt <rlandolt@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:45:27 by rlandolt          #+#    #+#             */
/*   Updated: 2023/10/15 22:25:52 by rlandolt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

int	file_input(int argc, char **argv, int *filein, int *fileout)
{
	*fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*filein = open(argv[1], O_RDONLY, 0644);
	if (*filein == -1 || *fileout == -1)
		ft_error();
	dup2(*filein, STDIN_FILENO);
	return (2);
}

int	terminal_input(int argc, char **argv, int *fileout)
{
	*fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fileout == -1)
		ft_error();
	call_doc(argv);
	return (3);
}

int	main(int argc, char **argv, char **envp)
{
	int		filein;
	int		fileout;
	int		i;

	if (argc >= 5)
	{
		if (ft_strnstr(argv[1], "here_doc", 8) != 0 && argc > 5)
			i = terminal_input(argc, argv, &fileout);
		else
			i = file_input(argc, argv, &filein, &fileout);
		while (i < argc - 2)
			child(argv[i++], envp);
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
