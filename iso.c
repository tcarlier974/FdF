/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:50:30 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 20:01:40 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	isometric_format_x(int x, int y, int z)
{
	int tmp;
	
	tmp = x;
	(void)z;
	return ((tmp - y) * cos(0.523599));
}

int	isometric_format_y(int x, int y, int z)
{
	int tmp;
	
	tmp = x;
	return ((tmp + y) * sin(0.523599) - z);
}

void	change_to_iso(t_tab ***tab, char *av)
{
	int x;
	int y;
	int c;
	int l;

	y = 0;
	c = count_lines(av);
	l = count_col(av);
	while (y < c)
	{
		printf("y : %d\n", y);
		x = 0;
		while (x < l - 1)
		{
			tab[y][x]->x = isometric_format_x(tab[y][x]->x, tab[y][x]->y, tab[y][x]->z);
			printf("x : %d  ", tab[y][x]->x);
			tab[y][x]->y = isometric_format_y(tab[y][x]->x, tab[y][x]->y, tab[y][x]->z);
			printf("y : %d\n", tab[y][x]->y);
			x++;
		}
		y++;
	}
}