#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	get_line(char **line)
{
	int		i;
	int		b_read;
	char	*buffer;;

	i = 0;
	buffer = (char *)malloc(1024 * sizeof(char));
	while ((b_read = read(0, buffer + i, 1)) > 0)
	{
		if (buffer[i] == '\n' || buffer[i] == '\0')
			break;
		i++;
	}
	if (b_read > 0)
	{
		buffer[i + 1] = '\0';
		*line = buffer;
		printf("line read %s\n", *line);
	}
	free(buffer);
	return (b_read);
}

int	main(void)
{
	char	*line;
	int		result;

	result = get_line(&line);
	while (result > 0)
		result = get_line(&line);
	if (get_line(&line) == 0)
		printf("end of line reached\n");
	else
		printf("an error ocurred\n");
	return (0);
}
