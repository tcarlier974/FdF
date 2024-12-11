/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:48:39 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/11 13:35:14 by tcarlier         ###   ########.fr       */
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

#  define HEIGHT 1000
#  define WIDTH 1000

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
	int     draw_x;
	int     draw_y;
	int		color;
}				t_tab;

typedef struct	s_line {
	int		dx;
	int		dy;
	int		err;
	int		sx;
	int		sy;
}				t_line;

typedef struct	s_lenth {
	int		offset_x;
	int		offset_y;
}				t_lenth;

int		count_lines(char *av);
void	init_tab(t_tab ***tab, char *av);
int		count_col(char *av);
int  	isometric_format_y(int x, int y, int z);
int  	isometric_format_x(int x, int y, int z);
void	*draw_line_img(t_data *img, t_tab **tab, char *av);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		generate_rgb();
int		create_trgb(int t, int r, int g, int b);
void	change_to_iso(t_tab ***tab, char *av, int offset_x, int offset_y);
void	init_lenth(t_tab **tab, t_lenth *lenth, int height, int width);
int		gen_color(t_tab tab1, t_tab tab2);
int		gen_rgb(int z, int max, int min);
void	init_extremum(char *av, int *max, int *min);
int		max(int a, int b);
void	zoom_init(t_tab ****tab, char *av);
void	_fdf_calcul_draw(t_tab ****tab, int x, int y);
int	_fdf_get_gradient_color(t_tab point1, t_tab point2, t_tab current);

#endif