/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:38:08 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/01 19:00:19 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	is_valid(char **res, int size, t_dlist *p_dlist, int iter[3])
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (iter[0] + p_dlist->crd[i][0] >= size || iter[0] +
				p_dlist->crd[i][0] < 0 || iter[1] + p_dlist->crd[i][1]
				>= size || iter[1] + p_dlist->crd[i][1] < 0 ||
			res[iter[0] + p_dlist->crd[i][0]][iter[1] +
			p_dlist->crd[i][1]] != '.')
			return (0);
	}
	i = -1;
	while (++i < 4)
		res[iter[0] + p_dlist->crd[i][0]][iter[1] +
			p_dlist->crd[i][1]] = 'A' + iter[2];
	p_dlist->ocrd[0] = iter[0] + p_dlist->crd[0][0];
	p_dlist->ocrd[1] = iter[1] + p_dlist->crd[0][1];
	return (1);
}

void	bad_case(char ***res, t_dlist **p_dlist, int *size, int *iter)
{
	int i;

	if ((*p_dlist)->prev)
	{
		*p_dlist = (*p_dlist)->prev;
		--(iter[2]);
		i = -1;
		while (++i < 4)
			(*res)[(*p_dlist)->ocrd[0] +
				(*p_dlist)->crd[i][0]][(*p_dlist)->ocrd[1]
				+ (*p_dlist)->crd[i][1]] = '.';
		iter[0] = (*p_dlist)->ocrd[0];
		iter[1] = (*p_dlist)->ocrd[1] + 1;
	}
	else
	{
		i = -1;
		while (++i < *size)
			free((*res)[i]);
		free(*res);
		++(*size);
		*res = new_map(*size);
		iter[0] = 0;
		iter[1] = 0;
	}
}

void	assemble_inner(t_dlist **p_dlist, int *size, char **res, int iter[4])
{
	while (iter[0] < *size)
	{
		while (iter[1] < *size)
		{
			if (is_valid(res, *size, *p_dlist, iter))
			{
				*p_dlist = (*p_dlist)->next;
				++(iter[2]);
				iter[0] = *size;
				iter[3] = 1;
				break ;
			}
			++iter[1];
		}
		iter[1] = 0;
		++iter[0];
	}
}

void	assemble(t_dlist *p_dlist, int *size, char ***res)
{
	int		iter[4];

	*res = new_map(*size);
	iter[2] = 0;
	iter[1] = 0;
	iter[0] = 0;
	while (p_dlist)
	{
		iter[3] = 0;
		assemble_inner(&p_dlist, size, *res, iter);
		if (!iter[3])
			bad_case(res, &p_dlist, size, iter);
		else
		{
			iter[1] = 0;
			iter[0] = 0;
		}
	}
}

int		main(int argc, char **argv)
{
	int		size;
	char	**res;
	t_dlist	*head;

	if (argc != 2)
	{
		write(1, "usage: ./fillit file\n", 21);
		return (0);
	}
	head = file_parser(argv[1], &size);
	if (!head)
	{
		write(1, "error\n", 6);
		return (0);
	}
	size = min_out(size);
	assemble(head, &size, &res);
	print_res(res, size);
	free_out(&res, &head, size);
}
