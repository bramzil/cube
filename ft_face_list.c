/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_face_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/03 11:42:03 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static t_face   *new_node()
{
    t_face      *node;
    
    node = malloc(sizeof(t_face));
    if (node)
    {
        node->fix = 'U';
        node->dir = 'U';
        node->rays = 0;
        node->next = NULL;
    }
    return (node);
}

static void set_dir(t_data *data, t_face *tmp, int i)
{
    if (tmp->fix == 'Y')
    {
        if (data->array[i].y < data->plr.y)
            tmp->dir = 'N';
        else if (data->plr.y < data->array[i].y)
            tmp->dir = 'S';
    }
    else
    {
        if (data->array[i].x < data->plr.x)
            tmp->dir = 'E';
        else if (data->plr.x < data->array[i].x)
            tmp->dir = 'W';
    }
}

static void set_fix(t_face *tmp, t_point *arr, t_point *ref, int i)
{
    if (arr[i].y != ref->y)
            tmp->fix = 'X';
    else if (arr[i].x != ref->x)
        tmp->fix = 'Y';
}


static int  new_face(t_data *dt, t_face **tp, t_point *rf, int i)
{
    t_face      *new;

    rf->x = dt->array[i].x;
    rf->y = dt->array[i].y;
    if (tp)
    {
        new = new_node();
        if (!new)
            return (-1);
        if ((*tp) == NULL)
            (*tp) = new;
        else
        {
            (*tp)->next = new;
            (*tp) = (*tp)->next;
        }
    }
    return (-1 * (tp == NULL));
}

t_face  *face_list(t_data *data)
{
    int         i;
    t_point     ref;
    t_point     *arr;
    t_face      *tmp[2];

    i = -1;
    tmp[0] = NULL;
    new_face(data, &tmp[0], &ref, 0);
    (tmp[1] = tmp[0], arr = data->array);
    while (tmp[0] && (++i < data->wnd_wd))
    {
        if (tmp[0]->fix == 'U')
            set_fix(tmp[0], arr, &ref, i);
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
