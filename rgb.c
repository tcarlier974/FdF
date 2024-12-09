/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:18:28 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 23:55:04 by tcarlier         ###   ########.fr       */
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

int gen_color(t_tab tab1, t_tab tab2)
{
    float ratio;
    int r, g, b;

    if (tab1.z == tab2.z)
        ratio = 0.5;
    else
        ratio = (float)(tab2.z - tab1.z) / (float)max(abs(tab2.z), abs(tab1.z));
    r = interpolate((tab1.color >> 16) & 0xFF, (tab2.color >> 16) & 0xFF, ratio);
    g = interpolate((tab1.color >> 8) & 0xFF, (tab2.color >> 8) & 0xFF, ratio);
    b = interpolate(tab1.color & 0xFF, tab2.color & 0xFF, ratio);
    return create_trgb(0, r, g, b);
}

int gen_rgb(int z, int max, int min)
{
    float ratio;
    int r, g, b;

    if (max == min)
        ratio = 0.5;
    else
        ratio = (float)(z - min) / (float)(max - min);

    if (ratio < 0.33)
    {
        // Interpoler entre bleu (0x0000FF) et cyan (0x00FFFF)
        r = interpolate(0, 0, ratio / 0.33);
        g = interpolate(0, 255, ratio / 0.33);
        b = interpolate(255, 255, ratio / 0.33);
    }
    else if (ratio < 0.66)
    {
        // Interpoler entre cyan (0x00FFFF) et jaune (0xFFFF00)
        r = interpolate(0, 255, (ratio - 0.33) / 0.33);
        g = interpolate(255, 255, (ratio - 0.33) / 0.33);
        b = interpolate(255, 0, (ratio - 0.33) / 0.33);
    }
    else
    {
        // Interpoler entre jaune (0xFFFF00) et orange (0xFFA500)
        r = interpolate(255, 255, (ratio - 0.66) / 0.34);
        g = interpolate(255, 165, (ratio - 0.66) / 0.34);
        b = interpolate(0, 0, (ratio - 0.66) / 0.34);
    }

    return create_trgb(0, r, g, b);
}
