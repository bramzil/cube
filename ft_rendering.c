# include "cube.h"

static int  ft_render_line(t_data *data, t_face *tmp, double x)
{
    double      y;
    double      top;
    int         x_offset;
    int         y_offset;

    y = (data->wnd_ht / 2) - (tmp->height_1 / 2);
    top = y;
    if (tmp->fix == 1)
        x_offset = (int)((int)data->array[(int)x].y % data->grd_ht);
    else
        x_offset = (int)((int)data->array[(int)x].x % data->grd_wd);
    while (y < ((data->wnd_ht / 2) + (tmp->height_1 / 2)))
    {
        y_offset = (int)((y - top) * \
            (data->grd_ht / tmp->height_1));
        if (0 < y && y < data->wnd_ht)
            mlx_put_pixel(data->ddd__img, \
                x, y, data->texture.tb[(data->grd_wd * \
                    y_offset) + x_offset]);
        y++;
    }
    return (0);
}

void    ft_render_wall(t_data *data)
{
    int         i;
    double      x;
    t_face      *tmp;
    double      step;

    x = 0, 
    tmp = data->face_lst;
    while (tmp)
    {
        i = -1;
        step = (tmp->height_2 - tmp->height_1) / tmp->rays;
        while (++i < tmp->rays)
        {
            ft_render_line(data, tmp, x);
            tmp->height_1 += step;
            x++;
        }
        tmp = tmp->next;
    }
}
