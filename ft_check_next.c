/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:57:57 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/02 10:13:25 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static int  between_grds(t_data *data, double x, double y)
{
    int         i;
    int         j;
    int         plr_x;
    int         plr_y;

    plr_x = data->plr.x;
    plr_y = data->plr.y;
    i = ((plr_x / data->grd_wd) + (1 - 2 * (x < plr_x)));
    j = ((plr_y / data->grd_ht) + (1 - 2 * (y < plr_y)));
    if ((data->map[plr_y / data->grd_ht][i] != '0') && \
        (data->map[j][plr_x / data->grd_wd] != '0'))
    {
        i = (((plr_x + (20 * (-1 * (x < plr_x)))) / \
            data->grd_wd) );
        j = (((plr_y + (20 * (-1 * (y < plr_y)))) / \
            data->grd_wd) );
        if ((data->map[plr_y / data->grd_ht][i] != '1') || \
            (data->map[j][plr_x / data->grd_wd] != '0'))
            return (1);
    }
    return (0);
}

int  ft_check_next(t_data *data, double x, double y)
{
    int     x1;
    int     y1;
    char    **map;
    t_door  *door;

    map = data->map;
    x1 = ((x + 7.0 * (1.0 - (2.0 * (x < data->plr.x)))) / \
        data->grd_wd);
    y1 = ((y + 7.0 * (1.0 - (2.0 * (y < data->plr.y)))) / \
        data->grd_ht);
    if (map[y1][x1] != '0')
    {
        if (map[y1][x1] == '1')
            return (1);
        else if (data->map[y1][x1] == 'd')
        {
            door = get_door(data, x1, y1, 0);
            if (door->state == 'C')
                return (1);
        }
    }
    return (0);
}