/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 02:46:51 by jkim2             #+#    #+#             */
/*   Updated: 2026/01/21 04:17:38 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	append_buffer(t_static *stash, char *buffer, size_t bytes_read)
{
	char	*new_content;
	size_t	i;
	size_t	j;

	new_content = malloc(stash->size + bytes_read);
	if (!new_content)
	{
		stash_clear(stash);
		return (1);
	}
	i = 0;
	while (i < stash->size)
	{
		new_content[i] = stash->content[i];
		i++;
	}
	j = 0;
	while (j < bytes_read)
		new_content[i++] = buffer[j++];
	free(stash->content);
	stash->content = new_content;
	stash->size += bytes_read;
	return (0);
}

static int	stash_trim(t_static *stash, size_t newline_idx)
{
	char	*new_content;
	size_t	start;
	size_t	new_size;
	size_t	i;

	if (!stash->content || stash->size == 0)
		return (0);
	if (newline_idx >= stash->size)
		return (stash_clear(stash), 0);
	start = newline_idx + 1;
	new_size = stash->size - start;
	if (new_size == 0)
		return (stash_clear(stash), 0);
	new_content = malloc(new_size);
	if (!new_content)
		return (stash_clear(stash), 1);
	i = 0;
	while (i < new_size)
		new_content[i++] = stash->content[start++];
	free(stash->content);
	stash->content = new_content;
	stash->size = new_size;
	return (0);
}

static char	*get_line(t_static *stash)
{
	char	*line;
	size_t	idx;
	size_t	linelen;
	size_t	i;

	if (!stash->content || stash->size == 0)
		return (NULL);
	idx = newline_index(stash);
	linelen = stash->size;
	if (idx < stash->size)
		linelen = idx + 1;
	line = malloc(linelen + 1);
	if (!line)
		return (stash_clear(stash), NULL);
	i = 0;
	while (i < linelen)
	{
		line[i] = stash->content[i];
		i++;
	}
	line[linelen] = '\0';
	if (stash_trim(stash, idx))
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_static	stash;
	static int		last_fd = -1;
	char			*buffer;
	ssize_t			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (last_fd != fd)
		(stash_clear(&stash), last_fd = fd);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (stash_clear(&stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !has_newline(&stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (stash_clear(&stash), free(buffer), NULL);
		if (bytes_read > 0 && append_buffer(&stash, buffer, (size_t)bytes_read))
			return (free(buffer), NULL);
	}
	free(buffer);
	return (get_line(&stash));
}
