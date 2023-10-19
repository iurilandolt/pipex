
# pipex 

This program replicates the functionality of Unix terminal pipes `|`. 

It accepts input from a `file`, from the output of a `terminal command`, or through the `"here_doc"` `<<` method. 

The input is then channeled through one or more commands, with each command processing the output of the previous one. 

The final result is directed into an output file.

The allowed functions for this project are: 

`open`; `close`; `read`; `write`; `malloc`; `wait`; `waitpid`; `free`; `pipe`; `fork`; `dup`; `dup2`; `execve`; `perror`; `strerror`; `exit`.

The program's arguments, in comparison to the system's terminal arguments, are:

`$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

`< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`

`$> ./pipex here_doc eof cmd1 cmd2 cmd3 ... cmdn file2`

`<< eof cmd1 | cmd2 | cmd3 ... | cmdn > file2`

## Opening the correct files and storing their given file descriptors. 

These will be the first and last arguments of the ./pipex call.

	int	file_input(int argc, char **argv, int *filein, int *fileout)
	{
		*fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		*filein = open(argv[1], O_RDONLY, 0644);
		if (*filein == -1 || *fileout == -1)
			ft_error();
		dup2(*filein, STDIN_FILENO);
		return (2);
	}

The function `file_input()` serves as a starting step to set up the data flow for our first child process. 

`*filein = open(argv[1], O_RDONLY, 0644);`  We use `open()` to store the file descriptor of the input file given by the user, `argv[1]`.

### Redirecting the standard input

We redirect `(STDIN_FILENO)` to read from `filein` with:

	dup2(*filein, STDIN_FILENO);

With this redirection, we are ready to execute our first command `argv[2]`. If this command requires input, it will be read directly from `filein`.

The `dup2()` function duplicates one file descriptor, making it an alias to another.

If successful, it returns the new file descriptor. If there is an error, it returns -1. The function has two main arguments:

- oldfd: The original file descriptor you want to duplicate.
- newfd: The file descriptor number you want the duplicate to adopt. If newfd is already open, it gets closed before being reused.

Before moving on, we also set up our final destination, the output file, with: 

`*fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);`

These flags `O_WRONLY | O_CREAT | O_TRUNC` specify the type of access we want to the file. In this case, we want to write to the file, create it if it doesn't exist, and overwrite its content if it already exists.
The `0644` sets the file permission mode for `O_CREAT` when creating a new file.

## Starting and executing the first child process
		
	  int main(int argc, char **argv, char **envp) {
   		file_input(argc, argv, &filein, &fileout);
			while (i < argc - 2)
				child(argv[i++], envp);
			dup2(fileout, STDOUT_FILENO);
			execute(argv[argc - 2], envp); }

After setting up our source and destination, we can start running the child commands; `while (i < argc - 2)` -> `child(argv[i++], envp);`
  
Within the child function, we will encounter `**envp`, `pipe()`, `fork()`, `waitpid()`, and `execve()` for the first time. Familiarity with these concepts is key to understanding this project. I've tried to approach them in the most simplistic way possible as they are new concepts to me.
  
Similar to what we did before with `filein` and `fileout`, we will use `pipe()` on an array of two ints and use them as file descriptors: one for reading `fd[0]` and one for writing `fd[1]`.
	
	int fd[2];
	if (pipe(fd) == -1)
	    ft_error();

We use another int to identify the `process id`. The way `fork()` works is that it creates a parallel process to our original process, creating a child and a parent. 

In this instance, we do not know which one will finish first, so for management purposes, these processes are given identifiers: the parent process will have a `positive value`, and the child process will have the `value 0`.

This allows us to control what happens in each process. 

Note that this is necessary because all the code below the fork() call will run twice, once for each process.

	pid_t	proc_id;
	proc_id = fork();
	if (proc_id == -1)
		ft_error();

If `proc_id` is 0, we're in the child process. 

We close the read end of the pipe `close(fd[0]);`.  

<sub>(In this instance, we don't need to read from the pipe because our input is already set up to be read from `filein` -> `dup2(*filein, STDIN_FILENO);`)</sub>

Redirect the standard output `STDOUT_FILENO` to the write end `fd[1]`. `dup2(fd[1], STDOUT_FILENO);`

Execute `argv[i]`; 

<sub>(In the first iteration, the child process will read its input from `filein`. In subsequent iterations, the child processes will read their input from the output of the previous command.) </sub>

	if (proc_id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
  
In opposition, if we're in the parent process, we use `waitpid()` to wait for a child with a matching ID to stop.

<sub>This is where we will pipe the output for subsequent `child()` iterations.</sub>

In the parent process, we wait for the child process to end with `waitpid(*id, NULL, 0);`, close the write end of the pipe with `close(fd[1])`, and set `STDIN_FILENO` to receive input from `fd[0]`. 

As a result, the next time we call the `execute()` function, whether in the next iteration of `child()` or in the `main()`, the executed command will receive input from the reading end of the previously set pipe `fd[0]`.

	else
	{
		waitpid(*id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}

After the last child() iteration ends, control returns to the main function. Here, we redirect the output and execute our final command `argv[argc - 2]`.

	dup2(fileout, STDOUT_FILENO);
	execute(argv[argc - 2], envp);

## Execute(), execve() and PATH 

This is where we deal with `execve()` and the `$PATH` `environment variable` for the first time.

In our main function, we are using a third argument `char ** envp`, envp is an array of strings containing `environment variables`. 

	#include <stdio.h>
	
	int main(int argc, char **argv, char **envp) 
	{
		(void)argc;
		(void)argv;
		for (int i = 0; envp[i] != NULL; i++)
			printf("%s\n", envp[i]);
		return 0;
	}

The code above will give you a list of all the environmental variables in your system. The one we are interested in is the `$PATH` environment variable.

It provides us with a list of directories where command-line utilities and other executable programs are located. 

The `PATH` variable contains a series of directory paths separated by colons `:`. For example, `"PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin"`.

You can add directories to your PATH if you have custom scripts or binaries located elsewhere. Alternatively, you can modify it in a user's profile settings (like `~/.bashrc`, `~/.bash_profile`, or `~/.profile` for the bash shell, for instance) to make the change persistent across sessions.

To view the current directories included in the PATH variable in a terminal, you can use the command: `echo $PATH`.

We need these directories in order to run `execve()`. The `execve()` function replaces the current process with a new one. 

If successful, it does not return. If there is an error, it returns -1. This function takes three arguments: 

- A string representing the path to the executable.
- A NULL-terminated array of string pointers representing the command and its arguments. For instance, for the command "ls -a", we might use a function like `split()`.
- A pointer to the environment variables, `**envp`.
 
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
  
If `execve()` is successful, no code after it will be considered. We use the if clause `if (execve(path, cmd, envp) == -1)` to free both `*path` and `**cmd` and to print an error to `stderr` in case it fails.

 # Managing errors, error codes and cleaning up.

 When a system call or library function encounters an error, it usually sets the global variable `errno` to a positive integer that corresponds to the error that occurred.
 
 The `perror()` function takes this `errno` value and displays its corresponding string description, preceded by the string you give to `perror().`

`ft_error()`: Calls perror() to display the last error message and then exits the program with the `EXIT_FAILURE` status.

`path_error()`: Prints an error message to the standard error (file descriptor 2), indicating that the given command str was not found, then exits with a status of 127. 

The exit code 127 is commonly used in shells to indicate that a command was not found.
- `EXIT_SUCCESS` is typically defined as 0, indicating success.
- `EXIT_FAILURE` is an implementation-defined non-zero value, which indicates failure. In most implementations, it's defined as 1.

## Alternative input `<<` `here_doc`

Alternatively we can use the input from the from the unix `<<` `here_doc` functionality `if (ft_strnstr(argv[1], "here_doc", 8) != 0 && argc > 5)`

	int	terminal_input(int argc, char **argv, int *fileout)
	{
		*fileout = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fileout == -1)
			ft_error();
		call_doc(argv);
		return (3);
	}
 The `call_doc()` basically uses input from the `get_line()` to write into `fd[1]` during the child process with;`ft_putstr_fd(line, fd[1]);`.
 	
  	proc_id = fork();
	if (proc_id == -1)
		ft_error();	
  	 if (proc_id == 0)
	{
		while (get_line(&line) > 0)
		{
			ft_putstr_fd(line, fd[1]);
			if (ft_strnstr(line, argv[2], ft_strlen(line)) != 0)
				exit(0);
			free(line);
		}
	}
 
 And in the parent process, like bofore, we wait for the child process to end with `waitpid(*id, NULL, 0);`, close the write end of the pipe with `close(fd[1])`, and set `STDIN_FILENO` to receive input from `fd[0]`. 
 
 	else
  	{
		waitpid(*id, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}

## Signal Flow

```
stdin   
   │
   ▼
filein ───────┐  (opened by main function using open())
/ here_doc    |
   │          │
   ▼          │
stdout ───┬───┘ (via dup2(*filein, STDIN_FILENO);)
          │
          ▼
        fd[1] ───────────┐  (write end of first pipe, set in child() using pipe())
          │              │
          ▼              │
stdout (of 1st child) ───┤ (via dup2(fd[1], STDOUT_FILENO); in child())
          │              │
          ▼              │
        fd[0] ───────────┘ (read end of first pipe)
          │
          ▼
stdout (of 2nd child) ────┬───┐ (via dup2(fd[1], STDOUT_FILENO); in 2nd child())
          │               │   │
          ▼               │   │
        fd[1] ────────────┘   │ (write end of second pipe, set in 2nd child using pipe())
          │                   │
          ▼                   │
stdout (of nth child) ────────┘
          │
          ▼
fileout (redirected by main)
   │
   ▼
stdout (via dup2(fileout, STDOUT_FILENO); in main) 
