/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:28:05 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 17:58:54 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static	void	init_slope(int *sx, int *sy, t_tab *tab1, t_tab *tab2)
{
	if (tab1->x < tab2->x)
		*sx = 1;
	else
		*sx = -1;
	if (tab1->y < tab2->y)
		*sy = 1;
	else
		*sy = -1;
}

static void	draw_line(t_tab tab1, t_tab tab2, t_data *img)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(tab2.x - tab1.x), dy = -abs(tab2.y - tab1.y), err = dx + dy;
	init_slope(&sx, &sy, &tab1, &tab2);
	while (1)
	{
		my_mlx_pixel_put(&(*img), tab1.x, tab1.y, tab1.color);
		if (tab1.x == tab2.x && tab1.y == tab2.y)
			break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			tab1.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			tab1.y += sy;
		}
	}
}

void	*draw_line_img(t_data *img, t_tab **tab, char *av)
{
	int x;
	int y;

	y = 0;
	while (y < count_lines(av))
	{
		x = 0;
		printf("test\n");
		while (x < count_col(av))
		{
			if (x + 1 < count_col(av))
				draw_line(tab[y][x], tab[y][x + 1], &(*img));
			if (y + 1 < count_lines(av))
				draw_line(tab[y][x], tab[y + 1][x], &(*img));
			x++;
		}
		y++;
	}
	return (img->img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}