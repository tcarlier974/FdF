/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:18:28 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 00:43:11 by tcarlier         ###   ########.fr       */
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

    ratio = fraction(min, max, z);
    r = interpolate(50, 255, ratio); // De 0 à 255 pour le rouge
    g = interpolate(0, 0, ratio);   // De 0 à 0 pour le vert (pas de vert)
    b = interpolate(255, 50, ratio); // De 255 à 0 pour le bleu

    return create_trgb(0, r, g, b);
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}