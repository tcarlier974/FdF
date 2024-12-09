/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:47:50 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 19:54:26 by tcarlier         ###   ########.fr       */
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
	int	c;
	int	l;

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	y = 0;
	c = count_lines(av);
	l = count_col(av);
	printf("Iso done\n");
	change_to_iso(tab, av);
	while (y < c)
	{
		x = 0;
		while (x < l)
		{
			my_mlx_pixel_put(&img, tab[y][x].x, tab[y][x].y, tab[y][x].color);
			x++;
		}
		y++;
	}
	return (draw_line_img(&img, tab, av));
}

void    *get_img(void *mlx, int width, int height, char *av)
{
	t_tab	**tab;
	int		fd;
	char	*line;
	int i;
	int j;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (NULL);
	j = 0;
	init_tab(&tab, av);
	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (ft_split(line, ' ')[i] != NULL)
		{
			tab[j][i].x = i * 20;
			tab[j][i].y = j * 20;
			tab[j][i].z = ft_atoi(ft_split(line, ' ')[i]);
			tab[j][i].color = create_trgb(0, 125, 0, 125);
			i++;
		}
		free(line);
		j++;
	}
	close(fd);
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
    mlx_win = mlx_new_window(mlx, 500, 500, "FDF");
    if (mlx_win == NULL)
        return (1);
	img.img = get_img(mlx, 500, 500, av[1]);
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
