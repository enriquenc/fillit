/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 17:23:47 by tmaslyan          #+#    #+#             */
/*   Updated: 2018/04/01 18:59:28 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		free_return_zero(t_dlist *head)
{
	if (!head)
		return ;
	while (head->next)
	{
		head = head->next;
		free(head->prev);
	}
	free(head);
}

t_dlist		*file_parser(char *file, int *size)
{
	int		fd;
	int		xy[2];
	int		hash;
	t_dlist	*head;

	if (!(head = (t_dlist *)malloc(sizeof(t_dlist))))
		return (0);
	head->prev = 0;
	head->next = 0;
	fd = open(file, O_RDONLY);
	xy[0] = 0;
	xy[1] = 0;
	hash = 0;
	if (!(optimization(head, &hash, xy, fd)) ||
			(hash != 4 || xy[0] || (xy[1] + 1) % 5))
	{
		free_return_zero(head);
		return (0);
	}
	*size = (xy[1] + 1) % 5;
	return (head);
}
