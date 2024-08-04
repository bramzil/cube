/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:57:57 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/04 16:39:20 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static int  between_grds(t_data *data, double x, double y)
{
    int         i;
    int         j;

    i = ((data->plr.x + 13 - (26 * (data->plr.x < x))) / \
        data->grd_wd) ;
    j = ((data->plr.y  + 13 - (26 * (data->plr.y < y)) / \
        data->grd_ht));
    if ((data->map[j][(int)(data->plr.x / data->grd_wd)] == '1') && \
        (data->map[(int)(data->plr.y / data->grd_ht)][i] == '1'))
        return (1);
    return (0);
}

int  ft_check_next(t_data *data, double x, double y)
{
    int     x1;
    int     y1;
    char    **map;

    map = data->map;
    x1 = ((x + 3 - (6 * (x < data->plr.x))) / \
        data->grd_wd);
    y1 = ((y + 3 - (6 * (y < data->plr.y))) / \
        data->grd_ht);
    if ((map[y1][x1] != '0'))
    {
        if (map[y1][x1] == '1')
            return (1);
    }
    return (0);
}