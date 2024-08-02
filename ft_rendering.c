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
        tab[0] = (data->array[x].x / data->grd_wd) - \
            1 * (data->array[x].x < data->plr.x);
    }
    else if (tmp->fix == 'Y')
    {
        tab[0] = (data->array[x].x / data->grd_wd);
        tab[1] = (data->array[x].y / data->grd_ht) - \
            1 * (data->array[x].y < data->plr.y);
    }
}

static int  put_pixel(t_data *data, int *ind, t_point *pos)
{
    char        **map;

    map = data->map;
    if (map[ind[1]][ind[0]] == '1')
        mlx_put_pixel(data->proj_img, pos->x, pos->y, \
            data->w_text.tb[ind[2]]);
    else
        mlx_put_pixel(data->proj_img, pos->x, pos->y, \
            data->d_text.tb[ind[2]]);
    return (0);
}

static int  line(t_data *data, t_face *tmp, t_point *offset, int x)
{
    double      top;
    int         ind[3];
    t_point     pixel_pos;

    pixel_pos.x = x;
    indices(data, tmp, ind, x);
    pixel_pos.y = (data->wnd_ht / 2.0) - \
        (tmp->height / 2.0);
    top = pixel_pos.y;
    while (pixel_pos.y < ((data->wnd_ht / 2.0) + \
        (tmp->height / 2.0)))
    {
        offset->y = (int)((pixel_pos.y - top) * \
            (data->grd_ht / tmp->height));
        if (0 < pixel_pos.y && pixel_pos.y < data->wnd_ht)
        {
            ind[2] = (data->grd_wd * offset->y) + offset->x;
            put_pixel(data, ind, &pixel_pos);
        }
        pixel_pos.y++;
    }
    return (0);
}

void    ft_render_wall(t_data *data)
{
    int         i;
    int         x;
    t_face      *tmp;
    t_point     offset;

    x = 0;
    tmp = data->face_lst;
    while (tmp)
    {
        i = -1;
        while (++i < tmp->rays)
        {
            offset.x = get_x_offset(data, tmp, x);
            tmp->height = get_height(data, x);
            line(data, tmp, &offset, x);
            x++;
        }
        tmp = tmp->next;
    }
}
