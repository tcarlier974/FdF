/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:28:05 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 21:10:58 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	init_slope(int *sx, int *sy, t_tab *tab1, t_tab *tab2)
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

static void	init_derivative(t_line *line, t_tab *tab1, t_tab *tab2)
{
	line->dx = abs(tab2->x - tab1->x);
	line->dy = abs(tab2->y - tab1->y);
	line->err = line->dx + line->dy;
}

static void	draw_line(t_tab tab1, t_tab tab2, t_data *img)
{
	t_line	line;
	int		e2;
	
	line.sx = 0;
	line.sy = 0;
	init_derivative(&line, &tab1, &tab2);
	init_slope(&line.sx, &line.sy, &tab1, &tab2);
	while (1)
	{
		my_mlx_pixel_put(&(*img), tab1.x, tab1.y, generate_rgb());
		if (tab1.x == tab2.x && tab1.y == tab2.y)
			break ;
		e2 = 2 * line.err;
		printf("e2 : %d\n", e2);
		printf("x1 : %d, y1 : %d\n", tab1.x, tab1.y);
		printf("x2 : %d, y2 : %d\n", tab2.x, tab2.y);
		if (e2 >= line.dy && tab1.x != tab2.x)
		{
			line.err -= line.dy;
			tab1.x += line.sx;
		}
		if (e2 <= line.dx)
		{
			line.err += line.dx;
			tab1.y += line.sy;
		}
	}
}

void	*draw_line_img(t_data *img, t_tab **tab, char *av)
{
	int	x;
	int	y;
	int	c;
	int	l;

	l = count_lines(av);
	c = count_col(av);
	y = 0;
	while (y < l)
	{
		x = 0;
		while (x < c)
		{
			printf("Draw line, x : %d\n", x);
			if (x + 1 < c)
				draw_line(tab[y][x], tab[y][x + 1], &(*img));
			if (y + 1 < l)
				draw_line(tab[y][x], tab[y + 1][x], &(*img));
			x++;
			printf("End draw line, x : %d\n", x);
		}
		y++;
	}
	return (img->img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
