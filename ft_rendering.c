# include "cube.h"

static int  ft_render_line(t_data *data, t_face *tmp, int32_t *texture, double x)
{
    double      y;
    double      top;
    int         x_offset;
    int         y_offset;

    y = (data->wnd_ht / 2) - (tmp->height_1 / 2);
    top = y;
    if (tmp->fix == 'X')
        x_offset = (int)((int)data->array[(int)x].y % data->grd_ht);
    else if (tmp->fix == 'Y')
        x_offset = (int)((int)data->array[(int)x].x % data->grd_wd);
    while (y < ((data->wnd_ht / 2) + (tmp->height_1 / 2)))
    {
        y_offset = (int)((y - top) * \
            (data->grd_ht / tmp->height_1));
        if (0 < y && y < data->wnd_ht)
            mlx_put_pixel(data->ddd__img, \
                x, y,texture[(data->grd_wd * \
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
            if (tmp->typ == '1')
                ft_render_line(data, tmp, data->w_text.tb, x);
            else
                ft_render_line(data, tmp, data->d_text.tb, x);

            tmp->height_1 += step;
            x++;
        }
        tmp = tmp->next;
    }
}
