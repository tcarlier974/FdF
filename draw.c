/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:28:05 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 17:34:45 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*draw_line_img(t_data img, t_tab **tab)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		dx;
	int		dy;
	int		p;
	int		xinc;
	int		yinc;
	int		color;

	i = 0;
	while (i < count_lines("map.fdf"))
	{
		j = 0;
		while (j < count_col("map.fdf"))
		{
			x1 = tab[i][j].x;
			y1 = tab[i][j].y;
			x2 = tab[i][j + 1].x;
			y2 = tab[i][j + 1].y;
			dx = x2 - x1;
			dy = y2 - y1;
			x = x1;
			y = y1;
			p = 2 * dy - dx;
			xinc = (dx > 0) ? 1 : -1;
			yinc = (dy > 0) ? 1 : -1;
			dx = (dx < 0) ? -dx : dx;
			dy = (dy < 0) ? -dy : dy;
			color = tab[i][j].color;
			while (x != x2 || y != y2)
			{
				my_mlx_pixel_put(&img, x, y, color);
				if (p >= 0)
				{
					y += yinc;
					p += 2 * dy - 2 * dx;
				}
				else
					p += 2 * dy;
				x += xinc;
			}
			j++;
		}
		i++;
	}
	return (img.img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}