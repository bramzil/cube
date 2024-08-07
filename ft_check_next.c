/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 00:57:57 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/07 16:50:35 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static int  check_dir(t_data *data, double angle)
{
    int             i;
    int             j;
    int             h;
    t_point         start;

    h = 0;
    start.x = data->plr.x;
    start.y = data->plr.y;
    while (++h < 13)
    {
        i = (start.x + (h * cos(angle))) / data->grd_wd;
        j = (start.y + (h * sin(angle) * -1)) / data->grd_ht;
        if (data->map[j][i] == '1')
            return (1);
    }
    return (0);
}

int  ft_check_next(t_data *data, double angle)
{
    int         st1;
    int         st2;
    int         st3;
    double      rad;
    
    rad = (M_PI / 180);
    if (check_dir(data, angle))
        return (1);
    if (check_dir(data, real_angle(angle + (30 * rad))) && \
        check_dir(data, real_angle(angle - (30 * rad))))
        return (1);
    return (0);
}
