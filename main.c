/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:47:50 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 16:19:37 by tcarlier         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
	int i;

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	i = 0;

	while (i < count_lines(av))
	{
		my_mlx_pixel_put(&img, tab[i]->x, tab[i]->y, tab[i]->color);
		i++;
	}
	return (img.img);
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
	i = 0, j = 0;
	tab = malloc(sizeof(t_tab) * count_lines(av));
	while ((line = get_next_line(fd)))
	{
		while (ft_split(line, ' ')[i])
		{
			tab[j]->x = j + width / 4;
			printf("test\n");
			tab[j]->y = i + height / 4;
			tab[j]->z = ft_atoi(ft_split(line, ' ')[i]);
			tab[j]->color = create_trgb(0, 255, 255, 255);
		}
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
    mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");
    if (mlx_win == NULL)
        return (1);
	img.img = get_img(mlx, 1920, 1080, av[1]);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    vars.mlx = mlx;
    vars.win = mlx_win;
    mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, my_close, &vars);
	mlx_hook(vars.win, ON_DESTROY, 1L<<17, my_close, &vars);
    mlx_loop(mlx);
}



// int generate_rgb()
// {
//     // get all the rgb color from the gratient each time i call the function
//     static int i = 0;
//     int r = (int)(sin(0.01 * i + 0) * 127 + 128);
//     int g = (int)(sin(0.01 * i + 2) * 127 + 128);
//     int b = (int)(sin(0.01 * i + 4) * 127 + 128);
//     i++;
//     return create_trgb(0, r, g, b);
// }

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