#include "../include/pipex.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

static void	ft_putstr_fd(char *str, int fd)
{
	if (str)
	{
		while (*str)
			ft_putchar_fd(*str++, fd);
	}
}

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_error(void)
{
	perror("Error.");
	exit(EXIT_FAILURE);
}
