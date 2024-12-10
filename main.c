/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:47:50 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/10 18:06:08 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "./get_next_line/get_next_line.h"
#include "fdf.h"
#include <stdio.h>

int    create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

int	my_close(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == ON_DESTROY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

void	*draw_img(void *mlx, int width, int height, t_tab **tab, char *av)
{
	t_data img;
	int x;
	int y;
	t_lenth lenth;
	int c;
	int l;

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	y = 0;
	c = count_lines(av);
	l = count_col(av);
	init_lenth(tab, &lenth, c, l);
	change_to_iso(&tab, av, lenth.offset_x, lenth.offset_y);
	while (y < c)
	{
		x = 0;
		while (x < l)
		{
			my_mlx_pixel_put(&img, tab[y][x].draw_x, tab[y][x].draw_y, tab[y][x].color);
			x++;
		}
		y++;
	}
	return (draw_line_img(&img, tab, av));
}

void    *get_img(void *mlx, int width, int height, char *av)
{
	t_tab	**tab;
	char	*line;
	int i;
	int j;
	int max;
	int min;
	int c;
	int l;

	j = 0;
	c = count_lines(av);
	l = count_col(av);
	init_tab(&tab, av);
	init_extremum(av, &max, &min);
	while (j < l - 1)
	{
		i = 0;
		while (i < c - 1)
		{
			tab[j][i].x = i * 20;
			tab[j][i].y = j * 20;
			tab[j][i].z = ft_atoi(ft_split(line, ' ')[i]);
			tab[j][i].color = gen_rgb(tab[j][i].z, max, min);
			tab[j][i].draw_x = 0;
			tab[j][i].draw_y = 0;
			i++;
		}
		j++;
	}
	return (draw_img(mlx, width, height, tab, av));
}

int	main(int ac, char **av)
{
    void	*mlx;
    void	*mlx_win;
    t_data	img;
    t_vars	vars;

	if (ac != 2)
	{
		ft_putstr_fd("Usage : ./fdf <file name>\n", 2);
		return (1);
	}
    mlx = mlx_init();
    if (mlx == NULL)
        return (1);
    mlx_win = mlx_new_window(mlx, HEIGHT, WIDTH, "FDF");
    if (mlx_win == NULL)
        return (1);
	img.img = get_img(mlx, HEIGHT, WIDTH, av[1]);
	printf("Display\n");
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    vars.mlx = mlx;
    vars.win = mlx_win;
    mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, my_close, &vars);
	mlx_hook(vars.win, ON_DESTROY, 1L<<17, my_close, &vars);
    mlx_loop(mlx);
}

// t_data gen_img(void *mlx)
// {
// 	t_data img;
// 	int j;

// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 								&img.endian);
// 	for (int x = 0; x < 1920 ; x++)
// 	{
// 		if (x % 2 == 0)
// 			j = generate_rgb();
// 		for (int y = 290; y < 790; y ++)
// 		{
// 			my_mlx_pixel_put(&img, x, y, j);
// 		}
// 	}
// 	return img;
// } 
