/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:28:05 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 17:40:24 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_tab tab1, t_tab tab2, t_data *img)
{
	int dx;
	int dy;
	int x;
	int y;
	int i;

	dx = abs(tab2.x - tab1.x);
	dy = -abs(tab2.y - tab1.y);
	x = tab1.x;
	y = tab1.y;
	i = 0;
	while (i <= dx)
	{
		my_mlx_pixel_put(&(*img), x + i, y + i * dy / dx, tab1.color);
		i++;
	}
}

void	*draw_line_img(t_data img, t_tab **tab, char *av)
{
	int x;
	int y;

	y = 0;
	while (y < count_lines(av))
	{
		x = 0;
		while (x < count_col(av))
		{
			if (x + 1 < count_col(av))
				draw_line(tab[y][x], tab[y][x + 1], &img);
			if (y + 1 < count_lines(av))
				draw_line(tab[y][x], tab[y + 1][x], &img);
			x++;
		}
		y++;
	}
	return (img.img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}