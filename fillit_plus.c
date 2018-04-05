/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 05:57:41 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/01 18:03:58 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char	**new_map(int size)
{
	char	**a;
	int		i;
	int		j;

	a = (char **)malloc(sizeof(char *) * size);
	i = -1;
	while (++i < size)
		a[i] = (char *)malloc(sizeof(char) * size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			a[i][j] = '.';
	}
	return (a);
}

void	print_res(char **res, int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			write(1, &res[i][j], 1);
		write(1, "\n", 1);
	}
}

int		min_out(int size)
{
	int i;

	i = 2;
	size *= 4;
	while (i * i < size)
		i++;
	return (i);
}

void	free_out(char ***res, t_dlist **head, int size)
{
	int		i;
	t_dlist	*bck;

	i = -1;
	while (++i < size)
		free((*res)[i]);
	free(*res);
	bck = *head;
	while (*head)
	{
		*head = (*head)->next;
		free(bck);
		bck = *head;
	}
}
