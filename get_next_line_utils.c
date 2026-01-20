/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 02:46:12 by jkim2             #+#    #+#             */
/*   Updated: 2026/01/21 04:17:05 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(t_static *stash)
{
	size_t	i;

	if (!stash->content || stash->size == 0)
		return (0);
	i = 0;
	while (i < stash->size)
	{
		if (stash->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
** Returns:
** - index of '\n' if found
** - stash->size if not found
*/
size_t	newline_index(t_static *stash)
{
	size_t	i;

	if (!stash->content || stash->size == 0)
		return (0);
	i = 0;
	while (i < stash->size)
	{
		if (stash->content[i] == '\n')
			return (i);
		i++;
	}
	return (stash->size);
}

void	stash_clear(t_static *stash)
{
	free(stash->content);
	stash->content = NULL;
	stash->size = 0;
}
