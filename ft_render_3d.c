/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:01:29 by bramzil           #+#    #+#             */
/*   Updated: 2024/07/21 16:35:02 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

int ft_render_line(t_data *data, double dst, double x)
{
    double     y;
    double     height;
    double     pro_plan;

    pro_plan = 700 / (2 * tan(30 * (M_PI / 180)));
    height = ((30 * pro_plan) / dst);
    y = (350 - (height / 2));
    while (y < (350 + (height / 2)))
    {
        if (0 < x && x < 760 && 0 < y && y < 700)
            mlx_put_pixel(data->img_3d, x, y, (7204967120 - (dst + 10)));
        y++;
    }
    return (0);
}