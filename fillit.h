/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:21:37 by obamzuro          #+#    #+#             */
/*   Updated: 2018/04/01 18:36:10 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_dlist
{
	int				crd[4][2];
	int				ocrd[2];
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

int				optimization(t_dlist *head, int *hash, int xy[2], int fd);
t_dlist			*file_parser(char *file, int *size);
char			**new_map(int size);
void			print_res(char **res, int size);
int				min_out(int size);
void			free_out(char ***res, t_dlist **head, int size);
t_dlist			*file_parser(char *file, int *size);
t_dlist			*end_row(t_dlist *head, int *hash, int fcrd[2]);
int				hash_nb(t_dlist *node, int arr[4], int hash);
t_dlist			*if_slash_n(int xy[2], t_dlist *head, int fcrd[2], int *hash);
t_dlist			*if_hash(int xy[2], int *hash, int fcrd[2], t_dlist *head);

#endif
