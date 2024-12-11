/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:45:07 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/11 13:35:02 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_lines(char *av)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

void	init_tab(t_tab ***tab, char *av)
{
	int		i;
	int		j;
	int 	fd;
	char	*line;

	*tab = malloc(sizeof(t_tab *) * count_lines(av));
	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		return ;
	j = 0;
	while ((line = get_next_line(fd)))
	{
		while (ft_split(line, ' ')[i] != NULL)
			i++;
		(*tab)[j] = malloc(sizeof(t_tab) * i);
		j++;
		free(line);
	}
	close(fd);
	free(line);
}

int	count_col(char *av)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	i = 0;
	while (ft_split(line, ' ')[i] != NULL)
		i++;
	close(fd);
	free(line);
	return (i);
}

void	init_max_min(t_tab **tab, int c, int l, int *min_x, int *max_x, int *min_y, int *max_y)
{
	int x;
	int y;

	*min_x = tab[0][0].draw_x;
	*max_x = tab[0][0].draw_x;
	*min_y = tab[0][0].draw_y;
	*max_y = tab[0][0].draw_y;
	y = 0;
	while (y < c)
	{
		x = 0;
		while (x < l)
		{
			if (tab[y][x].draw_x < *min_x)
				*min_x = tab[y][x].draw_x;
			if (tab[y][x].draw_x > *max_x)
				*max_x = tab[y][x].draw_x;
			if (tab[y][x].draw_y < *min_y)
				*min_y = tab[y][x].draw_y;
			if (tab[y][x].draw_y > *max_y)
				*max_y = tab[y][x].draw_y;
			x++;
		}
		y++;
	}
}

void	init_lenth(t_tab **tab, t_lenth *lenth, int c, int l)
{
	int min_x;
	int max_x;
	int min_y;
	int max_y;

	init_max_min(tab, c, l, &min_x, &max_x, &min_y, &max_y);
	(*lenth).offset_x = (WIDTH - (max_x - min_x)) / 2 - min_x;
	(*lenth).offset_y = (HEIGHT - (max_y - min_y)) / 2 - min_y;
}

void	init_extremum(char *av, int *max, int *min)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return ;
	*max = 0;
	*min = 0;
	while ((line = get_next_line(fd)))
	{
		i = 0;
		while (ft_split(line, ' ')[i] != NULL)
		{
			if (ft_atoi(ft_split(line, ' ')[i]) > *max)
				*max = ft_atoi(ft_split(line, ' ')[i]);
			if (ft_atoi(ft_split(line, ' ')[i]) < *min)
				*min = ft_atoi(ft_split(line, ' ')[i]);
			i++;
		}
		free(line);
	}
	close(fd);
}
