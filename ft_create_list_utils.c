/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:29:18 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/30 12:51:23 by bramzil          ###   ########.fr       */
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
    double      oppo;
    double      adja;
    double      result;

    adja = fabs(data->plr.x - data->array[i].x);
    oppo = fabs(data->plr.y - data->array[i].y);
    result = ((300 * 200) / sqrt((oppo * oppo) + \
        (adja * adja)));
    return (result);
} 

t_face   *new_node(double x_ref, double y_ref)
{
    t_face      *node;
    
    node = malloc(sizeof(t_face));
    if (node)
    {
        node->height_1 = -1;
        node->x_ref = x_ref;
        node->y_ref = y_ref;
        node->fix = 'U';
        node->dir = 'U';
        node->typ = '1';
        node->rays = 0;
        node->next = NULL;
    }
    return (node);
}