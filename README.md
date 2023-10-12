# pipex
https://chat.openai.com/share/b9b84508-050d-4bca-8094-de3b4a56978e
https://medium.com/@lannur-s/pipex-42-chapter-3-mastering-execve-using-fork-f93906a79d7c
https://github.com/gabcollet/pipex/blob/master/srcs/pipex.c
https://github.com/iurilandolt/pipex
https://github.com/mariadaan/PIPEXaminator

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

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}


#include <unistd.h>
#include <fcntl.h>

void execute_cmd(char *cmd, char **envp) {
    char *argv[] = { "/bin/sh", "-c", cmd, NULL };
    execve(argv[0], argv, envp);
}

int main(int argc, char **argv, char **envp) {
    int fd[2], f_in, f_out, pid, i = 2;
    f_in = open(argv[1], O_RDONLY); f_out = open(argv[argc-1], O_WRONLY | O_CREAT, 0644);
    dup2(f_in, 0); close(f_in); // Redirect stdin to infile
    while (i < argc - 1) {
        pipe(fd);
        if ((pid = fork()) == 0) {
            dup2(fd[1], 1); close(fd[0]); execute_cmd(argv[i], envp); }
        else { wait(NULL); close(fd[1]); dup2(fd[0], 0); close(fd[0]); }
        i++;
    }
    dup2(f_out, 1); close(f_out); // Redirect stdout to outfile
    execute_cmd(argv[i], envp);
    return (0);
}


< infile.txt ps aux | grep -v 0:00 | sort -k3 -r | head -n 10 > outfile.txt
./pipex infile.txt "ps aux" "grep -v '0:00'" "sort -k3" "head -n 10" outfile.txt
