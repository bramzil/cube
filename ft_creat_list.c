/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:22:54 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/21 17:11:44 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static t_face   *ft_create_node(void)
{
    t_face      *node;
    
    node = (t_face *)malloc(sizeof(t_face));
    node->next = NULL;
    return (node);
}

static int  ft_nearest_axis(double coord)
{
    int     tmp;

    tmp = (int)coord;
    if (((tmp + 1) % 20) == 0)
        return (tmp + 1);
    else if (((tmp - 1) % 20) == 0)
        return (tmp - 1);
    return (tmp);
}

static void ft_add_back(t_face **head, t_face *node)
{
    if (head && node)
    {
        if (!(*head))
            *head = node;
        else
        {
            while ((*head)->next)
                (*head) = (*head)->next;
            (*head)->next = node;
        }
    }
}

void    ft_create_list(t_face *list, double x, double y)
{
    int         axis;
    int         old_x;
    int         old_y;
    t_point     inter;

    while (condition)
    {
        ft
    }

    
}

