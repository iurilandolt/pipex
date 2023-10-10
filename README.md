# pipex
https://chat.openai.com/share/b9b84508-050d-4bca-8094-de3b4a56978e
https://medium.com/@lannur-s/pipex-42-chapter-3-mastering-execve-using-fork-f93906a79d7c
https://github.com/gabcollet/pipex/blob/master/srcs/pipex.c
https://github.com/iurilandolt/pipex

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
		write(fileout, buffer, n);
	close(fileout);
	close(fd[0]);
	execute(argv[3], envp);
}
*/
