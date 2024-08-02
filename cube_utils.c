/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:29:18 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/03 11:43:06 by bramzil          ###   ########.fr       */
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
    adja = fabs(data->plr.x - data->array[i].x);
    oppo = fabs(data->plr.y - data->array[i].y);
    dst = sqrt((oppo * oppo) + (adja * adja)) * \
        cos(ray_angle);
    result = ((200.0 * 200.0) / dst);
    return (result);
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