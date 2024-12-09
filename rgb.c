/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:18:28 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 23:32:16 by tcarlier         ###   ########.fr       */
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

static int interpolate(int start, int end, float ratio)
{
    return (int)(start + (end - start) * ratio);
}

static int  max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int gen_color(int z1, int z2, int color1, int color2)
{
    float ratio;
    int r, g, b;

    // Calculer le ratio basé sur la différence de hauteur
    if (z1 == z2)
        ratio = 0.5;
    else
        ratio = (float)(z2 - z1) / (float)max(abs(z2), abs(z1));

    // Interpoler les composantes de couleur
    r = interpolate((color1 >> 16) & 0xFF, (color2 >> 16) & 0xFF, ratio);
    g = interpolate((color1 >> 8) & 0xFF, (color2 >> 8) & 0xFF, ratio);
    b = interpolate(color1 & 0xFF, color2 & 0xFF, ratio);

    return create_trgb(0, r, g, b);
}