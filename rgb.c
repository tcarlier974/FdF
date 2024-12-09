/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:18:28 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 00:19:48 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int generate_rgb()
{
    
    static int i = 0;

    int r = (int)(sin(0.01 * i + 0) * 127 + 128);
    int g = (int)(sin(0.01 * i + 2) * 127 + 128);
    int b = (int)(sin(0.01 * i + 4) * 127 + 128);
    i++;
    return create_trgb(0, r, g, b);
}

float fraction(float x1, float x2, float x)
{
 if (x1 != x2)
  return ((x - x1) / (x2 - x1));
 return (0);
}

int interpolate(int start, int end, float ratio)
{
    return (start + ((end - start) * ratio));
}

int gen_rgb(int z, int max, int min)
{
    int r, g, b;
    int r1 = 0x0000FF;
    int r2 = 0xFF0000;
    int g1 = 0x0000FF;
    int g2 = 0xFF0000;
    int b1 = 0x0000FF;
    int b2 = 0xFF0000;

    r = r1 + (r2 - r1) * fraction(min, max, z);
    g = g1 + (g2 - g1) * fraction(min, max, z);
    b = b1 + (b2 - b1) * fraction(min, max, z);

    return create_trgb(0, r, g, b);
}

int gen_color(t_tab tab1, t_tab tab2)
{
    int r, g, b;

    int r1 = (tab1.color >> 16) & 0xFF;
    int r2 = (tab2.color >> 16) & 0xFF;
    int g1 = (tab1.color >> 8) & 0xFF;
    int g2 = (tab2.color >> 8) & 0xFF;
    int b1 = tab1.color & 0xFF;
    int b2 = tab2.color & 0xFF;
    int z = (tab1.z + tab2.z) / 2;

    r = r1 + (r2 - r1) * fraction(tab1.z, tab2.z, z);
    g = g1 + (g2 - g1) * fraction(tab1.z, tab2.z, z);
    b = b1 + (b2 - b1) * fraction(tab1.z, tab2.z, z);
    return create_trgb(0, r, g, b);
}
