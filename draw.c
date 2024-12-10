/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:28:05 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 20:08:23 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	init_slope(int *sx, int *sy, t_tab *tab1, t_tab *tab2)
{
	if (tab1->draw_x < tab2->draw_x)
		*sx = 1;
	else
		*sx = -1;
	if (tab1->draw_y < tab2->draw_y)
		*sy = 1;
	else
		*sy = -1;
}

static void	init_derivative(t_line *line, t_tab *tab1, t_tab *tab2)
{
	line->dx = abs(tab2->draw_x - tab1->draw_x);
	line->dy = abs(tab2->draw_y - tab1->draw_y);
	line->err = line->dx - line->dy;
}

static void	draw_line(t_tab tab1, t_tab tab2, t_data **img)
{
	t_line	line;
	int		e2;
	int		max_z;
	int    min_z;

	init_derivative(&line, &tab1, &tab2);
	init_slope(&line.sx, &line.sy, &tab1, &tab2);
	if (tab1.z > tab2.z)
		max_z = tab1.z;
	else
		max_z = tab2.z;
	if (tab1.z < tab2.z)
		min_z = tab1.z;
	else
		min_z = tab2.z;
	while (1)
	{
		my_mlx_pixel_put(&(**img), tab1.draw_x, tab1.draw_y, gen_rgb(tab1.z, max_z, min_z));
		if (tab1.draw_x == tab2.draw_x && tab1.draw_y == tab2.draw_y)
			break ;
		e2 = 2 * line.err;
		if (e2 >= -line.dy)
		{
			line.err -= line.dy;
			tab1.draw_x += line.sx;
		}
		if (e2 < line.dx)
		{
			line.err += line.dx;
			tab1.draw_y += line.sy;
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
    while (y < l - 1)
    {
        x = 0;
        while (x < c)
        {
            if (x < c - 1)
            {
                draw_line(tab[y][x], tab[y][x + 1], &img);
            }
            if (y < l - 2)
            {
                draw_line(tab[y][x], tab[y + 1][x], &img);
            }
            x++;
        }
        y++;
    }
    return (img->img);
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    
    // Vérifier que les coordonnées sont dans les limites de l'image
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
