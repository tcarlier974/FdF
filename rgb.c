/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:18:28 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 00:45:46 by tcarlier         ###   ########.fr       */
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
    float ratio;
    int cold[3] = {0, 0, 255};    // Blue
    int neutral[3] = {255, 255, 255}; // Green
    int hot[3] = {255, 0, 0};     // Red

    ratio = fraction(min, max, z);
    if (ratio < 0.5)
    {
        ratio *= 2;
        r = interpolate(cold[0], neutral[0], ratio);
        g = interpolate(cold[1], neutral[1], ratio);
        b = interpolate(cold[2], neutral[2], ratio);
    }
    else
    {
        ratio = (ratio - 0.5) * 2;
        r = interpolate(neutral[0], hot[0], ratio);
        g = interpolate(neutral[1], hot[1], ratio);
        b = interpolate(neutral[2], hot[2], ratio);
    }
    return create_trgb(0, r, g, b);
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}