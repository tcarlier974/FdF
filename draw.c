/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:28:05 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 17:49:41 by tcarlier         ###   ########.fr       */
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
	int		color;

	init_derivative(&line, &tab1, &tab2);
	init_slope(&line.sx, &line.sy, &tab1, &tab2);
	printf("tab1.x = %d, tab1.y = %d, tab2.x = %d, tab2.y = %d\n", tab1.draw_x, tab1.draw_y, tab2.draw_x, tab2.draw_y);
	printf("slope x = %d, slope y = %d\n", line.sx, line.sy);
	if (max(tab1.z, tab2.z) == tab1.z)
		color = tab1.color;
	else
		color = tab2.color;
	while (1)
	{
		my_mlx_pixel_put(&(**img), tab1.draw_x, tab1.draw_y, color);
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
		printf("tab1.draw_x = %d, tab1.draw_y = %d\n", tab1.draw_x, tab1.draw_y);
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
        while (x < c - 1)
        {
            if (x < c - 2)
            {
                printf("Drawing horizontal line at y=%d, x=%d to x+1=%d\n", y, x, x + 1);
                draw_line(tab[y][x], tab[y][x + 1], &img);
            }
            if (y < l - 2)
            {
                printf("Drawing vertical line at x=%d, y=%d to y+1=%d\n", x, y, y + 1);
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
