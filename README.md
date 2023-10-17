
# pipex 
This program replicates the functionality of Unix terminal pipes `|`. 

It accepts input from a `file`, from the output of a `terminal command`, or through the `"here_doc"` `<<` method. 

The input is then channeled through one or more commands, with each command processing the output of the previous one. The final result is directed into an output file.

The allowed functions for this project are: 

`open`; `close`; `read`; `write`; `malloc`; `wait`; `waitpid`; `free`; `pipe`; `fork`; `dup`; `dup2`; `execve`; `perror`; `strerror`; `exit`;

The program's arguments in comparison to the system's terminal arguments are:

`$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

`< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`

`$> ./pipex here_doc eof cmd1 cmd2 cmd3 ... cmdn file2`

`<< eof cmd1 | cmd2 | cmd3 ... | cmdn > file2`

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

The function file_input serves as a foundational step to set up the data flow for our first child process. 

This initial child process will read input, process it, and pass it through a series of other child processes. 

The data then finally reaches our parent process; `argv[argc -2]` ending in `fileout`.

To make this possible we use the `dup2()` function. 

Initially, with:

	dup2(*filein, STDIN_FILENO);

we redirect the standard input `(STDIN_FILENO)` to read from `filein`. 

With this redirection when we invoke the command from `argv[2]`, it will recieve input directly from `filein`.

We then loop through the subsequent commands using the child function, establishing a pipeline of processes to handle our data.
		
	  file_input(argc, argv, &filein, &fileout);
			while (i < argc - 2)
				child(argv[i++], envp);
			dup2(fileout, STDOUT_FILENO);
			execute(argv[argc - 2], envp);

  Within the child function is where things get more messy, we need to understand what a pipe is and how it works, and also how the code readability is affected after using functions like `fork()` and `execve()`.
  
  Similiar to what we did before with `filein` and `fileout` we will use  `pipe()` on an array of two ints and use them as file descriptors, one for reading, one for writting.
	
	int		fd[2];
	if (pipe(fd) == -1)
	    ft_error();

We use another int to identify the `process id`, the way `fork()` works is that it creates a paralel process to our initial process, a child to a parent. 

In this instance we do not know wich one will finish first, so for managing purposes these proccesses are given identifiers, the parent process will have a `positive value`, and the child process will have the `value 0`.

In this way we can decide what happens in each process. 

Note that this is necessary because all the code bellow the fork() call will run twice, one for each proccess.

	pid_t	proc_id;
	proc_id = fork();
	if (proc_id == -1)
		ft_error();

If proc_id is 0, we're within the child process. 

We close the read end of the pipe and redirect the standard output to the write end.  

	if (proc_id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
  
In oposition if we're in the parent process we use waitpid to wait for a child with a matching id to stop. 

We close the write end of the pipe `close(fd[1])` and redirect the input of the parent process `(STDIN_FILENO)` to the read end `(fd[0])` of the pipe.

	else
	{
		waitpid(*id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}

After the loop ends control returns to the main function, where we redirect the standard output `(STDOUT_FILENO)` of the parent process to `fileout` and `execute` the last argument. `argv[argc - 2]`.

	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);

understanding the execute() function. This is where we deal with 'execve' and the PATH environment variable for the first time.
In our main function, we are using a third argument char ** envp, envp is an array of strings containing envrimental variables. 

	#include <stdio.h>
	
	int main(int argc, char **argv, char **envp) 
	{
		(void)argc;
		(void)argv;
		for (int i = 0; envp[i] != NULL; i++)
			printf("%s\n", envp[i]);
		return 0;
	}

The one we are interested in is the PATH environment variable.
It provides us with a list of directories where command-line utilities and other executable programs are located. The PATH variable contains a series of directory paths separated by colons (:). "PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"
You can add directories to your PATH if you have custom scripts or binaries located elsewhere or modify it in a user's profile settings (~/.bashrc, ~/.bash_profile, or ~/.profile for the bash shell, for instance) to make the change persistent across sessions.
To view the current directories included in the PATH variable in a terminal, you can use the command: 'echo $PATH'

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

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

#metion path variable.

#error managing, stderr, exit() function

#check if anything is left open

#allowed functions

#program arguments vs system arguments

