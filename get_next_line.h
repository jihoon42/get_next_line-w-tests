/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkim2 <jkim2@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 02:45:14 by jkim2             #+#    #+#             */
/*   Updated: 2026/01/21 04:17:05 by jkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_static
{
	char	*content;
	size_t	size;
}	t_static;

char	*get_next_line(int fd);

int		has_newline(t_static *stash);
size_t	newline_index(t_static *stash);
void	stash_clear(t_static *stash);

#endif
