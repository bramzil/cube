/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/30 23:39:17 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static int new_face(t_data *data, t_face **tmp, int i)
{
    (*tmp)->next = new_node(data->array[i].x, \
        data->array[i].y);
    if (!(*tmp)->next)
        return (-1);
    (*tmp) = (*tmp)->next;
    return (0);
}

static int  update_x_face(t_data *data, t_face **tmp, int i)
{   
    int         y;
    int         x;

    x = (data->array[i].x / data->grd_wd);
    y = (data->array[i].y / data->grd_ht);
    if (data->array[i].x < data->plr.x)
        ((*tmp)->dir = 'E', x--);
    else if (data->array[i].x < data->plr.x)
        (*tmp)->dir = 'W';
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].y != (*tmp)->y_ref) || \
        (data->map[y][x] != (*tmp)->typ))
        (*tmp)->height_2 = get_height(data, i);
    if (data->map[y][x] != (*tmp)->typ)
        if (new_face(data, tmp, i))
            return (-1);
    return (0);
}

static int  update_y_face(t_data *data, t_face **tmp, int i)
{
    int         x;
    int         y;

    x = (data->array[i].x / data->grd_wd);
    y = (data->array[i].y / data->grd_ht);
    if (data->array[i].y <  data->plr.y)
        ((*tmp)->dir = 'N', y--);
    else if (0 < (data->array[i].y - data->plr.y))
        (*tmp)->dir = 'S';
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].y != (*tmp)->y_ref) || \
        (data->map[y][x] != (*tmp)->typ))
        (*tmp)->height_2 = get_height(data, i);
    if (data->map[y][x] != (*tmp)->typ)
        if (new_face(data, tmp, i))
            return (-1);
    return (0);
}

static void init_face(t_data *data, t_face *tmp, int i)
{
    int         x;
    int         y;

    x = data->array[i].x / data->grd_wd;
    y = data->array[i].y / data->grd_ht;
    if (data->array[i].x != tmp->x_ref)
    {
        tmp->fix = 'Y';
        ((data->array[i].y < data->plr.y) && y--);
    }
    else if (data->array[i].y != tmp->y_ref)
    {
        tmp->fix = 'X';
        ((data->array[i].x < data->plr.x) && x--);
    }
    if (tmp->height_1 == -1)
        tmp->height_1 = get_height(data, i);
    if ((i == (data->wnd_wd - 1)) || \
        (data->array[i + 1].x != tmp->x_ref))
        tmp->height_2 = get_height(data, i);
    (data->map[y][x] == 'd') && (tmp->typ = 'd');
}

t_face  *ft_create_list(t_data *data)
{
    int         i;
    t_face      *tmp[2];

    i = -1;
    tmp[0] = new_node(data->array[0].x, \
        data->array[0].y);
    tmp[1] = tmp[0];
    while (tmp[0] && (++i < data->wnd_wd))
    {
        if (tmp[0]->fix == 'U')
            init_face(data, tmp[0], i);
        else if ((tmp[0]->fix == 'X') && \
            (data->array[i].x == tmp[0]->x_ref))
            update_x_face(data, &tmp[0], i);  
        else if ((tmp[0]->fix == 'Y') && \
            (data->array[i].y == tmp[0]->y_ref))
            update_y_face(data, &tmp[0], i);
        else if (new_face(data, &tmp[0], i))
            return (ft_free_lst(tmp[1]), NULL);
        tmp[0]->rays++;
    }
    return (tmp[1]);
}

