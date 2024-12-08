/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:50:30 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 01:04:14 by tcarlier         ###   ########.fr       */
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

void	change_to_iso(t_tab ***tab, char *av, int offset_x, int offset_y)
{
    int x;
    int y;
    int c;
    int l;

    y = 0;
    c = count_lines(av);
    l = count_col(av);
    zoom_init(&tab, av);
    while (y < c - 1)
    {
        x = 0;
        while (x < l - 1)
        {
            (*tab)[y][x].draw_x = isometric_format_x((*tab)[y][x].x, 
                           (*tab)[y][x].y, (*tab)[y][x].z) + offset_x;
            printf("x : %d  ", (*tab)[y][x].x);
            (*tab)[y][x].draw_y = isometric_format_y((*tab)[y][x].x, 
                           (*tab)[y][x].y, (*tab)[y][x].z) + offset_y;
            printf("y : %d\n", (*tab)[y][x].y);
            x++;
        }
        y++;
    }
}

void	zoom_init(t_tab ****tab, char *av)
{
    float zoom;
    int x;
    int y;
    
    zoom = 1.0;
    x = 0;
    while (x < count_lines(av))
    {
        y = 0;
        while (y < count_col(av))
        {
            (**tab)[x][y].draw_x = (**tab)[x][y].x * zoom;
            (**tab)[x][y].draw_y = (**tab)[x][y].y * zoom;
            y++;
        }
        x++;
    }
}