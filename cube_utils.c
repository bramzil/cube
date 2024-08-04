/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:29:18 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/04 16:24:51 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int ft_free_lst(t_face *lst)
{
    t_face      *tmp;
    
    while (lst && lst->next)
    {
        tmp = lst;
        lst = lst->next;
        free (tmp);
    }
    return (0);
}

void    animation(void *arg)
{
    static int  counter;
    if (counter == 0)
    {
        ft_door_ctl(arg);
        counter = 5;
        shut(arg);
    }
    counter--;
}

double get_height(t_data *data, int i)
{
    double      dst;
    double      unit;
    double      oppo;
    double      adja;
    double      ray_angle;
    double      result;

    unit = (60.0 * (M_PI / 180.0)) / data->wnd_wd;
    ray_angle = real_angle(fabs((data->wnd_wd / \
        2.0) - i) * unit);
    adja = fabs(data->plr.x - data->inter_arr[i].x);
    oppo = fabs(data->plr.y - data->inter_arr[i].y);
    dst = sqrt((oppo * oppo) + (adja * adja)) * \
        cos(ray_angle);
    result = ((300.0 * 100.0) / dst);
    return (result);
}

void    fill_doors_array(t_data *data)
{
    int         ind[3];

    ind[2] = 0;
    ind[1] = 0;
    ind[0] = -1;
    while (data->map[ind[1]])
    {
        ind[0]++;
        if (data->map[ind[1]][ind[0]] == 'd')
        {
            data->door_arr[ind[2]].i = ind[0];
            data->door_arr[ind[2]].j = ind[1];
            data->door_arr[ind[2]].var = 32;
            data->door_arr[ind[2]].state = 'C';
            ind[2]++;
        }
        if (!data->map[ind[1]][ind[0] + 1] && ++ind[1])
            ind[0] = -1;
    }
}