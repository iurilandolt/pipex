
This program replicates the functionality of Unix terminal pipes (|). It accepts input from a file, from the output of a terminal command, or through the "here_doc" (<<) method. The input is then channeled through one or more commands, with each command processing the output of the previous one. The final result is directed into an output file.
#metion path variable.

We begin with opening the correct files and storing their given file descriptors. These will be the first and last argument of the ./pipex call.

int	file_input(int argc, char **argv, int *filein, int *fileout)
{
	*fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*filein = open(argv[1], O_RDONLY, 0644);
	if (*filein == -1 || *fileout == -1)
		ft_error();
	dup2(*filein, STDIN_FILENO);
	return (2);
}

The function file_input serves as a foundational step to set up the data flow for our first child process. This initial child process will read input, process it, and pass it through a series of other child processes. The data then finally reaches our parent process; argv[argc -2] ending in fileout.

To make this possible we use the dup2() function. 
Initially, with:

dup2(*filein, STDIN_FILENO);

we redirect the standard input (STDIN_FILENO) to read from filein. With this redirection when we invoke the command from argv[2], it will recieve input directly from filein.
We then loop through the subsequent commands using the child function, establishing a pipeline of processes to handle our data.
		
  file_input(argc, argv, &filein, &fileout);
		while (i < argc - 2)
			child(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);

  within the child function is where things get more messy, we need to understand what a pipe is and how it works, and also how the code readability is affected after using functions like fork() and execve().
  Similiar to what we did before with filein and fileout we will use an array of two ints as file descriptors, one for reading, one for writting.
	
int		fd[2];
if (pipe(fd) == -1)
    ft_error();

we use another int to identify the proccess id, the way fork works is that it creates a paralel process to our initial process, a child to a parent. In this instance we do not know wich one will finish first,
so por managing purposes these proccesses are given identifiers, the parent process will have a positive value, and the child process will have the value 0.
in this way we can decide what happens in each process. Note that this is necessary because all the code bellow the fork() call will run twice, one for each proccess.

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
	close_and_send(&proc_id, fd);


