/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:48:39 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 17:37:08 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./mlx/mlx.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_tab {
	int		x;
	int		y;
	int		z;
	int		color;
}				t_tab;

int		count_lines(char *av);
void	init_tab(t_tab ***tab, char *av);
int		count_col(char *av);
int  	isometric_format_y(int x, int y, int z);
int  	isometric_format_x(int x, int y, int z);
void	*draw_line_img(t_data img, t_tab **tab, char *av);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif