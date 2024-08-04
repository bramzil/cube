/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:07:11 by bramzil           #+#    #+#             */
/*   Updated: 2024/08/04 17:02:12 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube.h"

static int  steps(t_point *p1, t_point *p2, t_point *incr)
{
    double       d_x;
    double       d_y;
    double       steps;

    d_x = (p2->x - p1->x);
    d_y = (p2->y - p1->y);
    steps = fabs(d_x);
    if (fabs(d_x) < fabs(d_y))
        steps = fabs(d_y);
    incr->x = d_x / steps;
    incr->y = d_y / steps;
    return (steps);
}

static int draw_line(mlx_image_t *img, t_point *p1, t_point *p2)
{
    int         i;
    int         end;
    t_point     incr;
    t_point     start;

    i = -1;
    start.x = p1->x;
    start.y = p1->y;
    end = steps(p1, p2, &incr);
    while (++i < end)
    {
        mlx_put_pixel(img, start.x, \
            start.y, 0x00ff00ff);
        start.x += incr.x;
        start.y += incr.y;
        if ((start.x < 0) || (119 < start.x) || \
            (start.y < 0) || (119 < start.y))
            break ;
    }
    return (0);
}

static int  draw_triangle(t_data *data)
{
    int         i;
    int         j;
    t_point     p[3];
    double      angle;

    i = -1;
    while (++i < 5)
    {
        j = -1;
        angle = real_angle(data->plr.d - (M_PI / 2));
        while (++j < 3)
        {
            p[j].x = 60 + (i * cos(angle));
            p[j].y = 60 + (i * sin(angle) * -1);
            angle = real_angle(angle + (M_PI / 2));
        }
        draw_line(data->map_img, &p[0], &p[1]);
        draw_line(data->map_img, &p[1], &p[2]);
        draw_line(data->map_img, &p[2], &p[0]);
    }
    return (0);
}

static int  render_pixel(t_data *data, int *ref, int *ind, int *grd)
{
    ind[0]++;
    if ((0 < ind[1]) && (ind[1] < (grd[1] * 10)) && \
        (0 < ind[0]) && (ind[0] < (grd[0] * 10)))
    {
        
        if (data->map[(int)(ind[1] / grd[1])][(int)\
            (ind[0] / grd[0])] == '1')
            mlx_put_pixel(data->map_img, (ind[0] - ref[0]), \
                (ind[1] - ref[1]), 0xf0f0f0aa);
        else if (data->map[(int)(ind[1] / grd[1])][(int)\
            (ind[0] / grd[0])] == 'd')
            mlx_put_pixel(data->map_img, (ind[0] - ref[0]), \
                (ind[1] - ref[1]), 0x00f0f05f);
    }
    if ((int)((data->plr.x / data->fact) + 60) <= ind[0])
        (ind[0] = ref[0] - 1, ind[1]++);
    return (0);
}

int ft_mini_map(t_data *data)
{
    int     ind[2];
    int     ref[2];
    int     grd[2];

    grd[0] = data->grd_wd / data->fact;
    grd[1] = data->grd_ht / data->fact;
    ref[1] = (int)((data->plr.y / data->fact) - 60);
    ref[0] = (int)((data->plr.x / data->fact) - 60);
    ind[1] = ref[1];
    ind[0] = ref[0] - 1;
    while (ind[1] < (int)((data->plr.y / data->fact) + 60))
        render_pixel(data, ref, ind, grd);
    draw_triangle(data);
    return (0);
}
