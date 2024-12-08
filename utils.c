/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:45:07 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 23:36:55 by tcarlier         ###   ########.fr       */
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

void	init_lenth(t_tab **tab, t_lenth *lenth, int c, int l)
{
	(*lenth).offset_x = HEIGHT / 2 - isometric_format_x(tab[c / 2][l / 2].x, tab[c / 2][l / 2].y, tab[c / 2][l / 2].z);
	(*lenth).offset_y = WIDTH / 2 - isometric_format_y(tab[c / 2][l / 2].x, tab[c / 2][l / 2].y, tab[c / 2][l / 2].z);
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
