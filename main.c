#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		// printf("%s", line);  // 출력 필요하면 켜기
		free(line);
	}
	close(fd);
	return (0);
}
