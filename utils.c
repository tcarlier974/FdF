/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 02:45:07 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 16:47:41 by tcarlier         ###   ########.fr       */
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