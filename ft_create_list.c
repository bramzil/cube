/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/31 02:17:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static void set_dir(t_data *data, t_face *tmp, int i)
{
    if (tmp->fix == 'Y')
    {
        if (data->array[i].y <  data->plr.y)
            tmp->dir = 'N';
        else if (0 < (data->array[i].y - data->plr.y))
            tmp->dir = 'S';
    }
    else
    {
        if (data->array[i].x < data->plr.x)
            tmp->dir = 'E';
        else if (data->array[i].x < data->plr.x)
            tmp->dir = 'W';
    }
}

t_face  *ft_create_list(t_data *data)
{
    int         i;
    t_point     ref;
    t_point     *arr;
    t_face      *tmp[2];

    i = -1;
    tmp[0] = NULL;
    new_face(data, &tmp[0], &ref, 0);
    tmp[1] = tmp[0];
    arr = data->array;
    while (tmp[0] && (++i < data->wnd_wd))
    {
        if ((tmp[0]->fix == 'U') && (arr[i].y != ref.y))
            tmp[0]->fix = 'X';
        else if ((tmp[0]->fix == 'U') && (arr[i].x != ref.x))
            tmp[0]->fix = 'Y';
        else if (((arr[i].x != ref.x) || (arr[i].y != ref.y)) && \
            new_face(data, &tmp[0], &ref, i))
            return (ft_free_lst(tmp[1]), NULL);
        if ((tmp[0]->dir == 'U') && \
            (((tmp[0]->fix == 'X') && (arr[i].x == ref.x)) || \
            ((tmp[0]->fix == 'Y') && (arr[i].y == ref.y))))
            set_dir(data, tmp[0], i);
        tmp[0]->rays++;
    }
    return (tmp[1]);
}
