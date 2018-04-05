/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:27:28 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/01 18:59:42 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_dlist		*end_row(t_dlist *head, int *hash, int fcrd[2])
{
	if (!(head->next = (t_dlist *)malloc(sizeof(t_dlist))))
		return (0);
	head->next->prev = head;
	head->next->next = 0;
	head = head->next;
	*hash = 0;
	fcrd[0] = -1;
	return (head);
}

int			hash_nb(t_dlist *node, int arr[4], int hash)
{
	int		iter[5];

	iter[0] = 1;
	iter[4] = -1;
	while (++iter[4] < 2)
	{
		iter[1] = iter[4] ? -1 : 0;
		iter[2] = iter[4] ? 0 : -1;
		while (iter[4] ? (iter[1] <= 1) : (iter[2] <= 1))
		{
			iter[3] = -1;
			while (++iter[3] < 4)
			{
				if (node->crd[iter[3]][0] == iter[1] + node->crd[hash][0] &&
		node->crd[iter[3]][1] == iter[2] + node->crd[hash][1] && !arr[iter[3]])
				{
					arr[iter[3]] = 1;
					iter[0] += hash_nb(node, arr, iter[3]);
				}
			}
			iter[4] ? (iter[1] += 2) : (iter[2] += 2);
		}
	}
	return (iter[0]);
}

t_dlist		*if_slash_n(int xy[2], t_dlist *head, int fcrd[2], int *hash)
{
	int		arr[4];

	arr[0] = 1;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;
	++(xy[1]);
	if (((!(xy[1] % 5) && xy[0] != 0) || ((xy[1] % 5) && xy[0] != 4))
			|| xy[1] > 129)
		return (0);
	xy[0] = 0;
	if (!((xy[1] + 1) % 5))
	{
		arr[0] = 1;
		arr[1] = 0;
		arr[2] = 0;
		arr[3] = 0;
		if (hash_nb(head, arr, 0) != 4)
			return (0);
	}
	if (!(xy[1] % 5) && !(head = end_row(head, hash, fcrd)))
		return (0);
	return (head);
}

t_dlist		*if_hash(int xy[2], int *hash, int fcrd[2], t_dlist *head)
{
	if (*hash == 4)
		return (0);
	if (fcrd[0] == -1)
	{
		fcrd[0] = xy[1];
		fcrd[1] = xy[0];
	}
	head->crd[*hash][0] = xy[1] - fcrd[0];
	head->crd[*hash][1] = xy[0] - fcrd[1];
	++(*hash);
	return (head);
}

int			optimization(t_dlist *head, int *hash, int xy[2], int fd)
{
	int		fcrd[2];
	char	reading;

	fcrd[0] = -1;
	while (read(fd, &reading, 1))
	{
		if (reading == '\n')
		{
			if (!(head = if_slash_n(xy, head, fcrd, hash)))
				return (0);
			continue ;
		}
		else if (reading == '#')
		{
			if (!(head = if_hash(xy, hash, fcrd, head)))
				return (0);
		}
		else if (reading != '.')
			return (0);
		++(xy[0]);
	}
	return (1);
}
