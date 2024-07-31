# include "cube.h"

static int get_x_offset(t_data *data, t_face *tmp, double x)
{
    int     x_offset;

    x_offset = 0;
    if (tmp->fix == 'X')
        x_offset = ((int)((int)data->array[(int)x].y % \
            data->grd_ht));
    else if (tmp->fix == 'Y')
        x_offset = ((int)((int)data->array[(int)x].x % \
            data->grd_wd));
    return (x_offset);
}

static void indices(t_data *data, t_face *tmp, int *tab, int x)
{
    if (tmp->fix == 'X')
    {
        tab[1] = (data->array[x].y / data->grd_ht);
        if (data->plr.x < data->array[x].x)
            tab[0] = (data->array[x].x / data->grd_wd);
        else if (data->array[x].x < data->plr.x)
            tab[0] = ((data->array[x].x / data->grd_wd) - 1);
    }
    else if (tmp->fix == 'Y')
    {
        tab[0] = (data->array[x].x / data->grd_wd);
        if (data->plr.y < data->array[x].y)
            tab[1] = (data->array[x].y / data->grd_ht);
        else if (data->array[x].y < data->plr.y)
            tab[1] = ((data->array[x].y / data->grd_ht) - 1);
    }
}

static int  put_pixel(t_data *data, int *ind, t_point *pos)
{
    char        **map;

    map = data->map;
    if (map[ind[1]][ind[0]] == '1')
        mlx_put_pixel(data->ddd__img, pos->x, pos->y, \
            data->w_text.tb[ind[2]]);
    else
        mlx_put_pixel(data->ddd__img, pos->x, pos->y, \
            data->d_text.tb[ind[2]]);
    return (0);
}

static int  ft_render_line(t_data *data, t_face *tmp, int x)
{
    double      y;
    double      top;
    int         ind[3];
    int         x_offset;
    int         y_offset;
    t_point     pixel_pos;

    indices(data, tmp, ind, x);
    x_offset = get_x_offset(data, tmp, x);
    y = (data->wnd_ht / 2) - (tmp->height_1 / 2);
    top = y;
    pixel_pos.x = x;
    while (y < ((data->wnd_ht / 2) + (tmp->height_1 / 2)))
    {
        y_offset = (int)((y - top) * \
            (data->grd_ht / tmp->height_1));
        if (0 < y && y < data->wnd_ht)
        {
            pixel_pos.y = y;
            ind[2] = (data->grd_wd * y_offset) + x_offset;
            put_pixel(data, ind, &pixel_pos);
        }
        y++;
    }
    return (0);
}

void    ft_render_wall(t_data *data)
{
    int         i;
    int         x;
    t_face      *tmp;
    double      step;

    x = 0, 
    tmp = data->face_lst;
    while (tmp)
    {
        i = -1;
        step = (tmp->height_2 - tmp->height_1) / \
            tmp->rays;
        while (++i < tmp->rays)
        {
            ft_render_line(data, tmp, x);
            tmp->height_1 += step;
            x++;
        }
        tmp = tmp->next;
    }
}
