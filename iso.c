/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 19:50:30 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/11 13:38:42 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

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
        while (x < l)
        {
            (*tab)[y][x].draw_x += offset_x;
            (*tab)[y][x].draw_y += offset_y;
            x++;
        }
        y++;
    }
}

void	zoom_init(t_tab ****tab, char *av)
{
    int x;
    int y;
    
    x = 0;
    printf("Zoom start \n");
    while (x < count_col(av))
    {
        y = 0;
        while (y < count_lines(av))
        {
            _fdf_calcul_draw(tab, x, y);
            y++;
        }
        x++;
    }
    printf("Zoom done\n");
}

void	_fdf_calcul_draw(t_tab ****tab, int x, int y)
{
    float zoom;
    float scale_x;
    float scale_y;
    float scale_z;
    
    zoom = 0.6;
    scale_x = (**tab)[y][x].x * zoom;
    scale_y = (**tab)[y][x].y * zoom;
    scale_z = (**tab)[y][x].z * zoom;
    (**tab)[y][x].draw_x = (scale_x - scale_y) * cos(0.523599);
    (**tab)[y][x].draw_y = (scale_x + scale_y) * sin(0.523599) - scale_z;
}