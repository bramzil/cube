/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:57:57 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/31 01:27:47 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static void get_around(t_data *data, int *x1, int *y1)
{
    x1[0] = data->plr.x / data->grd_wd;
    x1[1] = (data->plr.x - 10) / data->grd_wd;
    x1[2] = (data->plr.x + 10) / data->grd_wd;
    y1[0] = data->plr.y / data->grd_ht;
    y1[1] = (data->plr.y - 10) / data->grd_ht;
    y1[2] = (data->plr.y + 10) / data->grd_ht;
}

static int  between_grds(t_data *data, double x, double y)
{
    int     x1[3];
    int     y1[3];
    char    **map;

    map = data->map;
    get_around(data, x1, y1);
    if ((x < data->plr.x) && (y < data->plr.y) && \
        map[y1[0]][x1[1]] != '0' && map[y1[1]][x1[0]] != '0')
        return (1);
    else if ((data->plr.x < x) && (data->plr.y < y) && \
        map[y1[0]][x1[2]] != '0' && map[y1[2]][x1[0]] != '0')
        return (1);
    else if ((x < data->plr.x) && (data->plr.y < y) && \
        map[y1[0]][x1[1]] != '0' && map[y1[2]][x1[0]] != '0')
        return (1);
    else if ((data->plr.x < x) && (y < data->plr.y) && \
        map[y1[0]][x1[2]] != '0' && map[y1[1]][x1[0]] != '0')
        return (1);
    return (0);
}

int  ft_check_next(t_data *data, double x, double y)
{
    int     x1;
    int     y1;
    char    **map;

    map = data->map;
    x1 = ((x + 3 * (1 - (2 * (x < data->plr.x)))) / \
        data->grd_wd);
    y1 = ((y + 3 * (1 - (2 * (y < data->plr.y)))) / \
        data->grd_ht);
    if (!between_grds(data, x, y) && map[y1][x1] == '0')
        return (0);
    return (1);
}