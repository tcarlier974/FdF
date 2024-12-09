/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarlier <tcarlier@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:27:56 by tcarlier          #+#    #+#             */
/*   Updated: 2024/12/09 02:25:18 by tcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* get_next_line_utils.c */
/* get_next_line_utils.c */
#include "get_next_line.h"

void	ft_init(t_gnl *f)
{
    if (!f)
        return;
    if (!f->buf)
    {
        f->buf = ft_strdup("");
        f->eof = 0;
    }
}

void	cleanup_fd(t_gnl *f)
{
    if (!f)
        return;
    if (f->buf)
    {
        free(f->buf);
        f->buf = NULL;
    }
    f->eof = 0;
}
